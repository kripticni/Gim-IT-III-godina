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
            int brojac = 0, suma = 0;
            StreamReader _read = new StreamReader("Brojevi.txt");
            while (!_read.EndOfStream)
            {
                suma += Convert.ToInt32(_read.ReadLine());
                brojac++;
            }
            textBox1.Text = Convert.ToString(suma / brojac);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
