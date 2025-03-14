using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Kuca
{
    public partial class Form1 : Form
    {
        Timer _timer = new Timer();
        Graphics _g;
        SolidBrush _cetka_crvena = new SolidBrush(Color.Red);
        SolidBrush _cetka_zuta = new SolidBrush(Color.Yellow);
        SolidBrush _cetka_plava = new SolidBrush(Color.Blue);
        SolidBrush _cetka_braon = new SolidBrush(Color.Brown);
        SolidBrush _cetka_zelena = new SolidBrush(Color.Green);
        Pen olovka = new Pen(Color.Black);

        Point a = new Point(75,150), b = new Point(425, 150), c = new Point(237, 75);
        Point[] trougao;

        public Form1()
        {
            InitializeComponent();
            _g = CreateGraphics();
            _timer.Interval = 1000;
            _timer.Tick += crtanje;
            trougao = new Point[] { a, b, c };
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (_timer.Enabled == false) _timer.Start();
            else _timer.Stop();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void crtanje(object sender, EventArgs e)
        {
            _g.FillRectangle(_cetka_zuta, 100, 150, 300, 200);
            _g.FillRectangle(_cetka_braon, 250, 250, 50, 100);
            _g.FillRectangle(_cetka_braon, 550, 150, 50, 200);
            _g.FillEllipse(_cetka_zelena, 525, 75, 100, 100);
            _g.FillEllipse(_cetka_plava, 140, 200, 75, 75);
            _g.FillPolygon(_cetka_crvena, trougao);
        }
    }
}
