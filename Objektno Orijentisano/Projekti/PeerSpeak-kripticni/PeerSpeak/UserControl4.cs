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
            richTextBox1.ReadOnly = true;
            richTextBox1.Rtf = "{\\rtf1\\ansi\\deff0\r\n" + 
                "{\\colortbl ;\\red0\\green0\\blue0;\\red0\\green128\\blue255;\\red34\\green177\\blue76;\\red255\\green165\\blue0;}\r\n" + 
                "\r\n" + "{\\b\\fs48\\cf2 Dobrodosli u PeerSpeak!}\\par\r\n" + 
                "\r\n" + "{\\fs28\\cf2 Lokalna komunikacija je ovde! }{\\fs26 PeerSpeak je \\b laka\\b0, \\b brza\\b0, \\b bezbedna i sifrovana \\b0 peer-to-peer chat aplikacija dizajnirana za lokalne mreze. \\par Bez servera, bez posrednika, samo cista direktna komunikacija.}\\par\r\n" + 
                "\r\n" + "{\\b\\fs36\\cf3 Zasto izabrati PeerSpeak?}\\par\r\n" +
                "{\\fs26\\cf3 \\b \\bullet Brz i lak: \\b0} {\\fs22 PearSpeak je optimizovan za minimalno koriscenje resursa i brzinu u C#, osigurava dobre performanse i na starijim uredjajima.}\\par\r\n" + 
                "{\\fs26\\cf3 \\b \\bullet Sifrovan po dizajnu: \\b0} {\\fs22 Svaka poruka i svaki fajl su sifrovani sa SSL1.2 End2End enkripcijom tako da su vase poruke privatne i samo za vas i primaoca.}\\par\r\n" + 
                "{\\fs26\\cf3 \\b \\bullet Minimalna konfiguracija: \\b0} {\\fs22 Minimalna konfiguracija je neophodna, napravite profil, izaberite adapter i mrezu, sacuvajte, i spremni ste za dopisivanje.}\\par\r\n" + 
                "{\\fs26\\cf3 \\b \\bullet Bez centralnih servera: \\b0} {\\fs22 Za razliku od cloud-messaging aplikacija, PearSpeak radi samo u vasoj lokalnoj mrezi pa su vasi podaci u vasim rukama.}\\par\r\n" + 
                 
                "\r\n" + "{\\b\\fs36\\cf4 Kratak vodic}\\par\r\n" + 
                "{\\fs28\\cf4 \\b 1. \\b0 Pokrenite aplikaciju i udjite u configure.}\\par\r\n" + 
                "{\\fs28\\cf4 \\b 2. \\b0 Unesite vase informacije, podesavanja za privatnost, i izaberite adapter i adresu.}\\par\r\n" + 
                "{\\fs28\\cf4 \\b 3. \\b0 Idite u chat, upalite vidljivost i pretrazivac, i zapocnite caskanja!}\\par\r\n" + 
                "\r\n" + "{\\b\\fs36\\cf2 Pridruzite se P2P revoluciji!}\\par\r\n" +
                "{\\fs28 Iskusi moc prave peer-to-peer komunikacije.\r\nBilo da si u kancelariji, kod kuce ili na nekom lokalnom dogadjaju, \\par PearSpeak te drzi povezanim – sigurno i bez ikakvog napora.}\\par\r\n" + 
                "\r\n" + "{\\b\\fs40\\cf3 Spreman za caskanje?}\\par\r\n" +
                "{\\fs28\\b Pokreni aplikaciju i zapocni brze, privatne razgovore odmah!\\b0}\\par\r\n" + "}\r\n";

        }
    }
}
