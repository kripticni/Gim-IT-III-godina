using System; 
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System.Windows;

namespace Pismeni1
{
    internal class Trougao
    {
        private int a;
        private Point o;

        public int A
        {
            get { return a; }
            set {
                if (value > 0) this.a = value;
                else throw new Exception("mora biti vece od 0");
            }
        }

        public Point[] P {
            get
            {
                Point[] p = new Point[3];
                p[0] = new Point(o.X, o.Y - (int)(a * Math.Sqrt(3) / 6));
                p[1] = new Point(o.X + a / 2, o.Y + (int)(a * Math.Sqrt(3) / 6));
                p[2] = new Point(o.X - a / 2, o.Y + (int)(a * Math.Sqrt(3) / 6));
                return p;
            }
        }

        public Trougao(Point _o, int _a) {
            if (_o.X > 0 && _o.Y > 0)
                o = _o;
            else throw new Exception("mora biti vece od nule");
            if (_a > 0) a = _a;
            else throw new Exception("mora biti vece od nule");
        }

        public Trougao() {
            o = new Point(100, 100);
            a = 25;
        }

        public void promeniO(Point _o) {
            if (_o.X > 0 && _o.Y > 0)
                o = _o;
            else throw new Exception("mora biti vece od nule");
        }
        public void promeniO(int x, int y)
        {
            if (x > 0 && y > 0)
            {
                o.X = x;
                o.Y = y;
            }
            else throw new Exception("mora biti vece od nule");
        }

        public void crtaj(Graphics g, Color boja)
        {
            Pen olovka = new Pen(boja, 5);
            g.DrawPolygon(olovka, P);
        }

        public void oboji(Graphics g, Color boja) {
            SolidBrush cetka = new SolidBrush(boja);
            g.FillPolygon(cetka, P);
        }
    }
}
