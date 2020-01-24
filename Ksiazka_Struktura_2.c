#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROZMIAR 30

// TEN KOD JEST BARDZO DOBRY DZIALA PICO BELLO

struct ksiazka{
	      char autor[100];
	      char tytul[100];
	      unsigned ilosc;
	      float cena;
};

struct ksiazka magazyn[ROZMIAR];

unsigned int obliczIloscLini(const char *nazwaPliku) {
	      FILE *fp = fopen(nazwaPliku, "r");
        int n_max = 100;
        char linia[n_max], *wynik_fgets;
	      int iloscLinii = 0;

	      wynik_fgets = fgets(linia, n_max, fp);

	      while(wynik_fgets != NULL) {
		            wynik_fgets = fgets(linia, n_max, fp);
		            iloscLinii++;
	      }
	      return iloscLinii;
}

int wypelnij_strukture (const char *nazwaPliku) {
	      FILE *fp = fopen(nazwaPliku, "r");
	      int n_max = 100;
	      char linia[n_max], *wynik_fgets;
	      int il = obliczIloscLini(nazwaPliku), i = 0, j = 0;
        char delim[2] = ";";
	      char *token, *tyt;

	      while(i <= il) {
		            wynik_fgets = fgets(linia, n_max, fp);
		            token = strtok(wynik_fgets, delim);
                tyt = token;
                j = 0;
		            while(token != NULL) {
                        strcpy(magazyn[i].tytul, tyt);
                        token = strtok(NULL, delim);
                        if(j == 0) {
                                strcpy(magazyn[i].autor, token);
                        }
                        else if(j == 1) {
                                magazyn[i].ilosc = atoi(token);
                        }
                        else if(j == 2) {
                                magazyn[i].cena = atof(token);
                        }
                        j++;
		            }
		            i++;
	      }
	      return 0;
}

float obliczVAT(const char *autor) {
        float suma = 0;
        int spr = 1;

        for(int i = 0; i < ROZMIAR; i++) {
                if((spr = strcmp(magazyn[i].autor, autor)) == 0) {
                        suma = suma + magazyn[i].cena;
                }
        }
        return suma * 0.07;
}

int main() {
	      int str = obliczIloscLini("lista.txt");

	      printf("Ilosc linii: %d\n", str);

        printf("\n");

	      wypelnij_strukture("lista.txt");

        printf("%f, %d, %s, %s\n", magazyn[0].cena, magazyn[0].ilosc, magazyn[0].autor,  magazyn[0].tytul);

        printf("\n");

        float osuma = obliczVAT("J. K. Rowling");

        printf("Suma: %f", osuma);

	      return 0;
}
