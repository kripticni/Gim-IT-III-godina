using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
public static class NetCalc
{
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

    public static IPAddress IncrementAddress(IPAddress ip)
    {
        byte[] bytes = ip.GetAddressBytes();

        for (int i = bytes.Length - 1; i >= 0; --i)
        {
            ++bytes[i];
            if (bytes[i] != 0)
                break;
        }

        return new IPAddress(bytes);
    }

    public static void IncrementAddress(ref IPAddress ip)
    {
        byte[] bytes = ip.GetAddressBytes();

        for (int i = bytes.Length - 1; i >= 0; --i)
        {
            ++bytes[i];
            if (bytes[i] != 0)
                break;
        }

        ip = new IPAddress(bytes); //updateujemo isti objekat koji smo dobili na ulazu
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

    public static IPAddress LowestAddressInNet(IPAddress ipAddress, IPAddress SubnetMask)
    {
        byte[] ip = ipAddress.GetAddressBytes();
        byte[] mask = SubnetMask.GetAddressBytes();
        for (int i = 0; i < ip.Length; ++i) //idemo do ip.Length jer se mozda radi o V6
            ip[i] = (byte)(ip[i] & mask[i]);
        return new IPAddress(ip);
    }

    public static IPAddress HighestAddressInNet(IPAddress ipAddress, IPAddress SubnetMask)
    {
        byte[] ip = ipAddress.GetAddressBytes();
        byte[] mask = SubnetMask.GetAddressBytes();
        for (int i = 0; i < ip.Length; ++i) //idemo do ip.Length jer se mozda radi o V6
            ip[i] = (byte)(ip[i] | (~mask[i]));
        return new IPAddress(ip);
    }

    public static bool isBitSet(byte b, int n)
    {
        return (b & (1 << n)) != 0;
    }
}
