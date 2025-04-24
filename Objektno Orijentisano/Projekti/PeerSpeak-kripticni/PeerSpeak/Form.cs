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
        public UserControl2 UserControl2
        {
            get
            {
                return userControl21;
            }
        }
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.Icon = new Icon("PeerSpeakV1Icon.ico");
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

        private void button1_Click(object sender, EventArgs e)
        {
            if (userControl21.p == null)
            {
                MessageBox.Show("Prvo ucitajte profil u configure, ili ga napravite i sacuvajte.");
                return;
            }
            if(userControl21.ComboBox1.SelectedIndex == -1 )
            {
                MessageBox.Show("Izaberite adapter i adresu u configure.");
                return;
            }
            if (userControl21.ComboBox2.SelectedIndex == -1)
            {
                MessageBox.Show("Izaberite adresu u configure.");
                return;
            }
            showUserControl(userControl11);
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
