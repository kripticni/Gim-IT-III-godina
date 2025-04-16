using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;



public class Sistem
{
    public string Hostname
    {
        get { return System.Net.Dns.GetHostName(); }
    }

    public List<IPAddress> AllPrivateIPs()
    {
        List<IPAddress> list = new List<IPAddress>();
        foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
        {
            IPInterfaceProperties ip = nic.GetIPProperties();
            foreach (UnicastIPAddressInformation address in ip.UnicastAddresses)
                //if (address.Address.AddressFamily == AddressFamily.InterNetwork)
                    list.Add(address.Address);
        }
        return list;
    }
}
