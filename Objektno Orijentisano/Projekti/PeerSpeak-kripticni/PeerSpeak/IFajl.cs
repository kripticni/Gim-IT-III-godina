using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public interface IFajl
{
    string podrazumevani_fajl { get; set; }
    void Pisi(string put);
    void Pisi();
    void Citaj(string put);
    void Citaj();
}