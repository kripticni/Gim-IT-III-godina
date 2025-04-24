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
using GUI;
using System.Net.NetworkInformation;
using System.Messaging;

//sealed sprecava dalje nasledjivanje
public sealed class Peer : IFajl
{
    public Korisnik Korisnik;
    public Mreza Mreza;
    const int DEFAULT_PORT = 51888;
    public static readonly string REQUEST_SCAN = "P2PChat Scan Request";
    public static readonly string REQUEST_CHAT = "P2PChat Initiate Chat";
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

    public enum Status
    {
        Success,
        ProtocolUnconfirmed,
        DataExchanged,
        ConnectionClosed,
        ChatRequest,
        MessageReceived,
        FileReceived,
        BadPacket
    }

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

    public static Pair<IPAddress, Korisnik> MakePeer(IPAddress ip, Korisnik k)
    {
        return new Pair<IPAddress, Korisnik>(ip, k);
    }
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
        TcpListener listener = new TcpListener(Mreza.PrivateIP, Port);
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
                    //multithreadujemo da bi mogli da obradimo vise konekcija odjednom
                }
                else
                {
                    break;
                }
            }
        }
        catch (OperationCanceledException)
        {
            //nista
        }
        finally
        {
            listener.Stop(); //u oba slucaja gasimo
        }
    }

    private async Task RespondInfo(TcpClient client)
    {
        
        IPAddress connected = ((IPEndPoint)client.Client.RemoteEndPoint).Address;
        Console.WriteLine($"Povezan od strane {connected.ToString()}");

        try
        {
            Pair<StreamReader,StreamWriter> rw_ssl = await GetServerSSl(client);
            StreamReader reader = rw_ssl.first;
            StreamWriter writer = rw_ssl.second;

            Pair<Status,Korisnik> response = await ServerHandshake(reader, writer);
            if (response.first == Status.ProtocolUnconfirmed)
                return;

            Pair<IPAddress, Korisnik> peer = new Pair<IPAddress, Korisnik>(connected, response.second);
            SetUpdate(Peers, peer);

            if (response.first == Status.DataExchanged)
                return;

            if(response.first == Status.ChatRequest)
                StartChat(reader, writer, this, peer);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"{connected.ToString()}: {ex.Message}");
        }
    }

    private async Task<Pair<StreamReader, StreamWriter>> GetServerSSl(TcpClient client)
    {
        NetworkStream netStream = client.GetStream();
        SslStream sslStream = new SslStream(netStream, false);
        try
        {
            X509Certificate2 serverCertificate = new X509Certificate2("P2PChatCert.pfx",
                                                 password: "PeerToPeerChatCertificate");
            await sslStream.AuthenticateAsServerAsync(
                serverCertificate,
                clientCertificateRequired: true,
                enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
                checkCertificateRevocation: false);
        }
        catch
        {
            throw new Exception("Client nije autentifikovao ssl certifikat.");
        }
        //object initializer, postavljamo atribut odma nakon konstruktora
        StreamReader reader = new StreamReader(sslStream);
        StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };
        Console.WriteLine("Imamo ssl stream");
        return new Pair<StreamReader,StreamWriter>(reader, writer);
    }

    private async Task<Pair<Status,Korisnik>> ServerHandshake(StreamReader r, StreamWriter w)
    {
        string received = await r.ReadLineAsync();
        Console.WriteLine($"Primljeno: {received}");
        if (received != REQUEST_SCAN && received != REQUEST_CHAT)
            return new Pair<Status, Korisnik>(Status.ProtocolUnconfirmed, null);

        Korisnik connected_profile;
        try
        {
            connected_profile = await SendAndReceive(r, w);
        }
        catch
        {
            return new Pair<Status, Korisnik>(Status.ConnectionClosed, null);
        }
        if (received == REQUEST_CHAT)
            return new Pair<Status, Korisnik>(Status.ChatRequest, connected_profile);
        else return new Pair<Status, Korisnik>(Status.DataExchanged, connected_profile);
    }

    private async Task<Korisnik> SendAndReceive(StreamReader r, StreamWriter w)
    {
        const int maxSize = 2 * 1024 * 1024; //ne prihavata vise od 2mb u povratku
        //ako neko pokusava da zloupotrebi otvoren port
        //proveravamo da li je zahtev od aplikacije ili ne
        await w.WriteAsync(FilteredData);
        Console.WriteLine($"Postalo {FilteredData}");

        //kad posaljemo nase informacije, isto pitamo za njihove jer smo potvrdili
        //da koriste nas protokol malopre, pa citamo i cuvamo
        char[] buffer = new char[maxSize];
        _ = await r.ReadAsync(buffer, 0, maxSize); //ostavljamo kolko smo byta procitali je nemamo upotrebu
        string full_response = new string(buffer);
        string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
        Korisnik connected_profile = new Korisnik(response);
        Console.WriteLine($"Primljeno {full_response}");

        return connected_profile;
    }

    public async Task<HashSet<Pair<IPAddress, Korisnik>>> ScanLocalNet(TextBox textBox, CancellationToken SCancelToken)
    {
        TcpClient client = new TcpClient(); //promenjiva za povezivanje
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

                    client = new TcpClient();
                    var connectTask = client.ConnectAsync(i, Port);
                    var timeoutTask = Task.Delay(500);

                    if (await Task.WhenAny(connectTask, timeoutTask) == connectTask)
                    {
                        Pair<StreamReader, StreamWriter> rw_ssl = await GetClientSSL(client);
                        StreamReader reader = rw_ssl.first;
                        StreamWriter writer = rw_ssl.second;

                        Korisnik found = await ClientHandshake(reader, writer);
                        SetUpdate(Peers, new Pair<IPAddress, Korisnik>(i, found));
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"{i.ToString()}:{Port.ToString()}, {ex}");
                    //brisemo kontakt iz hashseta ako nije uspesna konekcija
                    Peers.Remove(new Pair<IPAddress, Korisnik>(i, new Korisnik()));
                }
                finally
                {
                    client.Dispose();
                }
        }
        return Peers;
    }

    private async Task<Pair<StreamReader,StreamWriter>> GetClientSSL(TcpClient client)
    {
        NetworkStream netStream = client.GetStream();
        SslStream sslStream = new SslStream(netStream, false,
            new RemoteCertificateValidationCallback((sender, cert, chain, sslPolicyErrors) => true));
        //za sigurnost bi korektno bilo => return cert.GetCertHashString() == "...";
        //ali necemo to da radimo

        try
        {
            X509Certificate2 clientCertificate = new X509Certificate2("P2PChatCert.pfx",
                                                 password: "PeerToPeerChatCertificate");
            X509CertificateCollection certs = new X509CertificateCollection { clientCertificate };
            await sslStream.AuthenticateAsClientAsync(
                targetHost: "P2PChatCert", //mora da se podudara sa DNS name na generisan cert
                clientCertificates: certs,
                enabledSslProtocols: System.Security.Authentication.SslProtocols.Tls12,
                checkCertificateRevocation: false);
        }
        catch
        {
            throw new Exception("Client se nije autentifikovao ili nije prihvatio nasu.");
        }

        StreamReader reader = new StreamReader(sslStream);
        StreamWriter writer = new StreamWriter(sslStream) { AutoFlush = true };

        return new Pair<StreamReader, StreamWriter>(reader, writer);
    }

    private async Task<Korisnik> ClientHandshake(StreamReader r, StreamWriter w)
    {
        //potvrdjujemo protokol
        Console.WriteLine($"Saljemo {REQUEST_SCAN}");
        await w.WriteLineAsync(REQUEST_SCAN);
        //citamo njihove podatke

        Korisnik found = await ReceiveAndSend(r, w);
        return found;
    }

    private async Task<Korisnik> ReceiveAndSend(StreamReader r, StreamWriter w)
    {
        const int maxSize = 2 * 1024 * 1024; //ne prihvata vise od 2mb

        //primamo
        char[] buffer = new char[maxSize];
        _ = await r.ReadAsync(buffer, 0, maxSize);
        string full_response = new string(buffer);
        string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
        Korisnik found = new Korisnik(response);
        Console.WriteLine($"Primljeno {full_response}");

        //saljemo nase podatke
        Console.WriteLine($"Saljemo {FilteredData}");
        await w.WriteAsync(FilteredData);

        return found;
    }

    public async Task ConnectToPeer(Pair<IPAddress, Korisnik> Peer)
    {
        IPAddress ip = Peer.first;
        TcpClient client = new TcpClient();
        try
        {
            await client.ConnectAsync(ip, Port);

            Pair<StreamReader, StreamWriter> rw_ssl = await GetClientSSL(client);
            StreamReader reader = rw_ssl.first;
            StreamWriter writer = rw_ssl.second;

            await writer.WriteLineAsync(REQUEST_CHAT);
            Korisnik found = await ReceiveAndSend(reader, writer);

            Pair<IPAddress, Korisnik> peer = new Pair<IPAddress, Korisnik>(ip, found);
            SetUpdate(Peers, peer);
            StartChat(reader, writer, this, peer);
        }
        catch
        {
            MessageBox.Show("Veza nije uspostavljena");
            return;
        }
    }

    private void StartChat(StreamReader r, StreamWriter w, Peer self, Pair<IPAddress, Korisnik> peer)
    {
        Form2 form2 = new Form2(r, w, this, peer);
        form2.Show();
        form2.BringToFront();
        form2.Focus();
    }

    //sto se tice slanja, ne mozemo da cuvamo
    //streamwriter-e, streamreader-e, netstreamove
    //zajedno kao atribut klase jer zelimo da iz jednog
    //objekta imamo vise uspostavljenih konekcija koje generisemo
    //pa ce za funkcije za slanje i primanje preko uspostavljene
    //veze biti static i zahteva argumente reader/writer

    public static async Task SendFile(StreamWriter w, string path)
    {
        string b64_file = Convert.ToBase64String(File.ReadAllBytes(path));
        await w.WriteLineAsync($"{Peer.FILE_HEADER}{Path.GetFileName(path)}:{b64_file}");
    }

    public static async Task SendMessage(StreamWriter w, string msg)
    {
        await w.WriteAsync($"{Peer.MESSAGE_HEADER}{msg}");
        Console.Write($"Poslato: {Peer.MESSAGE_HEADER}{msg}");
    }

    public static async Task<Pair<Status,string>> PacketDispatcher(StreamReader r, Pair<IPAddress,Korisnik> peer)
    {
        string message = string.Empty;
        try
        {
            message = await r.ReadLineAsync();
            Console.WriteLine($"Primljeno: {message}");
        }
        catch { return new Pair<Status,string>(Status.ConnectionClosed, string.Empty); }

        if (message == string.Empty) //ovo se prakticno nikad nece desiti ali ako se desi je okej
            return new Pair<Status, string>(Status.Success, string.Empty);
        if (message == null) //ovde se jedino desava null ako readlineasync dobije kraj konekcije, pa gasimo
            return new Pair<Status, string>(Status.ConnectionClosed, string.Empty);

        if (message.StartsWith(Peer.MESSAGE_HEADER))
        {
            string handled_msg = HandleMessage(peer.second, message);
            return new Pair<Status, string>(Status.MessageReceived, handled_msg);
        }
        if (message.StartsWith(Peer.FILE_HEADER))
        {
            HandleFile(message);
            return new Pair<Status, string>(Status.FileReceived, string.Empty);
        }
        return new Pair<Status, string>(Status.BadPacket, string.Empty);
    }

    public static string HandleMessage(Korisnik k, string msg)
    {
        msg = msg.Substring(Peer.MESSAGE_HEADER.Length);
        return k.KorisnickoIme + ": " + msg + '\n';
    }

    public static void HandleFile(string msg)
    {
        string filename_b64file = msg.Substring(Peer.FILE_HEADER.Length);
        //ako je put sa folderima, izbacujemo sve osim imena fajla, ako to ne uradimo
        //dozvoljavamo da se sacuva i overwrite-uje fajl bilo gde na celom filesystem-u
        int separator_index = filename_b64file.IndexOf(":"); //delimo na filename i b64file
        string filename = Path.GetFileName(filename_b64file.Substring(0, separator_index));
        string b64_file = filename_b64file.Substring(separator_index + 1);

        MessageBox.Show($"Primljen fajl {filename}");
        byte[] file_bytes = Convert.FromBase64String(b64_file);
        string dirname = "PrimljeniFajlovi";
        string destination = ResolveNameCollision(dirname,filename);

        File.WriteAllBytes(destination, file_bytes);
    }

    public static string ResolveNameCollision(string dirname, string basename)
    {
        if (!File.Exists($"{dirname}/{basename}"))
            return $"{dirname}/{basename}";
        
        string name = Path.GetFileNameWithoutExtension(basename);
        string extension = Path.GetExtension(basename);
        int counter = 1;
        string new_filename = $"{dirname}/{name}({counter}){extension}";
        while (File.Exists(new_filename))
        {
            ++counter;
            new_filename = $"{dirname}/{name}({counter}){extension}";
        }
        return new_filename;
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
        w.WriteLine(Mreza.PrivateIP.ToString()); //soft checkujemo da li postoji
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
        w.WriteLine(Mreza.PrivateIP.ToString());
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
        NetworkInterface nic = Mreza.NicParse(r.ReadLine());
        IPAddress privateip = IPAddress.Parse(r.ReadLine());
        Mreza = new Mreza(nic);
        try { Mreza.PrivateIP = privateip; } //verovatno se je promenio pa try catchujemo
        catch { MessageBox.Show("IP adresa se je promenila od proslog koriscenja, izaberite korektnu u configure."); }  
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
        NetworkInterface nic = Mreza.NicParse(r.ReadLine());
        IPAddress privateip = IPAddress.Parse(r.ReadLine());
        Mreza = new Mreza(nic);
        try { Mreza.PrivateIP = privateip; } //verovatno se je promenio pa try catchujemo
        catch { MessageBox.Show("IP adresa se je promenila od proslog koriscenja, izaberite korektnu u configure."); }
        Korisnik = new Korisnik(Ime, Prezime, DatumRodjenja, Pol, KorisnickoIme, Email, BrojTelefona, PutDoProfilne);
        r.Close();
    }
    #endregion
}
