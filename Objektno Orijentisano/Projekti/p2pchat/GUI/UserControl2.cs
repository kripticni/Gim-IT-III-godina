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
        public Peer p { get; private set; } //za mrezu i profil
        private Mreza m; //privremeno
        private Korisnik k; //privremeno

        //da bi mogli da proverimo na form1 button
        public ComboBox ComboBox1{
            get { return comboBox1; }
        }
        public ComboBox ComboBox2
        {
            get { return comboBox2; }
        }


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
            comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;

            comboBox3.Items.Clear();
            comboBox3.Items.Add("Musko");
            comboBox3.Items.Add("Zensko");

            comboBox1.Items.Clear();
            foreach (NetworkInterface I in interfaces)
                comboBox1.Items.Add(I.Name);
        }

        private void fillListCheckBoxes() {
            for (int i = 0; i < checkedListBox1.Items.Count; ++i)
                    checkedListBox1.SetItemChecked(i, true);
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
            if (p != null)
                if(p.Mreza != null)
                    p.Mreza.PrivateIP = m.PrivateIP;
        }


        public UserControl2()
        {
            InitializeComponent();
        }

        private void UserControl2_Load(object sender, EventArgs e)
        {
            fillTextBoxes();
            fillComboBoxes();
            fillListCheckBoxes();

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
                if (Korisnik.validnaSlika(textBox16.Text))
                {
                    textBox16.Text = openFileDialog.FileName;
                    pictureBox1.Image = Image.FromFile(textBox16.Text);
                }
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
            k = new Korisnik(textBox12.Text, textBox13.Text, Datum.Parse(maskedTextBox1.Text),
                            comboBox3.SelectedItem.ToString(), textBox14.Text, textBox15.Text, maskedTextBox2.Text,
                            textBox16.Text);
            m = new Mreza(Mreza.NicParse(comboBox1.SelectedItem.ToString()), IPAddress.Parse(comboBox2.SelectedItem.ToString()));
            p = new Peer(k, m, ParseCheckedListBox());

            p.Pisi(textBox17.Text); //cuvamo u fajl
            UcitajPeer(); //ucitavamo da bi napravili peer-a
        }

        private byte ParseCheckedListBox()
        {
            byte PrivacySettings = new byte();
            for (int i = 0; i < checkedListBox1.Items.Count; ++i)
            {
                if(checkedListBox1.GetItemChecked(i))
                {
                    PrivacySettings = NetCalc.SetBit(PrivacySettings, i);
                }
            }
            return PrivacySettings;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            UcitajPeer();
        }

        private void UcitajPeer()
        {
            p = new Peer(textBox17.Text);
            if(comboBox2.SelectedItem != null)
                p.Mreza.PrivateIP = IPAddress.Parse(comboBox2.SelectedItem.ToString());
            textBox12.Text = p.Korisnik.Ime;
            textBox13.Text = p.Korisnik.Prezime;
            maskedTextBox1.Text = p.Korisnik.DatumRodjenja.ToString();
            comboBox3.SelectedItem = p.Korisnik.Pol;
            textBox14.Text = p.Korisnik.KorisnickoIme;
            textBox15.Text = p.Korisnik.Email;
            maskedTextBox2.Text = p.Korisnik.BrojTelefona;
            textBox16.Text = p.Korisnik.PutDoProfilne;
            p.Korisnik.postaviProfilnu(pictureBox1);
            postaviCheckListbox(p);
            comboBox1.SelectedItem = p.Mreza.Nic.Name;
        }

        private void postaviCheckListbox(Peer p)
        {
            for (int i = 0; i < checkedListBox1.Items.Count; i++)
            {
                if (NetCalc.isBitSet(p.PrivacySettings, i))
                {
                    checkedListBox1.SetItemChecked(i, true);
                }
                else
                {
                    checkedListBox1.SetItemChecked(i, false);
                }
            }
        }


    }
}
