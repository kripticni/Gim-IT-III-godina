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
            richTextBox1.Rtf = "{\\rtf1\\ansi\\deff0\\nouicompat" +
"{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri; } }" +
"{\\colortbl;\\red255\\green255\\blue255; }" +
"\\pard\\sa200\\sl276\\slmult1\\fs24\\lang9 \\b P2P Chat - Credits\\b0\\par" +
"\\par" +
"The programmer of this application is \\b Lazar Aleksic\\b0, a student of Gimnazija \"Bora Stankovic\" Vranje\\par" +
"\\par" +
"The application was written in: \\b C#\\b0\\par" +
"\\par" +
"Text formatting was done using: \\b RTF\\b0\\par" +
"\\par" +
"For more information, visit the following links:\\par" +
"\\pard\\sa200\\sl276\\slmult1\\fs20\\lang9 \\i{[Insert link here]}\\i0\\par" +
"\\par" +
"\\i{[https://github.com/kripticni]}\\i0\\par}";
        }
    }
}
