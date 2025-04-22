using System;
using System.Text;
using System.Linq;
using System.Net;
using System.Net.Sockets;

class Program
{
  public static async Task Main(string[] args){ //necessary async Task for socket/network ops
    Console.Write("Enter ip addr: ");
    string ip_in = "";

    bool check = true;
    do{
      try { 
        check = true;
        string? input = Console.ReadLine();
        if(!string.IsNullOrEmpty(input) && input.Length < 16 && input.Count(c => c == '.') == 3)
          //count goes over each character and the lambda checks if its '.', like python map
          ip_in = new string(input);
        else
          throw new Exception("Invalid input");
        check = false;
      }
      catch {
        Console.Write("Not a valid ip, try again: ");
        continue;
      }
    }while(check);

    Console.Write("Enter port number: ");
    UInt16 port = Convert.ToUInt16(Console.ReadLine());
    
    Console.Write($"Connecting to {ip_in}:{port} ...");

    try {
      IPAddress ip = IPAddress.Parse(ip_in);
      IPEndPoint endpoint = new(ip,port);

      using Socket client = new(//for autodisposal at end of block
        endpoint.AddressFamily, //takes ipv4 from endpoint ip version
        SocketType.Stream, 
        ProtocolType.Tcp); //makes tcp

     await client.ConnectAsync(endpoint);
     while(true){
      string message = "C# socket connection test. <|EOM|>";
      byte[] message_bytes = Encoding.UTF8.GetBytes(message);
      _ = await client.SendAsync(message_bytes, SocketFlags.None);

      byte[] buffer = new byte[1024];
      var received = await client.ReceiveAsync(buffer, SocketFlags.None);
      string response = Encoding.UTF8.GetString(buffer);

      Console.WriteLine(response);
     }
    }
    catch {
      Console.Write("Not connected, error");
      return;
    }
  }
}
