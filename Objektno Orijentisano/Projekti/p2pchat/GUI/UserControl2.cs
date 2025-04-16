using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Net.Http;

namespace GUI
{
    public partial class UserControl2 : UserControl
    {
        private void textBoxReadOnly()
        {
            textBox1.ReadOnly = true;
            textBox2.ReadOnly = true;
            textBox3.ReadOnly = true;
            textBox4.ReadOnly = true;
            textBox5.ReadOnly = true;
            textBox6.ReadOnly = true;
            //textBox7.ReadOnly = true;
            textBox8.ReadOnly = true;
            textBox9.ReadOnly = true;
            textBox10.ReadOnly = true;
            textBox12.ReadOnly = true;
        }
        private void WriteHostname() {
            textBox5.Text = System.Net.Dns.GetHostName();
        }

        async Task<string> WritePublicIP()
        {
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    string ip = await client.GetStringAsync("https://api.ipify.org");
                    textBox1.Text = ip;
                    return ip;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                    return string.Empty;
                }
            }
        }

        private void WritePrivateIP()
        {
            foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
            {
                var ip = nic.GetIPProperties();
                foreach (var address in ip.UnicastAddresses)
                    if (address.Address.AddressFamily == AddressFamily.InterNetwork)
                    {
                        string temp = address.Address.ToString();
                        if (temp == "127.0.0.1")
                            continue;
                        textBox2.Text = temp;
                        break;
                    }
            }
        }


        private void WriteSubnet()
        {
            foreach (NetworkInterface adapter in NetworkInterface.GetAllNetworkInterfaces())
                foreach (UnicastIPAddressInformation unicastIPAddressInformation in adapter.GetIPProperties().UnicastAddresses)
                    if (unicastIPAddressInformation.Address.AddressFamily == AddressFamily.InterNetwork)
                        if (textBox2.Text == unicastIPAddressInformation.Address.ToString())
                            textBox4.Text = unicastIPAddressInformation.IPv4Mask.ToString();
        }

        private void WriteGateway()
        {
            foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
                if (nic.OperationalStatus == OperationalStatus.Up)
                    foreach (GatewayIPAddressInformation gateway in nic.GetIPProperties().GatewayAddresses)
                        textBox3.Text = gateway.Address.ToString();
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

        private void WriteOS() {
            textBox9.Multiline = true;
            textBox9.Text = RuntimeInformation.OSDescription;
        }

        private void WritePower() {
            PowerStatus ps = SystemInformation.PowerStatus;
            textBox8.Text = Convert.ToString(ps.BatteryLifePercent * 100) + ',' + ps.BatteryChargeStatus.ToString();
        }

        private void fillComboBox()
        {
            comboBox1.Items.Clear();
            foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
                comboBox1.Items.Add(nic.Name);
        }

        public UserControl2()
        {
            InitializeComponent();

            textBoxReadOnly();
            fillComboBox();

            WriteHostname();
            WritePublicIP(); //no await, parallel
            WritePrivateIP();
            WriteSubnet();
            WriteGateway();
            WriteDHCP();

            WriteMAC();
            WriteAdapterType();
            WriteOS();
            WritePower();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string adp = comboBox1.SelectedItem.ToString();
            foreach (NetworkInterface nic in NetworkInterface.GetAllNetworkInterfaces())
                if (nic.Name == adp)
                {
                    //update
                    //break;
                }
        }
    }
}
