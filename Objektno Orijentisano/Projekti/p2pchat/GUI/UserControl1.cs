using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace GUI
{

    public partial class UserControl1 : UserControl
    {
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
        }

        private void fillComboBoxes()
        {
            comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
        }

        public UserControl1()
        {
            InitializeComponent();
        }


        CancellationTokenSource listener_cts; //za stopiranje listenera
        CancellationTokenSource portscanner_cts; //za stopiranje skenera
        System.Windows.Forms.Timer timer; //za updateovanje liste
        private void UserControl1_Load(object sender, EventArgs e)
        {
            fillTextBoxes();
            fillComboBoxes();
            listener_cts = new CancellationTokenSource();
            portscanner_cts = new CancellationTokenSource();
            timer = new System.Windows.Forms.Timer();
            timer.Interval = 10000;
            timer.Tick += UpdatePeersUI;
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            //pictureBox1.Image = Image.FromFile("defaultmalepfp.jpg");
            aktivan_listener = false;
            aktivan_skener = false;
        }

        //radimo ovo na visible changed da bi uhvatili
        //dobru referencu na Peer p iz usercontrol2
        bool first_change = false; //da ne bi uhvatili referencu na form_load
        Form1 form;
        Peer p;
        protected override void OnVisibleChanged(EventArgs e)
        {
            //tako da i dalje izvrsimo isti kod koji bi inace izvrsili na onVisibleChanged
            base.OnVisibleChanged(e);
            //Console.WriteLine("aktivirano");
            if (!first_change)
            {
                first_change = true;
                return;
            }
            //Console.WriteLine("proslo");
            
            if (this.Visible)
            {
                form = FindForm() as Form1;
                p = form.UserControl2.p;

                timer.Start();
            }
            else
            {
                timer.Stop();
            }
        }

        bool aktivan_listener;
        private void button1_Click(object sender, EventArgs e)
        {
            //guardujemo da se ne zapocnu vise
            if (aktivan_listener)
                return;
            aktivan_listener = true;
            panel1.BackColor = Color.Green;
            textBox1.Text = p.ListenerAddressString;
            listener_cts = new CancellationTokenSource();
            CancellationToken listener_token = listener_cts.Token;
            _ = p.Listener(listener_token); //salje u background thread
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!aktivan_listener)
                return;
            aktivan_listener = false;
            panel1.BackColor = Color.Red;
            listener_cts.Cancel(); //zavrsava listener
            //TODO: kad se zavrsi koriscenje aplikacije, 
            //svakom iz Peers hashseta salje logoff signal
            //koji ga brise iz hashseta
            textBox1.Text = string.Empty;
        }

        private void UpdatePeersUI(object sender, EventArgs e)
        {
            if (p.Peers == null) return;
            listBox1.Items.Clear();
            comboBox1.Items.Clear();
            foreach(var item in p.Peers)
            {
                string repr = $"{item.first.ToString()}:{item.second.KorisnickoIme}";
                listBox1.Items.Add(repr);
                comboBox1.Items.Add(repr);
            }
        }

        bool aktivan_skener;
        private void button3_Click(object sender, EventArgs e)
        {
            if (aktivan_skener)
                return;
            aktivan_skener = true;
            panel2.BackColor = Color.Green;
            portscanner_cts = new CancellationTokenSource();
            CancellationToken portscanner_token = portscanner_cts.Token;
            _ = p.ScanLocalNet(textBox2, portscanner_token); //salje u background thread
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (!aktivan_skener) 
                return;
            aktivan_skener = false;
            panel2.BackColor = Color.Red;
            portscanner_cts.Cancel(); //zavrsava listener
            textBox2.Text = string.Empty;
        }
        
        private Pair<IPAddress, Korisnik> GetPeer(string str)
        {
            string[] parts = str.Split(new[] { ":" }, StringSplitOptions.None);
            string ipaddr = parts[0];
            IPAddress ip = IPAddress.Parse(ipaddr);
            Pair<IPAddress, Korisnik> peer;
            p.Peers.TryGetValue(new Pair<IPAddress, Korisnik>(ip, new Korisnik()), out peer);
            return peer;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Korisnik profil = GetPeer(comboBox1.SelectedItem.ToString()).second;
            textBox3.Text = profil.Ime;
            textBox4.Text = profil.Prezime;
            textBox5.Text = profil.DatumRodjenja.ToString();
            textBox6.Text = profil.Pol;
            textBox7.Text = profil.KorisnickoIme;
            textBox8.Text = profil.Email;
            textBox9.Text = profil.BrojTelefona;
            textBox10.Text = "Godine: " + profil.DatumRodjenja.Starost.ToString();
            profil.postaviProfilnu(pictureBox1);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if(comboBox1.SelectedItem == null)
            {
                MessageBox.Show("Izaberite iznad osobu sa kojom zelite da se dopisujete");
                return;
            }
            Pair<IPAddress, Korisnik> receiver = GetPeer(comboBox1.SelectedItem.ToString());
            _ = p.ConnectToPeer(receiver); //novi thread za chat gui
        }
    }
}
