using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _300_tacaka
{
    public partial class Form1 : Form
    {
        Graphics _g;
        Random _r = new Random();
        public Form1()
        {
            InitializeComponent();
            _g = CreateGraphics();
        }

        int r = 15;
        Point[] tacke = new Point[300];
        double[] razlike = new double[300];
        SolidBrush crna = new SolidBrush(Color.Black);
        SolidBrush oznacen = new SolidBrush(Color.Red);
        Pen oznacen_olovka = new Pen(Color.Red);

        private void crtaj_Click(object sender, EventArgs e)
        {
            int i;
            for (i = 0; i < 300; i++)
            {
                tacke[i].X = _r.Next(0, ClientRectangle.Width) + r/2;
                tacke[i].Y = _r.Next(0, ClientRectangle.Height) + r/2;
                _g.FillEllipse(crna, tacke[i].X - r/2, tacke[i].Y - r/2, r, r);
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            int i, j;
            double x, y;
            double pom;
            Point swap;
            x = e.X;
            y = e.Y;

            for (i = 0; i < 300; i++)
                razlike[i] = Math.Sqrt(Math.Pow(e.X - tacke[i].X, 2) + Math.Pow(e.Y - tacke[i].Y, 2)); 

            for(i=0; i<10; i++)
                for(j=i+1; j<299; j++)
                    if(razlike[j] < razlike[i])
                    {
                        pom = razlike[j];
                        razlike[j] = razlike[i];
                        razlike[i] = pom;

                        swap = tacke[j];
                        tacke[j] = tacke[i];
                        tacke[i] = swap;
                    }
            
            for (i = 0; i < 10; i++)
                _g.FillEllipse(oznacen, tacke[i].X - r / 2, tacke[i].Y - r / 2, r, r);

            _g.DrawEllipse(oznacen_olovka, e.X - Convert.ToSingle(razlike[9]), e.Y - Convert.ToSingle(razlike[9]), Convert.ToSingle(razlike[9] * 2), Convert.ToSingle(razlike[9]* 2));
        }
    }
}
