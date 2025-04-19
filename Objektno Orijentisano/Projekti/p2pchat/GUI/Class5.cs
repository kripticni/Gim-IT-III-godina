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
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TaskbarClock;

//sealed sprecava dalje nasledjivanje
public sealed class Peer
{
    private readonly Korisnik Korisnik;
    private readonly Mreza Mreza;
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

    public string FilteredData
    {
        get
        {
            string ret = "";
            if (NetCalc.isBitSet(PrivacySettings, IME_BIT)) ret += $"Ime: {Korisnik.Ime}\n";
            if (NetCalc.isBitSet(PrivacySettings, PREZIME_BIT)) ret += $"Prezime: {Korisnik.Prezime}\n";
            if (NetCalc.isBitSet(PrivacySettings, DATUM_BIT)) ret += $"Datum rodjenja: {Korisnik.DatumRodjenja.ToString("dd/mm/yyyy")}\n";
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

    private TcpListener listener;
    private readonly CancellationToken LCancelToken; 
    //koristimo da bi mogli van klasu da napravimo
    //CancellationTokenSource koj ce da kontrolise
    //kolko dugo cemo da skeniramo ili slusamo
    //CancellationTokenSource cts = new...
    //cts.Close() bi zatvorio listener
    private async Task Listener()
    {
        listener = new TcpListener(Mreza.PrivateIP, Port);
        listener.Start();
        while (!LCancelToken.IsCancellationRequested)
        {
            TcpClient client = await listener.AcceptTcpClientAsync();
            _ = RespondInfo(client); //salje u pozadinu i slusa za sledecu konekciju
        }
        listener.Stop();
    }

    private async Task RespondInfo(TcpClient client)
    {
        NetworkStream netStream = client.GetStream();
        SslStream sslStream = new SslStream(netStream, false);

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
            
            //ako neko pokusava da zloupotrebi otvoren port
            //proveravamo da li je zahtev od aplikacije ili ne
            string received = await reader.ReadLineAsync();
            if(received != REQUEST_STRING)
            {
                client.Close();
                return;
            }

            await writer.WriteAsync(FilteredData);
            client.Close();
            //respond with data from privacy settings for scanning
        }
        catch (Exception ex)
        {
            Console.WriteLine($"SSL Error: {ex.Message}");
        }
    }

    private readonly CancellationToken SCancelToken;
    public async Task<List<Pair<IPAddress,Korisnik>>> ScanLocalNet()
    {
        const int maxSize = 2 * 1024 * 1024; //ne prihvata vise od 2mb
        X509Certificate2 clientCertificate = new X509Certificate2("P2PChatCert.pfx", 
                                                 password:"PeerToPeerChatCertificate");

        List<Pair<IPAddress, Korisnik>> open = new List<Pair<IPAddress,Korisnik>>();
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

                await writer.WriteLineAsync(REQUEST_STRING);
                char[] buffer = new char[maxSize];
                _ = await reader.ReadAsync(buffer, 0, maxSize); //ostavljamo kolko smo byta procitali je nemamo upotrebu
                string full_response = new string(buffer);
                string[] response = full_response.Split(new[] { "\r\n", "\n", "\r" }, StringSplitOptions.None);
                Korisnik found = new Korisnik(response);

                open.Add(new Pair<IPAddress,Korisnik>(i,found));
                client.Close();
            }
            catch
            {
                continue;
            }
        }
        return open;
    }
}
