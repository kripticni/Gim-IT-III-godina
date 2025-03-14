using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace slovo_M
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //_g = CreateGraphics();
        }


        int x1, y1, x2, y2;
        Point tacka1, tacka2;
        Pen olovka = new Pen(Color.Black);

        Graphics _g;
        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            _g = CreateGraphics();
            y2 = Convert.ToInt32(e.Y);
            x2 = Convert.ToInt32(e.X);

            if (y2 < y1)
            {
                y2 = y2 ^ y1;
                y1 = y2 ^ y1;
                y2 = y2 ^ y1;
            }

            tacka1 = new Point(x1, y1);
            tacka2 = new Point(x1, y2);
            _g.DrawLine(olovka, tacka1, tacka2);
            tacka2 = new Point(x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
            _g.DrawLine(olovka, tacka1, tacka2);
            tacka1 = new Point(x1 +(x2 - x1), y1);
            _g.DrawLine(olovka, tacka1, tacka2);
            tacka2 = new Point(x1 + (x2 - x1), y2);
            _g.DrawLine(olovka, tacka1, tacka2);
        }

        /*
        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            _g = CreateGraphics();
            x1 = Convert.ToInt32(e.X);
            y1 = Convert.ToInt32(e.Y);
            
            if(y2 < y1){
                int pom = y2;
                y2 = y1;
                y1 = pom;
            }

            x1 = x2;
            h = (y2 - y1) / 2;

            tacka1 = new Point(x1, y1);
            tacka2 = new Point(x2, y2);
            _g.DrawLine(olovka, tacka1, tacka2);
            tacka2 = new Point(x1 + h, y1 + h);
            _g.DrawLine(olovka, tacka1, tacka2);
            tacka1 = new Point(x1 + 2 * h, y1);
            _g.DrawLine(olovka, tacka1, tacka2);
            tacka2 = new Point(x1 + 2 * h, y2);
            _g.DrawLine(olovka, tacka1, tacka2);
        }
        */

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            y1 = Convert.ToInt32(e.Y);
            x1 = Convert.ToInt32(e.X);
        }
    }
}
