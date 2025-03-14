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

namespace Dinamicke_Strukture
{
    public partial class Form1 : Form
    {
        List<double> lista= new List<double>();
        StreamReader _reader;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            double prosek;
            double suma = 0;
            int brojac = 0;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            _reader = new StreamReader("plate.txt");
            try
            {
                while (!_reader.EndOfStream)
                {
                    double pomocna = Convert.ToDouble(_reader.ReadLine());
                    lista.Add(pomocna);
                    suma += pomocna;
                    brojac++;
                }
                prosek = suma / (1.0 * brojac);
                textBox1.Text = Convert.ToString(prosek);

                lista.Sort();
                for (brojac--; brojac > 0; brojac--)
                {
                    listBox2.Items.Add(Convert.ToString(lista[brojac]));
                    if (lista[brojac] > prosek)
                    {
                        listBox1.Items.Add(Convert.ToString(lista[brojac]));
                    }
                }
            }
            catch
            {
                textBox1.Text = "Pogresan input";
            }
            _reader.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
