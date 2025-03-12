#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preproces(char* lps, char str[]) {
    int len = 0; //sufiks sa proslim indeksom
    int i = 1; //krecemo od jedan
    int n = strlen(str); //do duzinu od str
    lps[0] = 0; //nulta je uvek nula

    while (i < n) 
        //ako su isti inkrementiramo
        if (str[i] == str[len]) 
            lps[i++] = ++len;

        //ako nisu isti
        else 
            if (len != 0) 
                len = lps[len - 1];
                //da bi smo preskocili poredjenja

            else 
                lps[i++] = 0;
                //ako nema ponavljanja len od i je nula
}

void kmp(char str[], char text[]) {
  int n = strlen(text);
  int m = strlen(str);
  int i = 0;
  int j = 0;

  char lps[m];
  preproces(lps, str);

  while (i < n) {
    if (text[i] == str[j]) {
      //ako su isti povecavamo oba, kao kod bruteforce
      i++;
      j++;

      if (j == m) {
        printf("Nadjeno na indeksu: %i\n", i - j);
        return; //ako trazimo jedno pojavljivanje
        //j = lps[j - 1]; // ako trazimo vise
      }
    }

    else {
      //ako nisu isti, koristimo lps niz da se vracamo
      if (j != 0)
        j = lps[j - 1];
      else
        i++;
    }
  }
}

void bruteforce(char str[], char text[]){
  int m = strlen(str);
  int i = 0;
  int j = 0;
  while(text[i] != '\0'){
    if(str[j] == text[i])
      ++j;
    else
      j = 0;

    if(j == m){
      printf("Nadjeno na indeksu: %i\n", i - j + 1);
      return;
    }
    ++i;
  }
}

int main(){
  char text[] = "acaadaaba";
  char str[] = "aaba";

  kmp(str, text);
  bruteforce(str, text);
}
