#include <stdio.h>
#define ROZMIAR 5

void wypelnij(unsigned tab[ROZMIAR][ROZMIAR]) {

  // kod robiony we wspolpracy z Kacprem Gorgoniem

  int r = ROZMIAR, zwoj = r/2, liczba = 1, z = zwoj, i = 0;

  for(z = zwoj; z > 0; z--) {
    int kier = zwoj - z;
    for(i = zwoj - z; i < r; i++) {
      tab[kier][i] = liczba;
      liczba++;
    }
    kier = zwoj + z;

    for(i = zwoj - z + 1; i < r; i++) {
      tab[i][kier] = liczba;
      liczba++;
    }

    for(i = zwoj + z - 1; i >= zwoj - z; i--) {
      tab[kier][i] = liczba;
      liczba++;
    }
    kier = zwoj - z;

    for(i = zwoj + z - 1; i > zwoj - z; i--) {
      tab[i][kier] = liczba;
      liczba++;
    }
    r--;

    if(r%2 != 0) {
      tab[zwoj][zwoj] = ROZMIAR * ROZMIAR;
    }
  }
}

void wyswietl(unsigned tab[ROZMIAR][ROZMIAR]) {

  // kod robiony we wspolpracy z Kacprem Gorgoniem

  for(int i = 0; i < ROZMIAR; i++) {
    for(int j = 0; j < ROZMIAR; j++) {
      printf("%d \t", tab[i][j]);
    }
    printf("\n");
  }
}

int main(void){
  unsigned tablica[ROZMIAR][ROZMIAR];
  wypelnij(tablica);
  wyswietl(tablica);                                                                                                                 
  return 0;
}
