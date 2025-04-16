using System;
using System.Text.RegularExpressions;
using System.Drawing;
using System.IO;


public class Korisnik : Osoba, IFajl
{
	private string korisnicko_ime;
    public string KorisnickoIme {
		get
		{
			return korisnicko_ime;
		}
		set
		{
			if (value == string.Empty)
				throw new ArgumentException("Losa Vrednost");
			korisnicko_ime = value;
		} 
	}

    private string email;

	public static bool validanEmail(string email)
	{
		if (email == string.Empty)
			return false;
		return email.Contains("@");
	}

	public string Email
	{
		get
		{
			return email;
		}
		private set
		{
			if (validanEmail(value))
				email = value;
			else throw new ArgumentException("Losa Vrednost");
		}
	}

	private string broj_telefona;
    public static bool validanBrTelefona(string br_telefona)
    {
		if (br_telefona == string.Empty)
			return false;
        string sablon = @"^\+\(\d{3}\) \(\d{3}\) \(\d{7}\)$";
        return Regex.IsMatch(br_telefona, sablon);
    }
    public string BrojTelefona
	{
		get
		{
			return broj_telefona;
		}
		private set
		{
			if (validanBrTelefona(value))
				broj_telefona = value;
			else
				throw new ArgumentException("Losa Vrednost");
		}
	}

	private Bitmap profilna;
	private string put_do_profilne;

	public static bool validnaSlika(string put)
	{
		const int maxVelicina = 1 * 1024 * 1024; //1mb
		if (!File.Exists(put))
			return false;
			//throw new FileNotFoundException("Fajl nije pronadjen.");

		long velicina = new FileInfo(put).Length;
		if (velicina > maxVelicina)
			return false;
		//throw new Exception("Fajl je veci od 1mb.");

		return true;
	}

	public void promeniProfilnu(string put)
	{
		if (!validnaSlika(put))
			throw new Exception("Slika nije validna");
		try
		{
			using (FileStream fs = new FileStream(put, FileMode.Open, FileAccess.Read))
				using (Image img = Image.FromStream(fs, useEmbeddedColorManagement: false, validateImageData: true))
					profilna = new Bitmap(img);
			put_do_profilne = put;
		}
		catch (Exception)
		{
			throw new Exception("Slika nije validna");
		}
	}

	

    public Korisnik(string _ime, string _prezime, DateTime _datum_rodjenja, bool _pol, string _korisnicko_ime, string _email, string _broj_telefona, string _put_do_slike)
		: base(_ime, _prezime, _datum_rodjenja, _pol)
    {
		KorisnickoIme = _korisnicko_ime;
		Email = _email;
		BrojTelefona = _broj_telefona;
		promeniProfilnu(_put_do_slike);
    }

	#region interface
	override public string podrazumevani_fajl { get; set; } = "korisnik.txt";
	override public void Pisi(string put)
    {
        StreamWriter w = new StreamWriter(put);
        w.WriteLine(Ime);
        w.WriteLine(Prezime);
        w.WriteLine(DatumRodjenja.ToString());
        w.WriteLine(Pol);
		w.WriteLine(KorisnickoIme);
		w.WriteLine(Email);
		w.WriteLine(BrojTelefona);
		w.WriteLine(put_do_profilne);
        w.Close();
    }
    override public void Pisi()
    {
        StreamWriter w = new StreamWriter(podrazumevani_fajl);
        w.WriteLine(Ime);
        w.WriteLine(Prezime);
        w.WriteLine(DatumRodjenja.ToString());
        w.WriteLine(Pol);
        w.WriteLine(KorisnickoIme);
        w.WriteLine(Email);
        w.WriteLine(BrojTelefona);
        w.WriteLine(put_do_profilne);
        w.Close();
    }
    override public void Citaj(string put)
    {
        StreamReader r = new StreamReader(put);
        Ime = r.ReadLine();
        Prezime = r.ReadLine();
        DatumRodjenja = DateTime.Parse(r.ReadLine());
        Pol = r.ReadLine();
        KorisnickoIme = r.ReadLine();
        Email = r.ReadLine();
        BrojTelefona = r.ReadLine();
        put_do_profilne = r.ReadLine();
        r.Close();
    }
    override public void Citaj()
    {
		StreamReader r = new StreamReader(podrazumevani_fajl);
        Ime = r.ReadLine();
        Prezime = r.ReadLine();
        DatumRodjenja = DateTime.Parse(r.ReadLine());
        Pol = r.ReadLine();
        KorisnickoIme = r.ReadLine();
        Email = r.ReadLine();
        BrojTelefona = r.ReadLine();
        put_do_profilne = r.ReadLine();
        r.Close();
    }
    #endregion
}
