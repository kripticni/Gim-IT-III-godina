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

//sealed sprecava dalje nasledjivanje
public sealed class Peer : IFajl
{
    public Korisnik Korisnik;
    public Mreza Mreza;
    const int DEFAULT_PORT = 51888;
    const string REQUEST_STRING = "P2PChat Scan Request";
    public int Port { get; private set; }
    public byte PrivacySettings { get; private set; }
    const int IME_BIT = 0;
    const int PREZIME_BIT = 1;
    const int DATUM_BIT = 2;
    const int POL_BIT = 3;
    const int K_IME_BIT = 4;
    const int EMAIL_BIT = 5;
    const int BROJ_BIT = 6;
    const int PROFILNA_BIT = 7;

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
                if (Korisnik.PutDoProfilne != "defaultmalepfp.jpg" && Korisnik.PutDoProfilne != "defaultfemalepfp.jpg")
                    ret += $"Profilna: {Korisnik.EnkodirajBitmapB64(Korisnik.profilna, Korisnik.profilna.RawFormat)}\n";
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
        NetworkStream netStream = client.GetStream();
        SslStream sslStream = new SslStream(netStream, false);
        IPAddress connected = ((IPEndPoint)client.Client.RemoteEndPoint).Address;
        MessageBox.Show($"Povezan od strane {connected.ToString()}");

        try
        {
            X509Certificate2 serverCertificate = new X509Certificate2("P2PChatCert.pfx", 
                                                     password:"PeerToPeerChatCertificate");

            await sslStream.AuthenticateAsServerAsync(
                serverCertificate,
                clientCertificateRequired: true,
                enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
                checkCertificateRevocation: false);

            StreamReader reader = new StreamReader(sslStream);
            //object initializer, postavljamo atribut odma nakon konstruktora
            StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };
            MessageBox.Show("Imamo ssl stream");
            
            //ako neko pokusava da zloupotrebi otvoren port
            //proveravamo da li je zahtev od aplikacije ili ne
            string received = await reader.ReadLineAsync();
            MessageBox.Show($"Primljeno: {received}");
            if(received != REQUEST_STRING)
            {
                client.Dispose();
                return;
            }

            await writer.WriteAsync(FilteredData);
            MessageBox.Show($"Postalo {FilteredData}");
            //kad posaljemo nase informacije, isto pitamo za njihove jer smo potvrdili
            //da koriste nas protokol malopre, pa citamo i cuvamo
            char[] buffer = new char[maxSize];
            _ = await reader.ReadAsync(buffer, 0, maxSize); //ostavljamo kolko smo byta procitali je nemamo upotrebu
            string full_response = new string(buffer);
            MessageBox.Show($"Primljeno {full_response}");
            string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
            Korisnik connected_profile = new Korisnik(response);

            SetUpdate(Peers, new Pair<IPAddress, Korisnik>(connected,connected_profile));
            client.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"{connected.ToString()}: {ex.Message}");
        }
    }


    public async Task<HashSet<Pair<IPAddress,Korisnik>>> ScanLocalNet(CancellationToken SCancelToken)
    {
        const int maxSize = 2 * 1024 * 1024; //ne prihvata vise od 2mb
        X509Certificate2 clientCertificate = new X509Certificate2("P2PChatCert.pfx", 
                                                 password:"PeerToPeerChatCertificate");

        for (IPAddress i = Mreza.NetworkPrefix;
            NetCalc.isLowerAddress(i, Mreza.Broadcast) 
            && !SCancelToken.IsCancellationRequested;
            NetCalc.IncrementAddress(ref i))
        {
            try
            {
                TcpClient client = new TcpClient();
                await client.ConnectAsync(i, Port);

                NetworkStream netStream = client.GetStream();
                SslStream sslStream = new SslStream(netStream, false,
                    new RemoteCertificateValidationCallback((sender, cert, chain, sslPolicyErrors) => true));
                //za sigurnost bi korektno bilo => return cert.GetCertHashString() == "...";
                //ali necemo to da radimo

                X509CertificateCollection certs = new X509CertificateCollection { clientCertificate };

                await sslStream.AuthenticateAsClientAsync(
                targetHost: "P2PChatCert", //mora da se podudara sa DNS name na generisan cert
                clientCertificates: certs,
                enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
                checkCertificateRevocation: false);

                StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };
                StreamReader reader = new StreamReader(sslStream);

                //potvrdjujemo protokol
                await writer.WriteLineAsync(REQUEST_STRING);
                //citamo njihove podatke
                char[] buffer = new char[maxSize];
                _ = await reader.ReadAsync(buffer, 0, maxSize); 
                string full_response = new string(buffer);
                string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
                Korisnik found = new Korisnik(response);
                //saljemo nase podatke
                await writer.WriteAsync(FilteredData);

                Peers.Add(new Pair<IPAddress,Korisnik>(i,found));
                client.Dispose();
            }
            catch
            {
                continue;
            }
        }
        return Peers;
    }

    public async Task<HashSet<Pair<IPAddress, Korisnik>>> ScanLocalNet(TextBox textBox2, CancellationToken SCancelToken)
    {
        const int maxSize = 2 * 1024 * 1024; //ne prihvata vise od 2mb
        X509Certificate2 clientCertificate = new X509Certificate2("P2PChatCert.pfx",
                                                 password: "PeerToPeerChatCertificate");

        for (IPAddress i = Mreza.NetworkPrefix;
            NetCalc.isLowerAddress(i, Mreza.Broadcast)
            && !SCancelToken.IsCancellationRequested;
            NetCalc.IncrementAddress(ref i))
        {
            try
            {
                textBox2.Text = i.ToString();
                TcpClient client = new TcpClient();
                await client.ConnectAsync(i, Port);

                NetworkStream netStream = client.GetStream();
                SslStream sslStream = new SslStream(netStream, false,
                    (sender, certificate, chain, sslPolicyErrors) => true);
                //za sigurnost bi korektno bilo => return cert.GetCertHashString() == "...";
                //ali necemo to da radimo

                X509CertificateCollection certs = new X509CertificateCollection { clientCertificate };

                await sslStream.AuthenticateAsClientAsync(
                targetHost: "P2PChatCert", //mora da se podudara sa DNS name na generisan cert
                clientCertificates: certs,
                enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
                checkCertificateRevocation: false);

                StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };
                StreamReader reader = new StreamReader(sslStream);

                //potvrdjujemo protokol
                await writer.WriteLineAsync(REQUEST_STRING);
                //citamo njihove podatke
                char[] buffer = new char[maxSize];
                _ = await reader.ReadAsync(buffer, 0, maxSize);
                string full_response = new string(buffer);
                string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
                Korisnik found = new Korisnik(response);
                //saljemo nase podatke
                await writer.WriteAsync(FilteredData);

                Peers.Add(new Pair<IPAddress, Korisnik>(i, found));
                client.Dispose(); 
            }   
            catch (Exception ex)
            {
                MessageBox.Show($"{i.ToString()}:{ex}");
                continue;
            }
        }
        return Peers;
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
