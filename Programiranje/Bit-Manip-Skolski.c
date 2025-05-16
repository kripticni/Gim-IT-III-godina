#include <stdio.h>
#include <stdlib.h>

/*
sf koja pokazuje bit na zadatoj poziciji za unsigned(getbit)
sf koja postavlja bit na zadatoj poziciji na 1 i prikazuje dobijeni broj tipa unsigned u binarnom(setbit)
sf koja postavlja bit na zadatoj poziciji na 0 i prikazuje dobijeni broj tipa unsigned(clearbit)
sf koja invertuje bit na zadatoj poziciji i prikazuje dobijeni broj u binarnom(flipbit)
sf koja cuva n krajnih desnih, a ostale leve postavi na 0(primer1)
sf koja zadnjih n bitova postavi na 1, a ostale sa leve strane cuva(primer2)
sf koja invertuje bitove od pozicije p u duzini n, a ostale sacuvati(primer3)
sf koja ce od pozicije p u duzini n postaviti bitove na 0, a ostale sacuvati(primer4)
u main uneti poziciju bita za svaku funkciju posebno i neki broj tipa unsigned i prikazati rezultate svake funkcije(uneti i vrednost bita na koju postavljamo za
*/
void getBit(unsigned v, int bitNo)
{
    unsigned mask=1;
    mask=mask<<(bitNo-1)
    if((mask&v)!=0) printf("1");
    else printf("0");
}

void setBit(unsigned v, int bitNo)
{
    unsigned mask=1;
    mask=mask<<(bitNo-1)
    v=v/mask;
    binIspis(a);
}

void clearBit(unsigned v, int bitNo)
{
    unsigned mask=1;
    mask=~(mask<<(bitNo-1))
    v=v&mask;
    binIspis(v);
}

void flipBit(unsigned v, int bitNo)
{
    unsigned mask=1;
    mask=mask<<(bitNo=1);
    v=v^mask;
    binIspis(v);
}

void binIspis(int n)
{
    int i;
    printf("%d ",n);
    for(i=1;i<=16;i++)
    {
        printf("%d",((n&0x8000)!=0));
        n = n << 1;
        if(i%4==0)
            printf(" ");
    }
}

void hexIspis(int n)
{
    printf("0x%x",n);
}

void primer1a(unsigned x)
{
    unsigned mask=0;
    mask=~(~max<<n);
    x=x&mask;
    binIspis(x);
}

void primer1b(unsigned x)
{
    unsigned mask=0;
    mask=mask>>(sizeof(unsigned)*8-n);
    x=x&mask;
    binIspis(x);
}

void

void primer3a(unsigned x, int p,int n)
{
    unsigned mask=0;
    mask=(~(~ mask<<n))<<(p-1);
    x=x^mask;
    binispis(x);
}

void primer3b(unsigned x, int p,int n)
{
    const int s=sizeof(x)*8;
    const int mask=0xffffffff;
    binIspis(x^(mask<<(s-p-n)>>(s-n)<<p));
}

void primer3a(unsigned x, int p,int n)
{
    unsigned mask=0;
    mask=~(~(~ mask<<n))<<(p-1);
    x=x&mask;
    binispis(x);
}

int main()
{
    int a,b;
    printf("Unesi a i b");
    scanf("%i %i",&a,&b);
    printf("\na=");
    binIspis(a);
    printf("\nb=");
    binIspis(b);
    printf("\nRezultat za &=");
    binIspis(a&b);
    printf("\nRezultat za |=");
    binIspis(a|b);
    printf("\nRezultat za ^=");
    binIspis(a^b);
    return 0;
}
