using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Security;
using System.IO;
public class Mreza
{
    public Mreza(NetworkInterface nic)
    {
        Nic = nic;
    }
    public Mreza(NetworkInterface nic, IPAddress addr)
    {
        Nic = nic;
        PrivateIP = addr;
    }

    private NetworkInterface nic;
    public NetworkInterface Nic { 
        get { return nic; }
        set
        {
            bool exists = false;
            foreach (var NIC in NetworkInterface.GetAllNetworkInterfaces())
                if (NIC.Id == value.Id)
                {
                    exists = true;
                    break;
                }
            if (!exists)
                throw new ArgumentException("Adapter ne postoji.");
            nic = value;
            GetNicType();
            GetMAC();
        }
    }
    public NetworkInterfaceType NicType { get; private set; }
    public PhysicalAddress MAC { get; private set; }
    private void GetMAC()
    {
        MAC = Nic.GetPhysicalAddress();
    }
    private void GetNicType()
    {
        NicType = Nic.NetworkInterfaceType;
    }

    private IPAddress privateip;
    public IPAddress PrivateIP {
        get { return privateip; }
        set {
            bool exists = false;
            foreach(var addr in Nic.GetIPProperties().UnicastAddresses)
            {
                if(addr.Address == value)
                {
                    exists = true;
                    break;
                }
            }
            if (!exists)
                throw new ArgumentException("Adresa ne postoji za adapter.");

            privateip = value;
            if (PrivateIP.AddressFamily == AddressFamily.InterNetwork)
                isPrivateIPv4 = true;
            else
                isPrivateIPv4 = false;

            GetPublicIP();
            SubnetAndPrefix();
            DefaultGateway();
            GetDHCP();
        } 
    }
    public bool isPrivateIPv4 { get; private set; }
    public IPAddress PublicIP { get; private set; }
    public bool isPublicIPv4 { get; private set; }

    private void GetPublicIP()
    {
        //prvo razresimo ip addr od api-ja
        IPAddress resolved_remote;
        //https://api.ipify.org
        const string PublicIPService = "api.ipify.org";
        try
        {
            IPAddress[] host = Dns.GetHostAddresses(PublicIPService);
            resolved_remote = host[0];
        }
        catch (Exception ex)
        {
            throw new Exception($"Greska pri razresavanju adrese \"{PublicIPService}\". {ex}");
        }
        IPEndPoint local = new IPEndPoint(PrivateIP, 0);
        IPEndPoint remote = new IPEndPoint(resolved_remote, 443); //port 443 za https

        TcpClient client = new TcpClient();

        client.Client.Bind(local);
        client.Connect(remote);
        SslStream sslStream = new SslStream(client.GetStream());
        sslStream.AuthenticateAsClient(PublicIPService);

        string request = $"GET / HTTP/1.1\r\nHost: {PublicIPService}\r\nConnection: close\r\n\r\n";
        byte[] requestBytes = Encoding.ASCII.GetBytes(request);
        sslStream.Write(requestBytes);
        sslStream.Flush();

        StreamReader r = new StreamReader(sslStream, Encoding.ASCII);
        while (!r.EndOfStream)
        {
            //parseujemo liniju po liniju od response za
            //liniju sa ip addresom
            string line = r.ReadLine();
            if(IPAddress.TryParse(line, out IPAddress ip))
            {
                PublicIP = ip;
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                    isPublicIPv4 = true;
                else if (ip.AddressFamily == AddressFamily.InterNetworkV6)
                    isPublicIPv4 = false;
                //Console.WriteLine(line);
                break;
            }
            //Console.WriteLine(line);
        }
        client.Close();
    }

    static public bool isLowerAddress(IPAddress a, IPAddress b)
    {
        byte[] byteArrayA = a.GetAddressBytes();
        byte[] byteArrayB = b.GetAddressBytes();

        for (int i = 0; i < byteArrayA.Length; ++i)
        {
            if (byteArrayA[i] < byteArrayB[i])
                return true;
            if (byteArrayA[i] > byteArrayB[i])
                return false;
        }

        return false;
    }

    public static void IncrementAddress(ref IPAddress ip)
    {
        byte[] bytes = ip.GetAddressBytes();

        for (int i = bytes.Length - 1; i >= 0; i--)
        {
            bytes[i]++;
            if (bytes[i] != 0)
                break;
        }

        ip = new IPAddress(bytes); //updateujemo isti objekat koji smo dobili na ulazu
    }

    public IPAddress Subnet { get; private set; }
    public int PrefixLength { get; private set; }
    private void SubnetAndPrefix()
    {
        if (isPrivateIPv4)
        {
            foreach (UnicastIPAddressInformation unicast1 in Nic.GetIPProperties().UnicastAddresses)
                if (unicast1.Address == PrivateIP)
                {
                    PrefixLength = unicast1.PrefixLength;
                    Subnet = unicast1.IPv4Mask;
                }
        }
        else
        {
            foreach (UnicastIPAddressInformation unicast2 in Nic.GetIPProperties().UnicastAddresses)
                if (unicast2.Address == PrivateIP)
                {
                    PrefixLength = unicast2.PrefixLength;
                    Subnet = new IPAddress(CreateSubnetMaskV6(PrefixLength));
                }
        }
    }
    public static byte[] CreateSubnetMask(int n, bool isIPv4)
    {
        if (isIPv4)
            return CreateSubnetMaskV4(n);
        else
            return CreateSubnetMaskV6(n);
    }

    public static byte[] CreateSubnetMaskV4(int n)
    {
        byte[] bits = new byte[4];

        for (int i = 0; i < n / 8; ++i)
        {
            bits[i] = 0xFF;
        }

        if (n % 8 != 0)
        {
            bits[n / 8] = (byte)(0xFF << (8 - (n % 8)));
        }

        return bits;
    }

    public static byte[] CreateSubnetMaskV6(int n)
    {
        byte[] bits = new byte[16];

        for (int i = 0; i < n / 8; ++i)
        {
            bits[i] = 0xFF;
        }

        if (n % 8 != 0)
        {
            bits[n / 8] = (byte)(0xFF << (8 - (n % 8)));
        }

        return bits;
    }

    public IPAddress NetworkPrefix
    {
        get
        {
                byte[] ip = PrivateIP.GetAddressBytes();
                byte[] mask = Subnet.GetAddressBytes();
                for (int i = 0; i < ip.Length; ++i) //idemo do ip.Length jer se mozda radi o V6
                    ip[i] = (byte)(ip[i] & mask[i]);
                return new IPAddress(ip);
        }
    }

    public IPAddress Broadcast //ustvari je najveca mreza u subnet-u za v6
    {
        get
        {
            byte[] ip = PrivateIP.GetAddressBytes();
            byte[] mask = Subnet.GetAddressBytes();
            for (int i = 0; i < ip.Length; ++i) //idemo do ip.Length jer se mozda radi o V6
                ip[i] = (byte)(ip[i] | (~mask[i]));
            return new IPAddress(ip);
        }
    }

    //ip verzija od gateway isto zavisi od lokalne ip verzije
    public IPAddress Gateway { get; private set; }
    private void DefaultGateway()
    { 
        //moze da pravi problemi ako nic podrzava vise gateway
        //adresa za obe adresne porodice, ali to se nece desiti za 
        //nijedan desktop racunar
        foreach (var gateway in Nic.GetIPProperties().GatewayAddresses)
            if (gateway.Address.AddressFamily == PrivateIP.AddressFamily)
                Gateway = gateway.Address;    
    }

    public bool DHCP { get; private set; }
    private void GetDHCP()
    {
        if (isPrivateIPv4)
            // ?. null-conditional operator, ako GetIPV4... vrati null cela ekspresija
            // postaje null umesto da dobijemo exception
            // ?? null-coalescing operator, ako je ekspresija null, vraca drugu ekspresiju (false)
            DHCP = Nic.GetIPProperties().GetIPv4Properties()?.IsDhcpEnabled ?? false;
        else
            DHCP = false; //C# nema biblioteke koje dozvoljavaju da razresimo ovo za IPv6
    }
}