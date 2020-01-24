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
	int il = 30, i = 0, j = 0;
	char delim[2] = ";";
	char *token, *tyt;

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
		token = strtok(wynik_fgets, delim);
		tyt = token;
		//printf("%s\n", token);
		strcpy(iterator->tytul, tyt);
		j = 0;

		while(token != NULL) {
		//	strcpy(iterator->tytul, tyt);
			token = strtok(NULL, delim);
			if (j == 0) { strcpy(iterator->autor, token); }
			else if (j == 1) { iterator->ilosc = atoi(token); }
			else if (j == 2) { iterator->cena = atof(token); }
			j++;
			//printf("%s\n", token);
		}
		push_back(iterator);
		iterator++;
		i++;
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
  int i = 0;
  char *pod;

  for(int i = 0; i < 30; i++) {
    //printf("Autor: %s \n", iterator->autor);
    //pod = strstr(iterator->autor, autor_do_usuniecia);
    //printf("PS: %s\n", pod);
    //iterator = iterator->nastepny;
    if (strstr(iterator->autor, autor_do_usuniecia) == autor_do_usuniecia) {
      printf("Weszlem: %s", pod);
      //free(iterator->tytul);
      //free(iterator->autor);
      //free(iterator->ilosc);
      //free(iterator->ilosc);
      //iterator->nastepny = iterator->nastepny->nastepny;

    }
    iterator = iterator->nastepny;
  
  }
  
}

int main() {
	wypelnij_strukture("lista.txt");
	wypisz();
	printf("Usun Lindsay\n");
	usun_autor("Lindsay");
	printf("\n");
	printf("Po usunieciu Lindsay:\n");
	wypisz(); 
  
	return 0;
}
