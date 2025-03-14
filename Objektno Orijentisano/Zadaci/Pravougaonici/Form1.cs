using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Pravougaonici
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            _g = CreateGraphics();

            Timer _timer_pravougaonik = new Timer();
            _timer_pravougaonik.Interval = 500;
            _timer_pravougaonik.Tick += crta_pravougaonik;
            _timer_pravougaonik.Start();

            Timer _timer_krug = new Timer();
            _timer_krug.Interval = 50;
            _timer_krug.Tick += crta_krug;
            _timer_krug.Start();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        int a, b, x, y, r, rx;
        float ry;
        Random _r = new Random();
        Pen olovka;
        SolidBrush cetka;

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            ry = Convert.ToSingle(e.Y);
            rx = Convert.ToInt32(e.X);
        }

        SolidBrush cetka_plava = new SolidBrush(Color.Blue);
        SolidBrush cetka_bela = new SolidBrush(Color.White);
        Graphics _g;
 
        private void crta_pravougaonik(object sender, EventArgs e)
        {
            olovka = new Pen(Color.FromArgb(_r.Next(0, 255), _r.Next(0, 255), _r.Next(0, 255)));
            cetka = new SolidBrush(Color.FromArgb(_r.Next(0, 255), _r.Next(0, 255), _r.Next(0, 255)));

            a = _r.Next(60, 100);
            b = _r.Next(20, 50);

            x = _r.Next(a / 2, ClientRectangle.Width - a / 2);
            y = _r.Next(b / 2, ClientRectangle.Height - b / 2);

            _g.FillRectangle(cetka, x, y, a, b);
            _g.DrawRectangle(olovka, x, y, a, b);
        }

        private void crta_krug(object sender, EventArgs e)
        {
            r = _r.Next(20, 150);
            rx = _r.Next(r, ClientRectangle.Width - r);
            ry = 0;

            do
            {
                _g.FillEllipse(cetka_bela, rx, ry + r/2, r, r);
                ry += (float)0.25;
                _g.FillEllipse(cetka_plava, rx, ry + r/2, r, r);
            } while(ry < ClientRectangle.Height);
        }
    }
}
