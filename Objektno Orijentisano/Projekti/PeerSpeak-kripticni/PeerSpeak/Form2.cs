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
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

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

        private void Form2_Load(object sender, EventArgs e)
        {
            this.Icon = new Icon("PeerSpeakV1Icon.ico");
            fillTextBoxes();
            peer.second.postaviProfilnu(pictureBox1);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            MessageHandler();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (richTextBox2.Text != string.Empty)
                posaljiPoruku(richTextBox2.Text + '\n');
        }

        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {
            if (richTextBox2.Text.EndsWith("\n") ||
               richTextBox2.Text.EndsWith("\r"))
                posaljiPoruku(richTextBox2.Text);
        }

        private void posaljiPoruku(string poruka)
        {
            string client_poruka = $"{p.Korisnik.KorisnickoIme}: {poruka}";
            richTextBox1.AppendText(client_poruka);
            richTextBox2.Clear();
            richTextBox1.ScrollToCaret();
            try{ 
                w.WriteAsync($"{Peer.MESSAGE_HEADER}{poruka}");
                Console.Write($"Poslato: {Peer.MESSAGE_HEADER}{poruka}");
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
            byte[] bytes = File.ReadAllBytes(filename);
            string b64_file = Convert.ToBase64String(bytes);
            await w.WriteLineAsync($"{Peer.FILE_HEADER}{Path.GetFileName(filename)}:{b64_file}");
        }

        private async void MessageHandler()
        {
            while (true)
            {
                string message;
                message = string.Empty;
                try
                {
                    message = await r.ReadLineAsync();
                    Console.WriteLine($"Primljeno: {message}");
                }
                catch { if (OnDisconnect() == true) return; }
                if (message == string.Empty)
                    continue;
                if (message == null)
                    if (OnDisconnect() == true) return;
                if (message.StartsWith(Peer.MESSAGE_HEADER))
                {
                    message = message.Substring(Peer.MESSAGE_HEADER.Length);
                    richTextBox1.AppendText(peer.second.KorisnickoIme + ": " + message + '\n');
                    richTextBox1.ScrollToCaret();
                }
                if (message.StartsWith(Peer.FILE_HEADER))
                {
                    string filename_b64file = message.Substring(Peer.FILE_HEADER.Length);
                    int separator_index = filename_b64file.IndexOf(":");
                    string filename = filename_b64file.Substring(0, separator_index);
                    string b64_file = filename_b64file.Substring(separator_index + 1);
                    MessageBox.Show($"Primljen fajl {Path.GetFileName(filename)}");
                    byte[] bytes = Convert.FromBase64String(b64_file);
                    string dirname = "PrimljeniFajlovi";
                    string destination = $"{dirname}/{Path.GetFileName(filename)}";
                    if(!File.Exists(destination))
                        File.WriteAllBytes(destination, bytes);
                    else
                    {
                        string name = Path.GetFileNameWithoutExtension(destination);
                        string extension = Path.GetExtension(destination);
                        int counter = 1;
                        string newpath = $"{dirname}/{name}({counter}){extension}";
                        while (File.Exists(newpath))
                        {
                            ++counter;
                            newpath = $"{dirname}/{name}({counter}){extension}";
                        }
                        File.WriteAllBytes(newpath, bytes);
                    }
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
    }
}
