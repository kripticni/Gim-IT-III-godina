using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Messaging;
using System.Net;
using System.Security.Principal;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    public partial class Form2 : Form
    {
        Pair<IPAddress, Korisnik> peer;
        Peer p;
        StreamReader r;
        StreamWriter w;

        public Form2(StreamReader reader, StreamWriter writer, Peer _p, Pair<IPAddress, Korisnik> _peer)
        {
            InitializeComponent();
            peer = _peer;
            p = _p;
            r = reader;
            w = writer;
        }
        private void fillTextBoxes()
        {
            richTextBox1.ReadOnly = true;
            richTextBox3.ReadOnly = true;
            textBox3.ReadOnly = true;
            textBox4.ReadOnly = true;
            textBox5.ReadOnly = true;
            textBox6.ReadOnly = true;
            textBox7.ReadOnly = true;
            textBox8.ReadOnly = true;
            textBox9.ReadOnly = true;
            textBox10.ReadOnly = true;
            richTextBox3.Text = $"{peer.second.PunoIme}/{peer.second.KorisnickoIme} ({peer.second.Starost.ToString()})";
            textBox3.Text = peer.second.Ime;
            textBox4.Text = peer.second.Prezime;
            textBox5.Text = peer.second.DatumRodjenja.ToString();
            textBox6.Text = peer.second.Pol;
            textBox7.Text = peer.second.KorisnickoIme;
            textBox8.Text = peer.second.Email;
            textBox9.Text = peer.second.BrojTelefona;
            textBox10.Text = "Godine: " + peer.second.DatumRodjenja.Starost.ToString();
        }

        CancellationTokenSource handler_cts;
        private void Form2_Load(object sender, EventArgs e)
        {
            this.Icon = new Icon("PeerSpeakV1Icon.ico");
            fillTextBoxes();
            peer.second.postaviProfilnu(pictureBox1);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            handler_cts = new CancellationTokenSource();
            MessageHandler(handler_cts.Token);
        }

        //nema razloga da awaitujemo button1_click ni rtb2_textchanged
        //jer se svakako metode zavrsavaju nakon poziva na posaljiPoruku
        private void button1_Click(object sender, EventArgs e)
        {
            if (richTextBox2.Text != string.Empty)
                _ = posaljiPoruku(richTextBox2.Text + '\n');
        }

        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {
            if (richTextBox2.Text.EndsWith("\n") ||
               richTextBox2.Text.EndsWith("\r"))
                _ = posaljiPoruku(richTextBox2.Text);
        }

        private async Task posaljiPoruku(string poruka)
        {
            string client_poruka = $"{p.Korisnik.KorisnickoIme}: {poruka}";
            richTextBox1.AppendText(client_poruka);
            richTextBox2.Clear();
            richTextBox1.ScrollToCaret();
            try{
                await Peer.SendMessage(w, poruka);
            }
            catch { OnDisconnect(); }
        }

        private async void button2_Click(object sender, EventArgs e)
        {
            string filename;
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Any File|*.*";
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true; //jako bitno da se ne bi promenio pwd
            if (openFileDialog.ShowDialog() == DialogResult.OK)
                filename = openFileDialog.FileName;
            else return;
            await Peer.SendFile(w, filename);
        }

        private async void MessageHandler(CancellationToken token)
        {
            while (!token.IsCancellationRequested)
            {
                Pair<Peer.Status, string> received = await Peer.PacketDispatcher(r, peer);
                if(received.first == Peer.Status.ConnectionClosed || received.first == Peer.Status.BadPacket)
                {
                    OnDisconnect();
                    return;
                }
                if (received.first == Peer.Status.MessageReceived) {
                    richTextBox1.AppendText(received.second);
                    richTextBox1.ScrollToCaret();
                }
                if (received.first == Peer.Status.FileReceived)
                {
                    continue;
                }
                if(received.first == Peer.Status.Success)
                {
                    continue;
                }
            }
        }

        bool closed = false; 
        private bool OnDisconnect()
        {
            if (closed) return true; //ako smo vec zatvorili sa OnFormClosing, samo vratimo
            DialogResult result = MessageBox.Show(
                $"{peer.second.KorisnickoIme}:{peer.first.ToString()} je zatvorio konekciju, zatvorite prozor?",
                "Zatvorena Konekcija",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (result == DialogResult.Yes)
            {
                this.Close();
                return true;
            }
            return false;
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            closed = true; //prakticno lock za OnDisconnect
            handler_cts.Cancel(); //gasimo handler
            try
            {
                r?.Close();
                w?.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Form2 close: {ex.Message}");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            richTextBox1.ResetText();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
