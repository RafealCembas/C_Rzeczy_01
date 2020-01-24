#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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

	if(iterator == NULL) {
		glowa = element;
		return;
	}
	while (iterator->nastepny != NULL) {
		iterator = iterator->nastepny;
	}

	iterator->nastepny = element;
	//iterator->nastepny->nastepny = NULL;
}

int wypelnij_strukture(const char *nazwaPliku) {
	FILE *fp = fopen(nazwaPliku, "r");
	ksiazka *iterator = glowa;
	int n_max = 100;
	char linia[n_max], *wynik_fgets;
	int i = 0, j = 0;
	char delim[2] = ";";
	char *token;

	while(i < 30) {

		if( (iterator = (ksiazka*)malloc(sizeof(ksiazka))) == NULL ) {
			fprintf(stderr, "Za mało pamięci!\n");
			exit(ZA_MALO_PAMIECI);
		}

		if( (iterator->tytul = (char*)malloc(sizeof(strlen(iterator->tytul)+1))) == NULL ) {
                	fprintf(stderr, "Za mało pamięci!\n");
                	exit(ZA_MALO_PAMIECI);
		}

		if( (iterator->autor = (char*)malloc(sizeof(strlen(iterator->autor)+1))) == NULL ) {
                        fprintf(stderr, "Za mało pamięci!\n");
                        exit(ZA_MALO_PAMIECI);
                }

		wynik_fgets = fgets(linia, n_max, fp);
		token = strtok(linia, ";");
		//tyt = token;
//		printf("%s\n", token);
		//strcpy(iterator->tytul, tyt);
//		j = 0;

		while(token != NULL) {
		//	strcpy(iterator->tytul, tyt);
			//token = strtok(NULL, delim);
			if (j == 0) { strcpy(iterator->tytul, token); }
			if (j == 1) { strcpy(iterator->autor, token); }
			else if (j == 2) { iterator->ilosc = atoi(token); }
			else if (j == 3) { iterator->cena = atof(token); }
			token = strtok(NULL, ";");
			j++;
//			printf("%s\n", token);
		}
		push_back(iterator);
		iterator++;
		i++;
		j = 0;
	}
	return 0;
}

void wypisz() {
	ksiazka *iterator = glowa;

/*	if (iterator != NULL) {
		printf("Pusta lista.\n");
	}
*/
	for (int i = 0; i < 30; i++) {
    printf("%d ", i+1);
		printf("Tytul: %s \t", iterator->tytul);
		printf("Autor: %s \t", iterator->autor);
		printf("Ilosc: %d \t", iterator->ilosc);
		printf("Cena: %.2f", iterator->cena);
		printf("\n");
	  iterator = iterator->nastepny;
	}
	//iterator = iterator->nastepny;

}

void usun_autor(const char* autor_do_usuniecia) {
  ksiazka *iterator = glowa;
  ksiazka *iterator2 = glowa->nastepny;
  int i = 0, kol = 0;
  char *pod;

  while(iterator->nastepny != NULL) {
    if (strstr(iterator->nastepny->autor, autor_do_usuniecia) != NULL) {
      free(iterator->nastepny);
      iterator->nastepny = iterator->nastepny->nastepny;
    }
    iterator = iterator->nastepny;
  }
    while(iterator2->nastepny != NULL) {
      if (strstr(iterator2->nastepny->autor, autor_do_usuniecia) != NULL) {
        free(iterator2->nastepny);
        iterator2->nastepny = iterator2->nastepny->nastepny;
      }
    iterator2 = iterator2->nastepny;
    }
 // }

}

int main() {
	wypelnij_strukture("lista.txt");
	wypisz();
	printf("Usun Lindsay\n");
	usun_autor("Rowling");
	printf("\n");
	printf("Po usunieciu Lindsay:\n");
	wypisz();

	return 0;
}
