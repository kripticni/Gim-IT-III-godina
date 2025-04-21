using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Threading;
using System.Net.Http;
using System.Net.Security;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing.Imaging;
using GUI; //Console.writeline

//sealed sprecava dalje nasledjivanje
public sealed class Peer : IFajl
{
    public Korisnik Korisnik;
    public Mreza Mreza;
    const int DEFAULT_PORT = 51888;
    public static readonly string REQUEST_STRING = "P2PChat Scan Request";
    public static readonly string REQUEST_CHAT_STRING = "P2PChat Initiate Chat";
    public static readonly string MESSAGE_HEADER = "P2PChat Send Message: ";
    public static readonly string FILE_HEADER = "P2PChat Send File: ";
    public int Port { get; private set; }
    public byte PrivacySettings { get; private set; }
    public static readonly int IME_BIT = 0;
    public static readonly int PREZIME_BIT = 1;
    public static readonly int DATUM_BIT = 2;
    public static readonly int POL_BIT = 3;
    public static readonly int K_IME_BIT = 4;
    public static readonly int EMAIL_BIT = 5;
    public static readonly int BROJ_BIT = 6;
    public static readonly int PROFILNA_BIT = 7;

    public Peer(Korisnik k, Mreza m, byte ps)
    {
        Korisnik = k;
        Mreza = m;
        PrivacySettings = ps;
        Port = DEFAULT_PORT;
        Peers = new HashSet<Pair<IPAddress, Korisnik>>();
    }

    public Peer(string put, IPAddress ip)
    {
        this.Citaj(put);
        this.Mreza.PrivateIP = ip;
        Port = DEFAULT_PORT;
        Peers = new HashSet<Pair<IPAddress, Korisnik>>();
    }
    public Peer(string put)
    {
        this.Citaj(put);
        Port = DEFAULT_PORT;
        Peers = new HashSet<Pair<IPAddress, Korisnik>>();
    }

    public string FilteredData
    {
        get
        {
            string ret = "";
            if (NetCalc.isBitSet(PrivacySettings, IME_BIT)) ret += $"Ime: {Korisnik.Ime}\n";
            if (NetCalc.isBitSet(PrivacySettings, PREZIME_BIT)) ret += $"Prezime: {Korisnik.Prezime}\n";
            if (NetCalc.isBitSet(PrivacySettings, DATUM_BIT)) ret += $"Datum rodjenja: {Korisnik.DatumRodjenja.ToString()}\n";
            if (NetCalc.isBitSet(PrivacySettings, POL_BIT)) ret += $"Pol: {Korisnik.Pol}\n";
            if (NetCalc.isBitSet(PrivacySettings, K_IME_BIT)) ret += $"Korisnicko ime: {Korisnik.KorisnickoIme}\n";
            if (NetCalc.isBitSet(PrivacySettings, EMAIL_BIT)) ret += $"Email: {Korisnik.Email}\n";
            if (NetCalc.isBitSet(PrivacySettings, BROJ_BIT)) ret += $"Broj telefona: {Korisnik.BrojTelefona}\n";
            if (NetCalc.isBitSet(PrivacySettings, PROFILNA_BIT))
            {
                if (Korisnik.profilna == null)
                    throw new ArgumentNullException("Profilna nije postavljena");
                if (Korisnik.PutDoProfilne != "defaultmalepfp.jpg" && Korisnik.PutDoProfilne != "defaultfemalepfp.jpg")
                    ret += $"Profilna: {Korisnik.EnkodirajBitmapB64(Korisnik.profilna, ImageFormat.Png)}\n";
                else
                    ret += $"Profilna: {Korisnik.PutDoProfilne}";
            }
            return ret;
        }
    }

    //hocemo da cuvamo sve pronadjene peer-ove u hashsetu
    //koristimo hashset da ne bi dodali iste profile vise puta
    //idealno bi i set isto radio (cak bolje), ali nemamo set u C#
    //kad smo vec primorani da koristimo hashset, nasa Pair klasa
    //ce da daje hash i proverava za jednakost jedino vezano za Pair.first
    //da bi imali neku korist od nje
    public HashSet<Pair<IPAddress, Korisnik>> Peers { get; set; }
    public static bool SetUpdate<T>(HashSet<T> set, T item)
    {
        if (set.Contains(item))
        {
            set.Remove(item);
            set.Add(item);
            return true;
        }
        set.Add(item);
        return false;
    }
    private bool SetUpdate(HashSet<Pair<IPAddress,Korisnik>> set, Pair<IPAddress,Korisnik> item)
    {
        if (set.Contains(item))
        {
            set.Remove(item);
            set.Add(item);
            return true;
        }
        set.Add(item);
        return false;
    }

    private TcpListener listener;
    public string ListenerAddressString
    {
        get { return $"{Mreza.PrivateIP.ToString()}:{Port.ToString()}"; }
    }
    public Pair<IPAddress,int> ListenerAddress
    {
        get { return new Pair<IPAddress, int>(Mreza.PrivateIP, Port); }
    }

    //koristimo da bi mogli van klasu da napravimo
    //CancellationTokenSource koj ce da kontrolise
    //kolko dugo cemo da skeniramo ili slusamo
    //CancellationTokenSource cts = new...
    //cts.Close() bi zatvorio listener
    public async Task Listener(CancellationToken LCancelToken)
    {
        listener = new TcpListener(Mreza.PrivateIP, Port);
        listener.Start();

        try
        {
            while (!LCancelToken.IsCancellationRequested)
            {
                Task<TcpClient> acceptTask = listener.AcceptTcpClientAsync(); //zapravo listener task
                Task completedTask = await Task.WhenAny(acceptTask, Task.Delay(Timeout.Infinite, LCancelToken));
                //completed task spaja infinite sleep koji se prekida na cancellation token sa nas listener
                //completed task sadrzi task koji se *prvi* zavrsi od ova dva taska
                //a zato sto je sleep infinite on se jedino zavrsava na cancellation
                //tako da kad nas completed task nije listener, onda break-ujemo sto
                //zavrsava oba taska na return

                if (completedTask == acceptTask)
                {
                    TcpClient client = acceptTask.Result;
                    _ = RespondInfo(client);
                }
                else
                {
                    break;
                }
            }
        }
        catch (OperationCanceledException)
        {
            
        }
        finally
        {
            listener.Stop();
        }
    }

    private async Task RespondInfo(TcpClient client)
    {
        const int maxSize = 2 * 1024 * 1024; //ne prihavata vise od 2mb u povratku
        X509Certificate2 serverCertificate = new X509Certificate2("P2PChatCert.pfx",
                                                 password: "PeerToPeerChatCertificate");
        NetworkStream netStream = client.GetStream();
        SslStream sslStream = new SslStream(netStream, false);
        IPAddress connected = ((IPEndPoint)client.Client.RemoteEndPoint).Address;
        Console.WriteLine($"Povezan od strane {connected.ToString()}");

        try
        {
            await sslStream.AuthenticateAsServerAsync(
                serverCertificate,
                clientCertificateRequired: true,
                enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
                checkCertificateRevocation: false);

            StreamReader reader = new StreamReader(sslStream);
            //object initializer, postavljamo atribut odma nakon konstruktora
            StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };
            Console.WriteLine("Imamo ssl stream");
            
            //ako neko pokusava da zloupotrebi otvoren port
            //proveravamo da li je zahtev od aplikacije ili ne
            string received = await reader.ReadLineAsync();
            Console.WriteLine($"Primljeno: {received}");
            if(received != REQUEST_STRING && received != REQUEST_CHAT_STRING)
            {
                client.Dispose();
                return;
            }

            await writer.WriteAsync(FilteredData);
            Console.WriteLine($"Postalo {FilteredData}");
            //kad posaljemo nase informacije, isto pitamo za njihove jer smo potvrdili
            //da koriste nas protokol malopre, pa citamo i cuvamo
            char[] buffer = new char[maxSize];
            _ = await reader.ReadAsync(buffer, 0, maxSize); //ostavljamo kolko smo byta procitali je nemamo upotrebu
            string full_response = new string(buffer);
            Console.WriteLine($"Primljeno {full_response}");
            string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
            Korisnik connected_profile = new Korisnik(response);

            Pair<IPAddress, Korisnik> peer = new Pair<IPAddress, Korisnik>(connected, connected_profile);
            SetUpdate(Peers, peer);
            if (received != REQUEST_CHAT_STRING)
            {
                client.Dispose();
                return;
            }
            Form2 form2 = new Form2(reader, writer, this, peer);
            form2.Show();
            form2.BringToFront();
            form2.Focus();

        }
        catch (Exception ex)
        {
            Console.WriteLine($"{connected.ToString()}: {ex.Message}");
        }
    }

    public async Task<HashSet<Pair<IPAddress, Korisnik>>> ScanLocalNet(TextBox textBox, CancellationToken SCancelToken)
    {
        const int maxSize = 2 * 1024 * 1024; //ne prihvata vise od 2mb
        X509Certificate2 clientCertificate = new X509Certificate2("P2PChatCert.pfx",
                                                 password: "PeerToPeerChatCertificate");
        X509CertificateCollection certs = new X509CertificateCollection { clientCertificate };
        while(!SCancelToken.IsCancellationRequested) //zauvek se ponavlja
        for (IPAddress i = NetCalc.IncrementAddress(Mreza.NetworkPrefix);
            NetCalc.isLowerAddress(i, Mreza.Broadcast)
            && !SCancelToken.IsCancellationRequested;
            NetCalc.IncrementAddress(ref i))
        {
            try
            {
                //preskacemo sebe, adresu mreze, i gateway
                if (i.ToString() == Mreza.PrivateIP.ToString() || i.ToString() == Mreza.Gateway.ToString())
                    continue;
                Console.WriteLine($"Pokusavamo {i.ToString()}:{Port.ToString()}");
                textBox.Text = i.ToString();
                TcpClient client = new TcpClient();
                var connectTask = client.ConnectAsync(i, Port);
                var timeoutTask = Task.Delay(1000);

                if (await Task.WhenAny(connectTask, timeoutTask) == connectTask)
                {
                    NetworkStream netStream = client.GetStream();
                    SslStream sslStream = new SslStream(netStream, false,
                        new RemoteCertificateValidationCallback((sender, cert, chain, sslPolicyErrors) => true));
                    //za sigurnost bi korektno bilo => return cert.GetCertHashString() == "...";
                    //ali necemo to da radimo

                    await sslStream.AuthenticateAsClientAsync(
                        targetHost: "P2PChatCert", //mora da se podudara sa DNS name na generisan cert
                        clientCertificates: certs,
                        enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
                        checkCertificateRevocation: false);

                    StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };
                    StreamReader reader = new StreamReader(sslStream);

                    //potvrdjujemo protokol
                    Console.WriteLine($"Saljemo {REQUEST_STRING}");
                    await writer.WriteLineAsync(REQUEST_STRING);
                    //citamo njihove podatke
                    char[] buffer = new char[maxSize];
                    _ = await reader.ReadAsync(buffer, 0, maxSize);
                    string full_response = new string(buffer);
                    string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
                    Console.WriteLine($"Primljeno {full_response}");
                    Korisnik found = new Korisnik(response);
                    //saljemo nase podatke
                    Console.WriteLine($"Saljemo {FilteredData}");
                    await writer.WriteAsync(FilteredData);

                    SetUpdate(Peers, new Pair<IPAddress, Korisnik>(i, found));
                }
                client.Dispose();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{i.ToString()}:{Port.ToString()}, {ex}");
                //brisemo kontakt iz hashseta ako nije uspesna konekcija
                Peers.Remove(new Pair<IPAddress, Korisnik>(i, new Korisnik()));
                continue;
            }
        }
        return Peers;
    }

    public async Task ConnectToPeer(Pair<IPAddress, Korisnik> Peer)
    {
        const int maxSize = 2 * 1024 * 1024;
        X509Certificate2 clientCertificate = new X509Certificate2("P2PChatCert.pfx", "PeerToPeerChatCertificate");
        X509CertificateCollection certs = new X509CertificateCollection { clientCertificate };

        IPAddress ip = Peer.first;
        try
        {
            TcpClient client = new TcpClient();
            await client.ConnectAsync(ip, Port);

            NetworkStream netStream = client.GetStream();
            SslStream sslStream = new SslStream(netStream, false,
                new RemoteCertificateValidationCallback((sender, cert, chain, sslPolicyErrors) => true));
            await sslStream.AuthenticateAsClientAsync(
            targetHost: "P2PChatCert",
            clientCertificates: certs,
            enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
            checkCertificateRevocation: false);

            StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };
            StreamReader reader = new StreamReader(sslStream);

            await writer.WriteLineAsync(REQUEST_CHAT_STRING);

            char[] buffer = new char[maxSize];
            int bytesRead = await reader.ReadAsync(buffer, 0, maxSize);
            string full_response = new string(buffer, 0, bytesRead);
            string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);

            Korisnik found = new Korisnik(response);
            await writer.WriteAsync(FilteredData);

            Pair<IPAddress, Korisnik> peer = new Pair<IPAddress, Korisnik>(ip, found);
            SetUpdate(Peers, peer);
            Form2 form2 = new Form2(reader, writer, this, peer);
            form2.Show();
            form2.BringToFront();
            form2.Focus();
        }
        catch
        {
            MessageBox.Show("Veza nije uspostavljena");
            return;
        }
    }

    #region interface
    public string podrazumevani_fajl { get; set; } = "peer-profil.txt";
    public void Pisi(string put)
    {
        StreamWriter w = new StreamWriter(put);
        w.WriteLine(Korisnik.Ime);
        w.WriteLine(Korisnik.Prezime);
        w.WriteLine(Korisnik.DatumRodjenja.ToString());
        w.WriteLine(Korisnik.Pol);
        w.WriteLine(Korisnik.KorisnickoIme);
        w.WriteLine(Korisnik.Email);
        w.WriteLine(Korisnik.BrojTelefona);
        w.WriteLine(Korisnik.PutDoProfilne);
        w.WriteLine(this.PrivacySettings.ToString());
        w.WriteLine(Mreza.Nic.Name);
        w.Close();
    }
    public void Pisi()
    {
        StreamWriter w = new StreamWriter(podrazumevani_fajl);
        w.WriteLine(Korisnik.Ime);
        w.WriteLine(Korisnik.Prezime);
        w.WriteLine(Korisnik.DatumRodjenja.ToString());
        w.WriteLine(Korisnik.Pol);
        w.WriteLine(Korisnik.KorisnickoIme);
        w.WriteLine(Korisnik.Email);
        w.WriteLine(Korisnik.BrojTelefona);
        w.WriteLine(Korisnik.PutDoProfilne);
        w.WriteLine(this.PrivacySettings.ToString());
        w.WriteLine(Mreza.Nic.Name);
        w.Close();
    }
    public void Citaj(string put)
    {
        StreamReader r = new StreamReader(put);
        string Ime = r.ReadLine();
        string Prezime = r.ReadLine();
        Datum DatumRodjenja = Datum.Parse(r.ReadLine());
        string Pol = r.ReadLine();
        string KorisnickoIme = r.ReadLine();
        string Email = r.ReadLine();
        string BrojTelefona = r.ReadLine();
        string PutDoProfilne = r.ReadLine();
        this.PrivacySettings = byte.Parse(r.ReadLine());
        Mreza = new Mreza(Mreza.NicParse(r.ReadLine()));
        Korisnik = new Korisnik(Ime, Prezime, DatumRodjenja, Pol, KorisnickoIme, Email, BrojTelefona, PutDoProfilne);
        r.Close();
    }
    public void Citaj()
    {
        StreamReader r = new StreamReader(podrazumevani_fajl);
        string Ime = r.ReadLine();
        string Prezime = r.ReadLine();
        Datum DatumRodjenja = Datum.Parse(r.ReadLine());
        string Pol = r.ReadLine();
        string KorisnickoIme = r.ReadLine();
        string Email = r.ReadLine();
        string BrojTelefona = r.ReadLine();
        string PutDoProfilne = r.ReadLine();
        this.PrivacySettings = byte.Parse(r.ReadLine());
        Mreza = new Mreza(Mreza.NicParse(r.ReadLine()));
        Korisnik = new Korisnik(Ime, Prezime, DatumRodjenja, Pol, KorisnickoIme, Email, BrojTelefona, PutDoProfilne);
        r.Close();
    }
    #endregion
}
