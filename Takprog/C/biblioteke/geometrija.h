#ifndef GEOMETRIJSKA_BIBLIOTEKA // guard za vise definisanja, preko
                                // preprocessora
#define GEOMETRIJSKA_BIBLIOTEKA
typedef struct vektor {
  float x;
  float y;
  float z;
} Vektor;

typedef struct tacka {
  float x;
  float y;
} Tacka;

void dodaj_vektor(Vektor *dest, Vektor src);
#endif
