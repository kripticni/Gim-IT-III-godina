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
    public partial class UserControl4 : UserControl
    {
        public UserControl4()
        {
            InitializeComponent();
        }

        private void UserControl4_Load(object sender, EventArgs e)
        {
            richTextBox1.Rtf = "{\\rtf1\\ansi\\deff0\r\n" + 
                "{\\colortbl ;\\red0\\green0\\blue0;\\red0\\green128\\blue255;\\red34\\green177\\blue76;\\red255\\green165\\blue0;}\r\n" + 
                "\r\n" + "{\\b\\fs48\\cf2 Welcome to P2PChat!}\\par\r\n" + 
                "\r\n" + "{\\fs28\\cf2 Local communication is here! }{\\fs26 P2PChat is a \\b lightweight\\b0, \\b blazingly fast\\b0, and \\b completely secure, \\b0 peer-to-peer chat application designed for local networks. No servers, no middlemen—just pure, direct communication.}\\par\r\n" + 
                "\r\n" + "{\\b\\fs36\\cf3 Why Choose P2PChat?}\\par\r\n" +
                "{\\fs26\\cf3 \\b \\bullet Fast and Lightweight: \\b0} {\\fs22 P2PChat is optimized for speed and minimal resource usage in C#, ensuring smooth performance even on older devices.}\\par\r\n" + 
                "{\\fs26\\cf3 \\b \\bullet Secure by Design: \\b0} {\\fs22 End-to-end encryption means that your messages stay private—only you and your chat partner can read them.}\\par\r\n" + 
                "{\\fs26\\cf3 \\b \\bullet Zero Configuration Needed: \\b0} {\\fs22 Just start the app and connect instantly to peers on the same local network. No need for complex setups.}\\par\r\n" + 
                "{\\fs26\\cf3 \\b \\bullet No Central Servers: \\b0} {\\fs22 Unlike cloud-based messaging apps, P2PChat operates entirely within your local network, keeping your data in your hands.}\\par\r\n" + 
                 
                "\r\n" + "{\\b\\fs36\\cf4 Getting Started}\\par\r\n" + 
                "{\\fs28\\cf4 \\b 1. \\b0 Launch P2PChat on your device.}\\par\r\n" + 
                "{\\fs28\\cf4 \\b 2. \\b0 It will automatically detect other users on the same network.}\\par\r\n" + 
                "{\\fs28\\cf4 \\b 3. \\b0 Start chatting instantly with anyone nearby—no sign-ups, no hassle!}\\par\r\n" + 
                "\r\n" + "{\\b\\fs36\\cf2 Join the P2P Revolution!}\\par\r\n" + 
                "{\\fs28 Experience the power of true peer-to-peer messaging. Whether you're in an office, at home, or at a local event, P2PChat keeps you connected—securely and effortlessly.}\\par\r\n" + 
                "\r\n" + "{\\b\\fs40\\cf3 Ready to Chat?}\\par\r\n" + 
                "{\\fs28\\b Launch the app and start your seamless, private conversations now!\\b0}\\par\r\n" + "}\r\n" + "";

        }
    }
}
