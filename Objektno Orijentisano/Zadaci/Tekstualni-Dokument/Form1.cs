using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Tekstualni_Dokument
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            /* double brojac = 0, suma = 0;
            StreamReader _read = new StreamReader("Brojevi.txt");
            while (!_read.EndOfStream)
            {
                suma += Convert.ToDouble(_read.ReadLine());
                brojac++;
            }
            textBox1.Text = Convert.ToString(suma / brojac);
            */ // Ovo moze da se doda kako bi se prosek izracunao odma pri pokretanju

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                double brojac = 0, suma = 0;
                StreamReader _read = new StreamReader("Brojevi.txt");
                while (!_read.EndOfStream)
                {
                    suma += Convert.ToDouble(_read.ReadLine());
                    brojac++;
                }
                textBox1.Text = Convert.ToString(suma / brojac);
            }
            catch
            {
                textBox1.Text = "Pogresan unos ili nema fajla.";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
