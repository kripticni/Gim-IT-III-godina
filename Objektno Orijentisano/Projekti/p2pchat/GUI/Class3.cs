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

class Mreza
{
    public NetworkInterface Nic { get; set; }


    public Mreza(NetworkInterface nic)
    {
        Nic = nic;
    }

    public string PublicIP { get; private set; }
    public bool isPublicIPv4 { get; private set; }
    private async Task<string> PublicIP_API()
    {
        using (HttpClient client = new HttpClient())
        {
            try
            {
                PublicIP = await client.GetStringAsync("https://api.ipify.org");
                return PublicIP;
            }
            catch
            {
                MessageBox.Show("Greska sa konekcijom.");
                PublicIP = string.Empty;
                return string.Empty;
            }
        }
    }

    public IPAddress PrivateIP { get; private set; }
    public bool isPrivateIPv4 { get; private set; }
    private void PrivateIP_Local()
    {
        foreach (var address in Nic.GetIPProperties().UnicastAddresses)
        {
            if (address.Address.AddressFamily == AddressFamily.InterNetwork)
            { 
                isPrivateIPv4 = true;
            }
            else
            { 
                isPrivateIPv4 = false;
            }
            PrivateIP = address.Address;
        }
    }

    public IPAddress Subnet { get; private set; }
    public int PrefixLength { get; private set; }
    private void SubnetAndPrefix()
    {
        foreach (UnicastIPAddressInformation unicastIPAddressInformation in Nic.GetIPProperties().UnicastAddresses)
            if (unicastIPAddressInformation.Address.AddressFamily == AddressFamily.InterNetwork)
                Subnet = unicastIPAddressInformation.IPv4Mask;
            else if (unicastIPAddressInformation.Address.AddressFamily == AddressFamily.InterNetworkV6)
                PrefixLength = unicastIPAddressInformation.PrefixLength;
    }

    //ip verzija od gateway isto zavisi od lokalne ip verzije
    public IPAddress Gateway { get; private set; }
    private void DefautltGateway()
    {
        if (Nic.OperationalStatus == OperationalStatus.Up)
            foreach (GatewayIPAddressInformation gateway in Nic.GetIPProperties().GatewayAddresses)
                Gateway = gateway.Address;
    }

    private void WriteDHCP()
    {
        foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
            if (nic.OperationalStatus == OperationalStatus.Up)
            {
                bool isDhcpEnabled = nic.GetIPProperties().GetIPv4Properties()?.IsDhcpEnabled ?? false;
                textBox12.Text = isDhcpEnabled ? "Dynamic" : "Static";
            }
    }

    private void WriteMAC() //LINQ, nice
    {
        textBox6.Text = NetworkInterface
        .GetAllNetworkInterfaces()
        .Where(nic => nic.OperationalStatus == OperationalStatus.Up && nic.NetworkInterfaceType != NetworkInterfaceType.Loopback)
        .Select(nic => nic.GetPhysicalAddress().ToString())
        .FirstOrDefault();
    }

    private void WriteAdapterType()
    {
        foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
        {
            string temp = nic.NetworkInterfaceType.ToString();
            if (temp != "Loopback")
                textBox10.Text = temp;
        }
    }

    private void WriteOS()
    {
        textBox9.Multiline = true;
        textBox9.Text = RuntimeInformation.OSDescription;
    }

    private void WritePower()
    {
        PowerStatus ps = SystemInformation.PowerStatus;
        textBox8.Text = Convert.ToString(ps.BatteryLifePercent * 100) + ',' + ps.BatteryChargeStatus.ToString();
    }
}