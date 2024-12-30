#include "geometrija.h"
#include <stdlib.h>
void dodaj_vektor(Vektor *dest, Vektor src) {
  dest->x = dest->x + src.x;
  dest->y = dest->y + src.y;
  dest->z = dest->z + src.z;
}
