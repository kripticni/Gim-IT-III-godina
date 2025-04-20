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

namespace GUI
{

    public partial class UserControl1 : UserControl
    {
        private void fillTextBoxes()
        {
            textBox1.ReadOnly = true;
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
            listener_cts = new CancellationTokenSource();
            portscanner_cts = new CancellationTokenSource();
            timer = new System.Windows.Forms.Timer();
            timer.Interval = 5000;
            timer.Tick += UpdatePeersUI;
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

        private void button1_Click(object sender, EventArgs e)
        {
            panel1.BackColor = Color.Green;
            textBox1.Text = p.ListenerAddressString;
            CancellationToken listener_token = listener_cts.Token;
            _ = p.Listener(listener_token); //salje u background thread
        }

        private void button2_Click(object sender, EventArgs e)
        {
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

        private void button3_Click(object sender, EventArgs e)
        {
            panel2.BackColor = Color.Green;
            CancellationToken portscanner_token = portscanner_cts.Token;
            _ = p.ScanLocalNet(textBox2, portscanner_token); //salje u background thread
        }

        private void button4_Click(object sender, EventArgs e)
        {
            panel2.BackColor = Color.Red;
            portscanner_cts.Cancel(); //zavrsava listener
            textBox2.Text = string.Empty;
        }
    }
}
