using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

public static class Sistem
{
    static public string OS
    {
        get { return RuntimeInformation.OSDescription; }
    }

    static public string Hostname
    {
        get { return System.Net.Dns.GetHostName(); }
    }

    static public string BatteryPercent
    {
        get {
            PowerStatus ps = SystemInformation.PowerStatus;
            return Convert.ToString(ps.BatteryLifePercent * 100);
        }
    }
    static public string ChargeStatus
    {
        get {
            PowerStatus ps = SystemInformation.PowerStatus;
            return ps.BatteryChargeStatus.ToString(); 
        }
    }
    
    public static List<IPAddress> AllPrivateIPs()
    {
        List<IPAddress> list = new List<IPAddress>();
        foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
            foreach (UnicastIPAddressInformation address in nic.GetIPProperties().UnicastAddresses)
                    list.Add(address.Address);
        return list;
    }

    public static List<IPAddress> AllPrivateIPv4()
    {
        List<IPAddress> list = new List<IPAddress>();
        foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
            foreach (UnicastIPAddressInformation address in nic.GetIPProperties().UnicastAddresses)
                if(address.Address.AddressFamily == AddressFamily.InterNetwork)
                    list.Add(address.Address);
        return list;
    }

    public static List<IPAddress> AllPrivateIPv6()
    {
        List<IPAddress> list = new List<IPAddress>();
        foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
            foreach (UnicastIPAddressInformation address in nic.GetIPProperties().UnicastAddresses)
                if (address.Address.AddressFamily == AddressFamily.InterNetworkV6)
                    list.Add(address.Address);
        return list;
    }

    public static async Task<string> MainPublicIP()
    {
        using (HttpClient client = new HttpClient())
        {
            try
            {
                return await client.GetStringAsync("https://api.ipify.org");
            }
            catch
            {
                MessageBox.Show("Greska sa konekcijom.");
                return string.Empty;
            }
        }
    }
}
