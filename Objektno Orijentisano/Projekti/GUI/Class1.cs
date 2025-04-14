using System;
using System.IO;

public abstract class Osoba
{
	protected string ime;
	protected string prezime;

	public string Ime {
		get { return ime; }
		protected set {
			if (value != string.Empty)
				ime = value;
			else
				throw new ArgumentException("Losa Vrednost");
		}
	}
	public string Prezime {
		get { return prezime; }
        protected set{
            if (value != string.Empty)
                prezime = value;
            else
                throw new ArgumentException("Losa Vrednost");
        }
    }

	protected DateTime datum_rodjenja;
	public int Starost { 
		get
		{  
			DateTime danas = DateTime.Today;
			int godine = danas.Year - datum_rodjenja.Year;
            if (datum_rodjenja > danas.AddYears(-godine))
                godine--; //ako se rodjendan nije jos desio, smanjimo godinu
			return godine;
		}
	}

	public DateTime DatumRodjenja
	{
		get { return datum_rodjenja; }
		protected set
		{
			datum_rodjenja = value;
		}
	}

	protected bool pol;

	public static bool PolToBool(string pol)
	{
		if (pol == "Musko")
			return true;
		else
			return false;
	}
	public string Pol
	{
		get
		{
			if (pol == true)
				return "Musko";
			else
				return "Zensko";
		}
		protected set
		{
			pol = PolToBool(value);
		}
	}

	public string PunoIme => $"{Ime} {Prezime}";
    //skracenica za get i string interpolacija

	//nezasticeno za string.Empty, sluzi za izvedene klase
    protected Osoba()
    {
		ime = string.Empty;
		prezime = string.Empty;
		datum_rodjenja = DateTime.Now;
		pol = false;
    }

    public Osoba(string _ime, string _prezime, DateTime _datum_rodjenja, bool _pol)
	{
		Ime = _ime;
		Prezime = _prezime;
		DatumRodjenja = _datum_rodjenja;
		pol = _pol;
	}

    public Osoba(string _ime, string _prezime, DateTime _datum_rodjenja, string _pol)
    {
        Ime = _ime;
        Prezime = _prezime;
        DatumRodjenja = _datum_rodjenja;
        Pol = _pol;
    }

    public Osoba(StreamReader r) {
        Ime = r.ReadLine();
        Prezime = r.ReadLine();
        DatumRodjenja = DateTime.Parse(r.ReadLine());
        Pol = r.ReadLine();
        r.Close();
	}

	public void SacuvajInformacije()
	{
		StreamWriter w = new StreamWriter("osoba.txt");
        w.WriteLine(Ime);
        w.WriteLine(Prezime);
        w.WriteLine(DatumRodjenja.ToString());
        w.WriteLine(Pol);
        w.Close();
	}
}
