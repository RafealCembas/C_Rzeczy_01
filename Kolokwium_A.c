#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ZA_MALO_PAMIECI -1

typedef struct wezel {
  char *tytul;
  char *autor;
  double cena;
  int ilosc;
  struct wezel *nastepny;
} ksiazka;

ksiazka *glowa = NULL;

void push_back(ksiazka *element) {

  ksiazka *iterator = glowa;

  if (iterator == NULL) {
    glowa = element;
    return;
  }

  while (iterator->nastepny != NULL) {
    iterator = iterator->nastepny;
  }
  iterator->nastepny = element;
}

int wypelnij_strukture(const char *nazwaPliku) {

  ksiazka *iterator = glowa;
  int max_n = 100, i=0;
  char lista[max_n], *wynik_fgets, *token;

  FILE *fp = fopen(nazwaPliku, "r");

  while (feof(fp) == 0) {

    if( (iterator = (ksiazka*)malloc(sizeof(ksiazka))) == NULL ) {
      fprintf(stderr, "Za mało pamięci!\n");
      exit(ZA_MALO_PAMIECI);
    }

    if( (iterator->tytul = (char*)malloc(sizeof(strlen(iterator->tytul)+1)) ) == NULL ) {
      fprintf(stderr, "Za mało pamięci!\n");
      exit(ZA_MALO_PAMIECI);
    }

    if( (iterator->autor = (char*)malloc(sizeof(strlen(iterator->autor)+1)) ) == NULL ) {
      fprintf(stderr, "Za mało pamięci!\n");
      exit(ZA_MALO_PAMIECI);
    }


    wynik_fgets = fgets(lista, max_n, fp);
    token = strtok(lista, ";");
    while (token != NULL) {
      if (i == 0) {
        strcpy(iterator->tytul, token);
      }
      else if (i == 1) {
        strcpy(iterator->autor, token);
      }
      else if (i == 2) {
        iterator->ilosc = atoi(token);
      }
      else if (i == 3) {
        iterator->cena = atof(token);
      }
      token = strtok(NULL, ";");
      i++;
    }
  push_back(iterator);
  iterator++;
  i=0;
  }

  return 0;
}

void wypisz() {

  ksiazka *iterator = glowa;
  int i = 1;

  if (iterator == NULL) {
    printf("Pusta lista\n");
  }

  while (iterator->nastepny != NULL) {
    printf("%d. rekord: ", i);
    printf("Autor: %s | ", iterator->autor);
    printf("Tytul: %s | ", iterator->tytul);
    printf("Ilosc: %d | ", iterator->ilosc);
    printf("Cena: %.2f", iterator->cena);
    iterator = iterator->nastepny;
    printf("\n");
    i++;
  }
}

void usun_autor(const char* autor_do_usuniecia) {

  ksiazka *iterator = glowa;
  ksiazka *tmp;
  char *wynik = strstr(iterator->autor, autor_do_usuniecia);
  int flaga = 0;

  if (iterator == NULL) {
    printf("Pusta lista\n");
  }

  if (wynik != NULL && wynik != iterator->autor) {
    glowa = iterator->nastepny;
    free(iterator);
  }

  else {

    while (iterator->nastepny != NULL) {
      flaga = 0;
      wynik = strstr(iterator->nastepny->autor, autor_do_usuniecia);
      if (wynik != NULL) {
        free(iterator->nastepny);
        iterator->nastepny = iterator->nastepny->nastepny;
        flaga = 1;
      }
      if (flaga == 0)
        iterator = iterator->nastepny;
    }
  }
}

int main() {
  wypelnij_strukture("lista.txt");
  wypisz();
  printf("Usun Lindsay\n");
  usun_autor("Rowling");
  printf("\n");
  printf("Po usunieciu Lindsay:\n");
  wypisz();

/************************************/

  return 0;
}
