using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Brod
{
    public partial class Form1 : Form
    {
        Graphics _g;
        Timer _t;
        public Form1()
        {
            InitializeComponent();
            x = ClientRectangle.Width / 2;
            y = ClientRectangle.Height / 2;
            a = 35;

            _t = new Timer();
            _t.Interval = 100;
            _t.Tick += pomak;
            _t.Start();
        }

        private void Form1_Load(object sender, EventArgs e)
        {


        }

        int a, x, y;
        SolidBrush braon = new SolidBrush(Color.Brown);
        SolidBrush bela = new SolidBrush(Color.White);
        SolidBrush plava = new SolidBrush(Color.LightBlue);
        Pen olovka = new Pen(Color.Black);
        Point t1, t2, t3, d1, d2, d3, j1, j2, j3;

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            _g = e.Graphics;
            _g.FillRectangle(plava, 0, ClientRectangle.Height / 2 - 15, ClientRectangle.Width, ClientRectangle.Height / 2 + 15);

            _g.FillRectangle(braon, x - a, y, 2*a, a);
            _g.DrawRectangle(olovka, x - a, y, 2 * a, a);
            t1 = new Point(x - 2 * a, y);
            t2 = new Point(x - a, y + a);
            t3 = new Point(x - a, y);
            d1 = new Point(x + 2 * a, y);
            d2 = new Point(x + a, y + a);
            d3 = new Point(x + a, y);
            j1 = new Point(x, y - 3*a);
            j2 = new Point(x, y - a);
            j3 = new Point(x + 2*a, y - 2*a);

            Point[] trougao1 = { t1, t2, t3 }, trougao2 = { d1, d2, d3 };
            _g.FillPolygon(braon, trougao1);
            _g.FillPolygon(braon, trougao2);
            _g.DrawPolygon(olovka, trougao1);
            _g.DrawPolygon(olovka, trougao2);

            Point[] jarbol = { j1, j2, j3 };
            _g.FillPolygon(bela, jarbol);
            _g.DrawPolygon(olovka, jarbol);

            _g.DrawLine(olovka, x, y, x, y - 3*a);
        }

        private void pomak(object sender, EventArgs e) {
            x += 5;
            if (x > ClientRectangle.Width + 2 * a)
            {
                x = -(2 * a);
            }
            Refresh();
        }
    }
}
