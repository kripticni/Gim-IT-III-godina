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
using System.Globalization;

namespace GUI
{
    public partial class UserControl2 : UserControl
    {
        Mreza m; // Klasa za sve mrezne operacije
        Korisnik k; // Za profil
        private void fillTextBoxes()
        {
            textBox1.ReadOnly = true;
            textBox2.ReadOnly = true;
            textBox3.ReadOnly = true;
            textBox4.ReadOnly = true;
            textBox5.ReadOnly = true;
            textBox6.ReadOnly = true;
            textBox7.ReadOnly = true;
            textBox8.ReadOnly = true;
            textBox9.ReadOnly = true;
            textBox10.ReadOnly = true;
            textBox11.ReadOnly = true;
            
            textBox1.Text = Sistem.OS;
            textBox2.Text = Sistem.Hostname;
            textBox3.Text = Sistem.BatteryPercent;
            textBox4.Text = Sistem.ChargeStatus;
            textBox16.Text = "defaultmalepfp.jpg";
            textBox17.Text = "korisnik.txt";
        }

        List<NetworkInterface> interfaces = NetworkInterface.GetAllNetworkInterfaces().ToList();
        private void fillComboBoxes()
        {
            comboBox3.Items.Clear();
            comboBox3.Items.Add("Musko");
            comboBox3.Items.Add("Zensko");

            comboBox1.Items.Clear();
            foreach (NetworkInterface I in interfaces)
                comboBox1.Items.Add(I.Name);
        }

        List<IPAddress> AddressesForNic = new List<IPAddress>();
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            NetworkInterface nic = interfaces[comboBox1.SelectedIndex];
            comboBox2.Items.Clear();
            comboBox2.Text = string.Empty;
            comboBox2.SelectedIndex = -1; //resetujemo
            AddressesForNic.Clear();
            foreach (var address in nic.GetIPProperties().UnicastAddresses)
            {
                comboBox2.Items.Add(address.Address.ToString());
                AddressesForNic.Add(address.Address);
            }


            m = new Mreza(nic);
            textBox5.Text = m.MAC.ToString();
            textBox6.Text = m.NicType.ToString();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            IPAddress addr = AddressesForNic[comboBox2.SelectedIndex];
            m.PrivateIP = addr;
            textBox7.Text = m.PublicIP.ToString();
            textBox8.Text = m.PrivateIP.ToString();
            textBox9.Text = m.Gateway.ToString();
            textBox10.Text = m.Subnet.ToString();
            textBox11.Text = m.DHCP.ToString();
        }


        public UserControl2()
        {
            InitializeComponent();

            fillTextBoxes();
            fillComboBoxes();

            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.Image = Image.FromFile("defaultmalepfp.jpg");
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (textBox16.Text == "defaultmalepfp.jpg" || textBox16.Text == "defaultfemalepfp.jpg")
            {
                if (comboBox3.SelectedItem.ToString() == "Musko")
                {
                    textBox16.Text = "defaultmalepfp.jpg";
                    pictureBox1.Image = Image.FromFile("defaultmalepfp.jpg");
                }
                else
                {
                    textBox16.Text = "defaultfemalepfp.jpg";
                    pictureBox1.Image = Image.FromFile("defaultfemalepfp.jpg");
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image Files|*.bmp;*.jpg;*.jpeg;*.png;*.gif;*.tiff;*.tif;*.ico";
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                textBox16.Text = openFileDialog.FileName;
                pictureBox1.Image = Image.FromFile(textBox16.Text);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Text Files|*.txt";
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true; //jako bitno da se ne bi promenio pwd
            if (openFileDialog.ShowDialog() == DialogResult.OK)
                textBox17.Text = openFileDialog.FileName;
        }

        //ime, prezime, datum, pol, korisnicko ime, email, broj telefona, put do slike
        private void button3_Click(object sender, EventArgs e)
        {
            k = new Korisnik(textBox12.Text, textBox13.Text, DateTime.ParseExact(maskedTextBox1.Text, "dd/mm/yyyy", CultureInfo.InvariantCulture),
                            comboBox3.SelectedItem.ToString(), textBox14.Text, textBox15.Text, maskedTextBox2.Text,
                            textBox16.Text);
            
            k.Pisi(textBox17.Text); //cuvamo u fajl
        }

        private void button4_Click(object sender, EventArgs e)
        {
            k = new Korisnik(textBox17.Text);
            textBox12.Text = k.Ime;
            textBox13.Text = k.Prezime;
            maskedTextBox1.Text = k.DatumRodjenja.ToString("/dd/mm/yyyy");
            comboBox3.SelectedItem = k.Pol;
            textBox14.Text = k.KorisnickoIme;
            textBox15.Text = k.Email;
            maskedTextBox2.Text = k.BrojTelefona;
            textBox16.Text = k.PutDoProfilne;
        }
    }
}
