using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace projekat_IgraHvatanja
{
    public partial class Form1 : Form
    {
        Random r = new Random();
        List<Predmet> predmeti = new List<Predmet>();
        Timer t = new Timer();

        int korpaX;
        int korpaY;
        int korpaSirina;
        int korpaVisina = 20;
        bool gameStarted = false;

        int poeni = 0;
        int zivoti = 3;

        public Form1()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
            korpaY = this.ClientSize.Height - korpaVisina - 10;
            korpaX = this.ClientSize.Width / 2 - korpaSirina / 2;
            t.Tick += timer1_Tick;
            t.Start();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (gameStarted)
            {
                if (r.Next(0, 10) < 2)
                    DodajPredmet();
                for (int i = predmeti.Count - 1; i >= 0; i--)
                {
                    predmeti[i].Pomeri();

                    if (predmeti[i].SudarSa(korpaX, korpaY, korpaSirina, korpaVisina))
                    {
                        if (predmeti[i] is Jabuka || predmeti[i] is Pomorandza)
                            poeni++;
                        else if (predmeti[i] is Bomba)
                            zivoti--;

                        predmeti.RemoveAt(i);
                    }
                    else if (predmeti[i].Y > this.ClientSize.Height)
                    {
                        predmeti.RemoveAt(i);
                    }
                }

                Refresh();

                if (zivoti <= 0)
                {
                    t.Stop();
                    MessageBox.Show("Kraj igre! Poeni: " + poeni);
                    Close();
                }
            }
        }

        private void DodajPredmet()
        {
            int x = r.Next(0, this.ClientSize.Width - 30);
            int tip = r.Next(0, 3);
            Predmet p;

            if (tip == 0)
                p = new Jabuka(x, 0);
            else if (tip == 1)
                p = new Bomba(x, 0);
            else
                p = new Pomorandza(x, 0);

            predmeti.Add(p);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Visible = false;
            button2.Visible = false;
            radioButton1.Visible = false;
            radioButton2.Visible = false;
            radioButton3.Visible = false;
            label1.Visible = false;
            label2.Visible = false;
            gameStarted = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (gameStarted)
            {
                Graphics g = e.Graphics;
                SolidBrush cetka1 = new SolidBrush(Color.SaddleBrown);
                SolidBrush cetka2 = new SolidBrush(BackColor);
                Pen olovka = new Pen(Color.Black, 1);
                Rectangle korpaRect = new Rectangle(korpaX, korpaY, korpaSirina, korpaVisina);
                g.FillEllipse(Brushes.SaddleBrown, korpaRect);
                g.DrawEllipse(Pens.Black, korpaRect);
                Rectangle gornjiDeo = new Rectangle(korpaX, korpaY, korpaSirina, korpaVisina / 2);
                g.FillRectangle(cetka2, gornjiDeo);
                for (int i = 0; i < predmeti.Count; i++)
                {
                    predmeti[i].Crtaj(e.Graphics);
                }
                label1.Visible = true;
                label2.Visible = true;
                label1.Text = "Poeni: " + poeni;
                label2.Text = "Životi: " + zivoti;
            }
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            t.Interval = 75;
            korpaSirina = 150;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            t.Interval = 30;
            korpaSirina = 80;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            t.Interval = 1;
            korpaSirina = 40;
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            korpaX = e.X - 25;
            korpaY = this.ClientSize.Height - 50;
            Refresh();
        }
    }
}
