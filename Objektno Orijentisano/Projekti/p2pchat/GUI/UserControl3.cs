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
    public partial class UserControl3 : UserControl
    {
        public UserControl3()
        {
            InitializeComponent();
            richTextBox1.ReadOnly = true;
            richTextBox1.Rtf =
    "{\\rtf1\\ansi\\deff0\\nouicompat" +
    "{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri;}}" +
    "{\\colortbl;" +
      "\\red0\\green0\\blue0;" +       //black
      "\\red0\\green128\\blue255;" +   //blue
      "\\red34\\green177\\blue76;" +   //green
      "\\red255\\green165\\blue0;}" +  //orange
    "\\viewkind4\\uc1\\pard" +
    //title
    "\\cf2\\b\\fs48 PeerSpeak - Credits\\b0" +
    "\\cf1\\b\\fs24\\par" +
    "\\par" +
    //programmer
    "\\cf1\\b\\fs36 Programer:\\b0" +
    "\\cf3\\b\\fs32  Lazar Aleksic\\b0" +
    "\\cf3\\b\\fs26  (Gimnazija \"Bora Stankovic\" Vranje III-7)\\b0\\par" +
    "\\par" +
    //artist
    "\\cf1\\b\\fs36 Graficki dizajner:\\b0" +
    "\\cf3\\b\\fs32  Katarina Stoilkovic\\b0" +
    "\\cf3\\b\\fs26  (Hemijsko - Tehnoloska Skola Vranje III-3)\\b0\\par" +
    "\\cf1\\b\\fs24\\par" +
    "\\par" +
    //language
    "\\cf1\\b\\fs32 Napisano u:\\b0" +
    "\\cf3\\b\\fs28  C#\\b0" +
    "\\cf1\\b\\fs24\\par" +
    "\\par" +
    //formatting
    "\\cf1\\b\\fs32 Formatirano sa:\\b0" +
    "\\cf3\\b\\fs28  RTF\\b0" +
    "\\cf1\\b\\fs24\\par" +
    "\\par" +
    //links
    "\\cf1\\b\\fs32 Linkovi:\\b0\\par" +
    "  \\cf4\\fs24\\ul https://github.com/kripticni\\ul0\\cf1\\b\\fs24\\b0\\par" +
    "\\par" +
    //footer
    "\\pard\\qc\\cf2\\b\\fs28 Hvala vam sto koristite PeerSpeak!\\b0" +
    "\\cf1\\b\\fs24\\par" +
    "}";
        }
    }
}
