#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROZMIAR 30

struct ksiazka{
  char autor[100];
  char tytul[100];
  unsigned ilosc;
  float cena;
};
struct ksiazka magazyn[ROZMIAR];

unsigned int obliczIloscLini(const char *nazwaPliku)
{
  unsigned int licznik = 0;
  FILE *fp = fopen(nazwaPliku, "r");
  int max_n = 100;
  char linia[max_n], *wynik_fgets;
  while (feof(fp) == 0){
    wynik_fgets = fgets(linia, max_n, fp);
    if (wynik_fgets != NULL){
      licznik++;
    }
  }
  return licznik;
}

int wypelnij_strukture (const char *nazwaPliku)
{
  struct ksiazka *p = magazyn;
  unsigned int i=0, j=0, linie = obliczIloscLini(nazwaPliku);
  FILE *fp = fopen(nazwaPliku, "r");
  int max_n = 100;
  char linia[max_n], *wynik_fgets;
  char *pch;
  while(i < linie){
   wynik_fgets = fgets(linia, max_n, fp);
   pch = strtok(wynik_fgets, ";");
   while(pch != NULL){
     if (j == 0){strcpy(p->tytul, pch);}
     else if (j == 1){strcpy(p->autor, pch);}
     else if (j == 2){p->ilosc = atoi(pch);}
     else if (j == 3){p->cena = atof(pch);}
    pch = strtok(NULL, ";");
    j++;
  }
  j = 0;
  i++;
  p++;
  }
  return 0;
}

float obliczVAT(const char *autor)
{
  unsigned i = 0;
  float vat = 0, cena = 0;
  struct ksiazka *p = magazyn;
  int ret = 1;
  while(i < ROZMIAR){
    ret = strcmp(autor, p->autor);
    if(ret == 0){
      vat += p->cena;
    }
    p++;
    i++;
  }
  vat = vat*0.07;
  return vat;
}

void wyswietl_strukture() {
  struct ksiazka *p = magazyn;
  int linie = obliczIloscLini("lista.txt");
  for (int i=0; i<linie; i++) {
    printf("Cena: %.2f | Autor: %s | Tytul: %s | Ilosc: %u\n", (p+i)->cena, (p+i)->autor, (p+i)->tytul, (p+i)->ilosc);
  }
}

int cmp(const void* left, const void* right) {
  float a = ((struct ksiazka *)left)->cena;
  float b = ((struct ksiazka *)right)->cena;

  if (a < b)
    return -1;
  else if (a == b)
    return 0;
  else
    return 1;
}

void sortuj_wg_ceny() {
  struct ksiazka *p = magazyn;
  int linie = obliczIloscLini("lista.txt");
  qsort(p, linie, sizeof(*p), cmp);
}

int main() {
  wypelnij_strukture("lista.txt");
  //wyswietl_strukture();
  sortuj_wg_ceny();
  wyswietl_strukture();
  return 0;
}
