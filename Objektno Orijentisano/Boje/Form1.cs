using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Boje
{
    public partial class Form1 : Form
    {
        private Timer _timer;
        private Random _random;

        public Form1()
        {
            InitializeComponent();

            _random = new Random();

            _timer = new Timer();
            _timer.Interval = 500;
            _timer.Tick += promeni_pozadinu;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.BackColor = Color.Red;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.BackColor = Color.FromArgb(123, 152, 53);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (_timer.Enabled) _timer.Stop();
            else _timer.Start();
        }

        private void promeni_pozadinu(object sender, EventArgs e)
        {
            this.BackColor = Color.FromArgb(_random.Next(0,255), _random.Next(0,255), _random.Next(0,255));
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
