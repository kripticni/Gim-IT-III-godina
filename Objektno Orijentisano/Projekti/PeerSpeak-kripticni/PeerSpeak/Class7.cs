using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//std::pair iz C++ koji za nasu
//upotrebu proverava samo Pair.first
//za jednakost i za hash
//jer jedna IP adresa moze da ima 
//samo jednog korisnika
public class Pair<F,S>
{
    public F first { get; set; }
    public S second { get; set; }

    public Pair(F _first, S _second)
    {
        first = _first;
        second = _second;
    }

    public override int GetHashCode()
    {
        return first.GetHashCode(); //nas pair
        //return first.GetHashCode() ^ second.GetHashCode(); //generalno za pair
    }

    public override bool Equals(object obj)
    {
        if (obj is Pair<F, S> other)
        {
            return this.first.Equals(other.first);
            // za normalan set bi hteli i && this.second.Equals(other.second);
        }
        return false;
    }
}
