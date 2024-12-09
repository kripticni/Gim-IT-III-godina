using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Pismeni1
{
    public partial class Form1 : Form
    {
        public int width { get
            {
                return this.ClientRectangle.Width;
            } 
        }

        Trougao trougao = new Trougao();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                trougao.A = Convert.ToInt32(textBox1.Text);
            }
            catch
            {
                
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            //trougao.promeniO(e.X, e.Y);
            //Refresh();
        }

        int brojac = 0;
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (brojac > 0)
            {
                trougao.oboji(e.Graphics, Color.Black);
                trougao.crtaj(e.Graphics, Color.Red);
            }
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            brojac++;
            trougao.promeniO(e.X, e.Y);
            Refresh();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            StreamWriter _fw = new StreamWriter("tekst.txt");
            Random r = new Random();
            int n = r.Next(3, 7);
            for(int i = 0; i < n; i++) 
                _fw.WriteLine(r.Next(0, 255));
            _fw.Close();
            StreamReader _fr = new StreamReader("tekst.txt");

            for (int i = 0; i < n; i++)    
                listBox1.Items.Add(_fr.ReadLine());
            
            _fr.Close();
        }
    }
}
