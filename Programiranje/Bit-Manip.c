#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ove dve funkcije zanemarite napisao sam ih
//da meni bude lakse da prikazujem
//macro za kad mi treba unsigned int od 8 bita
void showbits(void* src, short n);
void print(const char* str, void* src, short n);

/*
operacije:
~, not
|, or
&, and
^, xor
>>, arithmetic right shift
<<, arithmetic left shift
printf format string:
%h znaci short ali mora da se naglasi
da li je integer ili unsigned sa i ili u
%hu short unsigned, %hi short signed

%x ispisuje heksadecimalni format
%o ispisuje oktalni format

takodje je bitno da se zapamti
da kad xorujemo sa 1, invertuje stanje
a kad xorujemo sa 0, nista se ne desi
*/


//odavde krece
short copy6lsb(short a); //vraca 6 najmanjih bitova
void printbin(short a); //ispisuje binarni oblik
void printdecbin(short a); //ispisuje dekadni pa binarni format broja
void printhex(short a); //ispisuje heksadecimalni format
void printbinorand(short a, short b); //ispisuje oba broja i rezultate AND i OR
void savenright(unsigned a, short n); //cuva n desnih
void setnright(unsigned a, short n);  //postavlja n desnih
void getbitn(unsigned a, short n);    //ispisuje bit na poziciji n
void setbitn(unsigned a, short n);    //postavlja 1 na poziciji i prikazuje bin
void unsetbitn(unsigned a, short n);  //postavlja 0 na poziciji i prikazuje bin
void invertbitn(unsigned a, short n); //menja stanje na n-ti bit i ispisuje
void frompinvertn(unsigned a, short p, short n); //invertuje n pitova od pozicije p

int main(){
  int a = 3;
  print("Bitovi za 3: ", &a, sizeof(a));

  a = a | 12;
  print("Bitovi za 3 OR 12 -> 15: ", &a, sizeof(a));

  a = a & 20;
  print("15 AND 20 -> 4: ", &a, sizeof(a));

  a = a ^ 100;
  print("4 XOR 100 -> 96: ", &a, sizeof(a));

  short b = copy6lsb((short)a);
  print("Kopiranje 6 najmanjih bitova iz a u b\na i b su po 16 bita, prva 6 bita od 96 -> 32: ", &b, sizeof(b));

  printf("Ispis b u binarni oblik: ");
  printbin(b);

  printf("Ispis b u dekadni i binarni oblik: \n");
  printdecbin(b);

  printf("Ispis b u heksadecimalnom formatu: ");
  printhex(b);

  printf("Binaran ispis a i b, zatim rezultati operacija OR i AND:\n");
  printbinorand(a,b);

  a = 0xFFFFFFFF;
  printf("Cuva N desnih bitova i ostale postavlja na nulu (n=10)\n(a = 0xFFFFFFFF): ");
  savenright((unsigned)a, 10);

  a = 32000;
  printf("Postavlja jedinice na levu stranu i ostale cuva (n = 10)\n(a = 32000): ");
  setnright(a,10);

  a = 7;
  printf("Vraca bit na poziciji N (n = 2) (a = 7): ");
  getbitn(a,2);

  printf("Postavlja jedinicu na N i ispisuje (n = 4) (a = 7): ");
  setbitn(a,4);

  printf("Postavlja nulu na N i ispisuje (n = 1) (a = 7): ");
  unsetbitn(a,1);

  printf("Invertuje bit na N i ispisuje (n = 3) (a = 7): ");
  invertbitn(a,3);

  printf("Na poziciji p invertuje sledecih n bitova i ispisuje\n(n = 4) (p = 4) (a = 7)");
  frompinvertn(a,4,4);
}

short copy6lsb(short a){
  short mask = 0b0000000000111111;
  return a & mask;
}

void printbin(short a){
  short i;
  for(i = 1; i <= 16; ++i){ //ispisuje 16 bita, jedan u svakoj iteraciji
    printf("%c",(a&0x8000)?'1':'0');
    a <<= 1; //shiftujemo a u levo
    if(i%4==0) printf(" "); //stavljamo razmak na svaka 4 bita
  }
  printf("\n\n");
}

void printdecbin(short a){
  printf("Dekadni: %hi\nBinarni: ", a);
  short i;
  for(i = 1; i <= 16; ++i){ //ispisuje 16 bita, jedan u svakoj iteraciji
    printf("%c",(a&0x8000)?'1':'0');
    a <<= 1; //shiftujemo a u levo
    if(i%4==0) printf(" "); //stavljamo razmak na svaka 4 bita
  }
  printf("\n\n");
}

void printhex(short a){
  printf("0x%x \n\n",a);
  //ispisuj 0x pa onda heksadecimalni zapis i dve nove linije
}

void printbinorand(short a, short b){
  printbin(a);
  printbin(b);
  printbin(a|b);
  printbin(a&b);
}

void savenright(unsigned a, short n){
  unsigned mask = 0xFFFFFFFF;
  mask = ~(mask << n);
  printbin(a & mask);
}

void setnright(unsigned a, short n){
  unsigned mask = 0xFFFFFFFF;
  mask = ~(mask << n);
  printbin(a | mask);
}

void getbitn(unsigned a, short n){
  printf("%c\n\n",(a & (1 << n))?'1':'0');
}

void setbitn(unsigned a, short n){
  printbin(a|(1<<n));
}

void unsetbitn(unsigned a, short n){
  printbin(a&(~(1<<n)));
}

void invertbitn(unsigned a, short n){
  printbin(a^(1<<n));
}

void frompinvertn(unsigned a, short p, short n){
    unsigned mask = 0xFFFFFFFF;
    mask = ~(mask << n) << (p - 1);
    printbin(a^mask);
}

//licne pomocne funkcije za pokazivanje bitova
//zanemarite ovo nemamo na test
void showbits(void* src, short n){
  short i;
  for(;n>0;--n){
    for(i = 7; i >= 0; --i)
      printf("%c",(*((char*)src+(n-1)) & (1 << i))?'1':'0');
    printf(" ");
  }
}

void print(const char* str, void* src, short n){
  puts(str);
  showbits(src,n);
  printf("\n\n");
}
