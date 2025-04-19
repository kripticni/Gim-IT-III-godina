using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Pair<F,S>
{
    public F first { get; set; }
    public S second { get; set; }

    public Pair(F _first, S _second)
    {
        first = _first;
        second = _second;
    }
}
