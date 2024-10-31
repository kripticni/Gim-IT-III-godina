#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vektor{
    float x;
    float y;
    float z;
} vektor;

typedef struct tacka{
    float x;
    float y;
} tacka;

float intenzitet(vektor U);
void vektorski(vektor a, vektor b, vektor *c);
float povrsina(tacka A, tacka B, tacka C);
float povrsina1(tacka A, tacka B, tacka C);

float intenzitet(vektor U){
    return sqrt(U.x*U.x + U.y*U.y + U.z*U.z);
}

float povrsina(tacka A, tacka B, tacka C){
    vektor AB, AC, c;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AB.z = 0;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    AC.z = 0;
    vektorski(AB, AC, &c);
    return 1.0/2*intenzitet(c);
}

float povrsina1(tacka A, tacka B, tacka C){
    return fabs((B.x*C.y-C.x*B.y)-(A.x*C.y-A.y*C.x)+(A.x*B.y-A.y*B.x))/2.0;
}

void vektorski(vektor a, vektor b, vektor* c){
    c->x = a.y*b.z - a.z*b.y;
    c->y = a.x*b.z - a.z*b.x;
    c->z = a.x*b.y - a.y*b.x;
}

int main()
{
    tacka
    A = {1, 1},
    B = {2, 3},
    C = {4, 5};
    printf("Povrsina = %f, Povrsina1=%f", povrsina(A,B,C), povrsina1(A,B,C));

    return 0;
}
