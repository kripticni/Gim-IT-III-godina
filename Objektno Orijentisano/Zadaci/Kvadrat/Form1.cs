using System;
using System.Windows.Forms;

namespace Kvadrat
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // jedna linija, nula promenjive i osecam se kao da pisem javu 
            textBox5.Text = (checkBox1.Checked) ? Convert.ToString(Math.Abs(Convert.ToDouble(textBox1.Text) - Convert.ToDouble(textBox3.Text)) * Math.Abs(Convert.ToDouble(textBox2.Text) - (Convert.ToDouble(textBox4.Text)))) : Convert.ToString(Math.Pow(Convert.ToDouble(textBox1.Text) - Convert.ToDouble(textBox3.Text), 2) + Math.Pow(Convert.ToDouble(textBox2.Text) - Convert.ToDouble(textBox4.Text), 2)); textBox6.Text = (checkBox1.Checked) ? Convert.ToString(2 * Math.Abs(Convert.ToDouble(textBox1.Text) - Convert.ToDouble(textBox3.Text)) + 2 * Math.Abs(Convert.ToDouble(textBox2.Text) - Convert.ToDouble(textBox4.Text))) : Convert.ToString(4 * Math.Sqrt(Math.Pow(Convert.ToDouble(textBox1.Text) - Convert.ToDouble(textBox3.Text), 2) + Math.Pow(Convert.ToDouble(textBox2.Text) - Convert.ToDouble(textBox4.Text), 2)));
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
