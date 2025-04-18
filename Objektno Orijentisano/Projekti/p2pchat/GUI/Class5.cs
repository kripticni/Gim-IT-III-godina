using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Net;
public class Peer
{
    private readonly Korisnik Korisnik;
    private readonly Mreza Mreza;
    const int DEFAULT_PORT = 999;


    public async Task<List<IPAddress>> ScanLocalNet(int port)
    {
        List<IPAddress> open = new List<IPAddress>();
        for(IPAddress i = Mreza.NetworkPrefix; 
            Mreza.isLowerAddress(i, Mreza.Broadcast);
            Mreza.IncrementAddress(ref i))
        {
            try
            {
                TcpClient client = new TcpClient();
                await client.ConnectAsync(i, port);
                //nema multithreading da ne bi eksplodirali
                //kompjuteri na vece mreze
                open.Add(i);
            }
            catch
            {
                continue;
            }
        }
        return open;
    }


    //isto samo sto skenira default port koji postavim
    public async Task<List<IPAddress>> ScanLocalNet()
    {
        List<IPAddress> open = new List<IPAddress>();
        for (IPAddress i = Mreza.NetworkPrefix;
            Mreza.isLowerAddress(i, Mreza.Broadcast);
            Mreza.IncrementAddress(ref i))
        {
            try
            {
                TcpClient client = new TcpClient();
                await client.ConnectAsync(i, DEFAULT_PORT);
                open.Add(i);
            }
            catch
            {
                continue;
            }
        }
        return open;
    }
}
