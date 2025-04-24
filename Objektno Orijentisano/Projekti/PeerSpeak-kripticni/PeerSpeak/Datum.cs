using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//moja prosta implementacija za 
//date only klasu, jer C# kroz
//drugacije verzije nece da mi
//prihvata stringove za datetime
public class Datum
{
    public int Dan { get; private set; }
    public int Mesec { get; private set; }
    public int Godina { get; private set; }
    public Datum(int dan, int mesec, int godina)
    {
        if (dan < 1 || dan > 31)
            throw new ArgumentOutOfRangeException(nameof(dan), "Dan nije izmedju 1 i 31");
        if (mesec < 1 || mesec > 12)
            throw new ArgumentOutOfRangeException(nameof(mesec), "Mesec nije izmedju 1 i 12");
        if (godina < 1)
            throw new ArgumentOutOfRangeException(nameof(godina), "Godina mora da bude pozitivan broj");

        Dan = dan;
        Mesec = mesec;
        Godina = godina;
    }

    public override string ToString()
    {
        return $"{Dan:00}/{Mesec:00}/{Godina}";
    }

    public static Datum Parse(string datum)
    {
        //da bi smo popravili uzasne probleme
        //sa razlicitim C# verzijama koje stavljaju
        //'.' na masked textboxovima i ostalim slucajevima
        char[] input = datum.ToCharArray();
        input[2] = '/';
        input[5] = '/';
        datum = new string(input);

        var parts = datum.Split('/');
        if (parts.Length != 3)
            throw new FormatException("Koristite dd/mm/gggg");

        int dan = int.Parse(parts[0]);
        int mesec = int.Parse(parts[1]);
        int godina = int.Parse(parts[2]);

        return new Datum(dan, mesec, godina);
    }

    public int Starost
    {
        get
        {
            DateTime today = DateTime.Today;
            int starost = today.Year - Godina;

            // If the birthday hasn't occurred yet this year, subtract 1 from the age
            if (today.Month < Mesec || (today.Month == Mesec && today.Day < Dan))
                --starost;

            return starost;
        }
    }
}
