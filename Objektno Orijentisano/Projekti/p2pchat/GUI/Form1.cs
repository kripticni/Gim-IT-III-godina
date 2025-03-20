using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            fixButtonBorders();
            showUserControl(userControl41);
        }

        private void fixButtonBorder(Button button){
            button.FlatStyle = FlatStyle.Flat;
            button.FlatAppearance.BorderSize = 2;
            button.FlatAppearance.BorderColor = ColorTranslator.FromHtml("#2E3440");
        }

        private void fixButtonBorders() {
            fixButtonBorder(button1);
            fixButtonBorder(button2);
            fixButtonBorder(button3);
        }

        private void showUserControl(UserControl selected)
        {
            userControl11.Hide();
            userControl21.Hide();
            userControl31.Hide();
            userControl41.Hide();
            selected.Show();
        }

        private void button2_Click(object sender, EventArgs e){
            showUserControl(userControl21);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            showUserControl(userControl31);
        }
    }
}
