using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace projekat_IgraHvatanja
{
    public abstract class Predmet
    {
        protected int x, y;
        protected int velicina;
        public int X
        {
            get { return x; }
            set { x = value; }
        }
        public int Y
        {
            get { return y; }
            set { y = value; }
        }
        public int Velicina { get; } = 30;

        public Predmet(int x, int y)
        {
            X = x;
            Y = y;
        }

        public void Pomeri()
        {
            Y += 5;
        }

        public bool SudarSa(int korpaX, int korpaY, int korpaSirina, int korpaVisina)
        {
            if (korpaX + korpaSirina < X || korpaX > X + Velicina || korpaY + korpaVisina < Y || korpaY > Y + Velicina)
            { 
                return false;
            }
        return true;
        }
        public abstract void Crtaj(Graphics g);
    }
    public class Jabuka : Predmet
    {
        public Jabuka(int x, int y) : base(x, y) { }

        public override void Crtaj(Graphics g)
        {
            SolidBrush cetka1 = new SolidBrush(Color.Red);
            SolidBrush cetka2 = new SolidBrush(Color.Green);
            Pen olovka = new Pen(Color.Black, 1);
            g.FillEllipse(cetka1, X, Y, Velicina, Velicina);
            g.DrawEllipse(olovka, X, Y, Velicina, Velicina);
            Point[] listic = {
            new Point(X + Velicina / 2, Y),
            new Point(X + Velicina / 2 - 5, Y - 10),
            new Point(X + Velicina / 2 + 5, Y - 10)
        };
            g.FillPolygon(cetka2, listic);
        }
    }
    public class Bomba : Predmet
    {
        public Bomba(int x, int y) : base(x, y) { }

        public override void Crtaj(Graphics g)
        {
            SolidBrush cetka = new SolidBrush(Color.Black);
            Pen olovka = new Pen(Color.Orange, 4);
            g.FillEllipse(cetka, X, Y, Velicina, Velicina);
            g.DrawLine(olovka, X + Velicina / 2, Y, X + Velicina / 2, Y - 10);
        }
    }
    public class Pomorandza : Predmet
    {
        public Pomorandza(int x, int y) : base(x, y) { }

        public override void Crtaj(Graphics g)
        {
            SolidBrush cetka1 = new SolidBrush(Color.Orange);
            SolidBrush cetka2 = new SolidBrush(Color.Green);
            Pen olovka = new Pen(Color.Black, 1);
            g.FillEllipse(cetka1, X, Y, Velicina, Velicina);
            g.DrawEllipse(olovka, X, Y, Velicina, Velicina);
            Point[] listic = {
            new Point(X + Velicina / 2, Y),
            new Point(X + Velicina / 2 - 5, Y - 10),
            new Point(X + Velicina / 2 + 5, Y - 10)
        };
            g.FillPolygon(cetka2, listic);
        }
    }
}
