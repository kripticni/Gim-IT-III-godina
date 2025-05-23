﻿using System;
using System.Text.RegularExpressions;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Globalization;
using System.CodeDom;


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
        string sablon = @"^\+\(\d{3}\) \d{3} \d{6,7}$";
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

	public Bitmap profilna { get; private set; }
	
	private string put_do_profilne;
    public string PutDoProfilne { get { return put_do_profilne; } 
		set
		{
			promeniProfilnu(value);
		}
	}
    public static bool validnaSlika(string put)
	{
		const int maxVelicina = 1 * 1024 * 1024; //1mb
		FileInfo file = new FileInfo(put);

		if (!File.Exists(put))
			return false;
        //throw new FileNotFoundException("Fajl nije pronadjen.");

        string[] ekstenzije = { ".jpg", ".jpeg", ".png", ".bmp", ".gif", ".tiff", ".tif", ".ico" };
		if (!ekstenzije.Contains(file.Extension.ToLower()))
			return false;

		if (file.Length > maxVelicina)
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
			{
				Image img = Image.FromStream(fs, false, true);
				profilna?.Dispose();
				profilna = new Bitmap(img);
			}
			put_do_profilne = put;
		}
		catch (Exception)
		{
			throw new Exception("Slika nije validna");
		}
	}

	public void postaviProfilnu(PictureBox pb) 
	{
		if (profilna == null)
			throw new Exception("Nije ucitana profilna");

		if (pb.Image != null)
			pb.Image.Dispose();

		pb.Image = profilna; 
		//deli referencu jer hocu
		//da direktno povezem klasu
		//sa taj picturebox
	}

    public string EnkodirajBitmapB64(Bitmap bitmap, ImageFormat format)
    {
        using (MemoryStream ms = new MemoryStream())
        {
            bitmap.Save(ms, format);
            byte[] imageBytes = ms.ToArray();
            return Convert.ToBase64String(imageBytes);
        }
    }

    // Decode Base64 string to Bitmap
    public static Bitmap DekodirajBitmapB64(string base64)
    {
        byte[] imageBytes = Convert.FromBase64String(base64);
        using (MemoryStream ms = new MemoryStream(imageBytes))
        {
            return new Bitmap(ms);
        }
    }

    public override int GetHashCode()
    {
		string podaci = $"{Ime}{Prezime}{DatumRodjenja.ToString()}{Pol}{KorisnickoIme}{Email}{BrojTelefona}{PutDoProfilne}";
		return podaci.GetHashCode();
    }

	public override bool Equals(object obj)
	{
		if(obj is Korisnik other){
			if (this.Ime == other.Ime &&
				this.Prezime == other.Prezime &&
				this.DatumRodjenja == other.DatumRodjenja &&
				this.Pol == other.Pol &&
				this.Email == other.Email &&
				this.BrojTelefona == other.BrojTelefona &&
				this.PutDoProfilne == other.PutDoProfilne)
				return true;
		}
		return false;
	}

	public static bool operator==(Korisnik a, Korisnik b)
	{
		return a.Equals(b);
	}

    public static bool operator !=(Korisnik a, Korisnik b)
    {
        return !a.Equals(b);
    }

    public Korisnik(string _ime, string _prezime, Datum _datum_rodjenja, bool _pol, string _korisnicko_ime, string _email, string _broj_telefona, string _put_do_slike)
		: base(_ime, _prezime, _datum_rodjenja, _pol)
    {
		KorisnickoIme = _korisnicko_ime;
		Email = _email;
		BrojTelefona = _broj_telefona;
		promeniProfilnu(_put_do_slike);
    }

    public Korisnik(string _ime, string _prezime, Datum _datum_rodjenja, string _pol, string _korisnicko_ime, string _email, string _broj_telefona, string _put_do_slike)
     : base(_ime, _prezime, _datum_rodjenja, _pol)
    {
        KorisnickoIme = _korisnicko_ime;
        Email = _email;
        BrojTelefona = _broj_telefona;
        promeniProfilnu(_put_do_slike);
    }

	public Korisnik(string[] podaci)
	{
		Ime = "nepoznato";
		Prezime = "nepoznato";
		DatumRodjenja = Datum.Parse("01/01/1970");
		Pol = "Musko";
		KorisnickoIme = "nepoznato";
		Email = "nepoznato@nepoznato";
		BrojTelefona = "+(000) 000 0000000";
		promeniProfilnu("defaultmalepfp.jpg");
		foreach(string linija in podaci)
		{
			if (linija.StartsWith("Ime: ")) Ime = linija.Substring("Ime: ".Length);
			if (linija.StartsWith("Prezime: ")) Prezime = linija.Substring("Prezime: ".Length);
			if (linija.StartsWith("Datum rodjenja: ")) DatumRodjenja = Datum.Parse("01/01/1970");
			if (linija.StartsWith("Pol: ")) Pol = linija.Substring("Pol: ".Length);
			if (linija.StartsWith("Korisnicko ime: ")) KorisnickoIme = linija.Substring("Korisnicko ime: ".Length);
			if (linija.StartsWith("Email: ")) Email = linija.Substring("Email: ".Length);
			if (linija.StartsWith("Broj telefona: ")) BrojTelefona = linija.Substring("Broj telefona: ".Length);
			if (linija.StartsWith("Profilna: "))
			{
				string enkodirano = linija.Substring("Profilna: ".Length);
				if (enkodirano.StartsWith("defaultmalepfp.jpg"))
				{
					promeniProfilnu("defaultmalepfp.jpg");
					continue;
				}
				if (enkodirano.StartsWith("defaultfemalepfp.jpg"))
				{
					promeniProfilnu("defaultfemalepfp.jpg");
					continue;
				}
				//nema provere, ali sobzirom da je bitmap
				//i da je response ogranicen na 2mb, trebalo
				//bi da je sve u redu ovako
				profilna = DekodirajBitmapB64(enkodirano);
			}
		}
	}

	public Korisnik(string put)
	{
		this.Citaj(put);
	}

	public Korisnik()
	{
        Ime = "nepoznato";
        Prezime = "nepoznato";
        DatumRodjenja = Datum.Parse("01/01/1970");
        Pol = "Musko";
        KorisnickoIme = "nepoznato";
        Email = "nepoznato@nepoznato";
        BrojTelefona = "+(000) 000 0000000";
        promeniProfilnu("defaultmalepfp.jpg");
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
		w.WriteLine(PutDoProfilne);
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
        w.WriteLine(PutDoProfilne);
        w.Close();
    }
    override public void Citaj(string put)
    {
        StreamReader r = new StreamReader(put);
        Ime = r.ReadLine();
        Prezime = r.ReadLine();
        DatumRodjenja = Datum.Parse(r.ReadLine());
        Pol = r.ReadLine();
        KorisnickoIme = r.ReadLine();
        Email = r.ReadLine();
        BrojTelefona = r.ReadLine();
        promeniProfilnu(r.ReadLine());
        r.Close();
    }
    override public void Citaj()
    {
		StreamReader r = new StreamReader(podrazumevani_fajl);
        Ime = r.ReadLine();
        Prezime = r.ReadLine();
        DatumRodjenja = Datum.Parse(r.ReadLine());
        Pol = r.ReadLine();
        KorisnickoIme = r.ReadLine();
        Email = r.ReadLine();
        BrojTelefona = r.ReadLine();
        promeniProfilnu(r.ReadLine());
        r.Close();
    }
    #endregion
}
