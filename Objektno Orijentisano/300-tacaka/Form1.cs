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

        int r = 5;
        Point[] tacke = new Point[300];
        int[] razlike = new int[300];
        SolidBrush crna = new SolidBrush(Color.Black);
        SolidBrush oznacen = new SolidBrush(Color.Red);

        private void crtaj_Click(object sender, EventArgs e)
        {
            int i;
            for (i = 0; i < 300; i++)
            {
                tacke[i].X = _r.Next(0, ClientRectangle.Width);
                tacke[i].Y = _r.Next(0, ClientRectangle.Height);
                _g.FillEllipse(crna, tacke[i].X, tacke[i].Y, r, r);
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            int i, j, x, y;
            x = e.X;
            y = e.Y;

            for(i = 0; i<300; i++)
                razlike[i] = Math.Abs(x - tacke[i].X) + Math.Abs(y - tacke[i].Y);

            for(i=0; i<10; i++)
                for(j=i+1; j<299; j++)
                    if(razlike[j] < razlike[j + 1])
                    {
                        razlike[j] = razlike[j] ^ razlike[j + 1];
                        razlike[j+1] = razlike[j] ^ razlike[j + 1];
                        razlike[j] = razlike[j] ^ razlike[j + 1];

                        tacke[j].X = tacke[j].X ^ tacke[j+1].X;
                        tacke[j+1].X = tacke[j].X ^ tacke[j + 1].X;
                        tacke[j].X = tacke[j].X ^ tacke[j + 1].X;

                        tacke[j].Y = tacke[j].Y ^ tacke[j + 1].Y;
                        tacke[j + 1].Y = tacke[j].Y ^ tacke[j + 1].Y;
                        tacke[j].Y = tacke[j].Y ^ tacke[j + 1].Y;
                    }
            
            for (i = 0; i < 10; i++)
                _g.FillEllipse(oznacen, tacke[i].X, tacke[i].Y, r, r);
        }
    }
}
