#include <stdio.h>
#include <stdlib.h>
#define ZA_MALO_PAMIECI -1

typedef struct wezel {
  int wartosc;
  struct wezel *nastepny;
  //struct wezel *poprzedni;//w przypadku listy dwukierunkowej
} Wezel;

Wezel *glowa = NULL;

/**********************************************************/

void wypisz() {
  Wezel *iterator = glowa;

  if(iterator == NULL){
    printf("Pusta lista\n");
  }

  while (iterator != NULL) {
    printf("%d\n", iterator->wartosc);
    iterator = iterator->nastepny;
  }
  printf("\n");
}

/**********************************************************/

void push_back(int liczba) {//wstaw element na koniec listy

  // konstruujemy nowy węzeł
  Wezel* element;
  Wezel* iterator = glowa;

  if( (element = (Wezel*)malloc(sizeof(Wezel))) == NULL ) {
    fprintf(stderr, "Za mało pamięci!\n");
    exit(ZA_MALO_PAMIECI);
  }
    element->wartosc = liczba;
    element->nastepny = NULL;

    if (iterator == NULL){//pusta lista
        glowa = element;
        return;
    }

    while (iterator->nastepny != NULL){
        iterator = iterator->nastepny;
    }

    iterator->nastepny = element;

}

/**********************************************************/

int pop_front() {//zwroc wartosc z poczatku listy i usun pierwszy element
int zwracana_wart = -1;
  Wezel *schowek = NULL;

  if (glowa == NULL) {
     return -1;
  }

  zwracana_wart = glowa->wartosc;
  schowek = glowa;
  glowa = glowa->nastepny;
  free(schowek);
  return zwracana_wart;
}

/**********************************************************/

//2pkt
int remove_last(){//zroc wartosc z ostatniego elementu i usun ostatni element
  Wezel *iterator = glowa;
  int zwrac_wart = -1;

  if(glowa->nastepny == NULL) {
    zwrac_wart = glowa->wartosc;
    glowa = NULL;
    free(glowa);
  }

  while(iterator->nastepny != NULL) {
    iterator = iterator->nastepny;
    if(iterator->nastepny->nastepny == NULL) {
      zwrac_wart = iterator->nastepny->wartosc;
      iterator->nastepny = NULL;
      free(iterator->nastepny);
    }
  }
  return zwrac_wart;
}

/**********************************************************/
//2pkt
int remove_by_index(int indx){//zwroc wartosc elementu wskazywanego przez index i usun ten element
  int i = 0;
  int zwrac_wart = -1;
  Wezel *iterator = glowa;

  if(indx == 0) {
    zwrac_wart = pop_front();
  }

  while(iterator->nastepny != NULL) {
    if(indx-1 == i) {
      zwrac_wart = iterator->nastepny->wartosc;
      free(iterator->nastepny);
      iterator->nastepny = iterator->nastepny->nastepny;
      return zwrac_wart;
    }
    i++;
    iterator = iterator->nastepny;
  }

  if(indx > i) {
    printf("Brak elementu w liscie\n");
    exit(-1);
  }

  return zwrac_wart;
}

/**********************************************************/
//2pkt
void push_front(int liczba) {//wstaw element na poczatek listy
  Wezel* element;
  Wezel* iterator = glowa;
  Wezel *schowek = NULL;

  if( (element = (Wezel*)malloc(sizeof(Wezel))) == NULL ) {
    fprintf(stderr, "Za mało pamięci!\n");
    exit(ZA_MALO_PAMIECI);
  }

  element->wartosc = liczba;

  if (iterator == NULL){//pusta lista
    glowa = element;
    return;
  }

  if (iterator != NULL){
    element->wartosc = liczba;
    element->nastepny = glowa;
    glowa = element;
    return;
  }
}

/**********************************************************/


int main(){
  //proszę samemu napisać funkcję main.
  push_back(0);
  push_back(1);
  push_back(2);
  push_back(3);
  push_back(4);
  push_back(5);
  push_back(6);
  wypisz();

  int val;
  val = remove_last();
  printf("zwrac_wart: %d\n", val);
  printf("\n");
  wypisz();

  int rval = remove_by_index(3);
  printf("remove_by_idx_val: %d\n", rval);
  printf("\n");
  wypisz();

  int vali = remove_by_index(1);
  printf("remove_by_idx_val: %d\n", vali);
  printf("\n");
  wypisz();

  push_front(1);
  push_front(8);
  push_front(3);
  push_front(4);
  wypisz();

  return 0;
}
