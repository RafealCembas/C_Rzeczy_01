#include <stdio.h>
#include <stdlib.h>
#define ZA_MALO_PAMIECI -1
/* proszę uzupelnic kod
proszę użyć rekurencji w każdej funkcji*/

int lh = 0, ph = 0, h = 0;

typedef struct wezel {
    int wartosc;
    struct wezel *lewy, *prawy;

} Wezel;
Wezel *korzen = NULL;

Wezel *nowyWezel(int liczba){
  Wezel *nowy;

  if( (nowy = (Wezel*)malloc(sizeof(Wezel))) == NULL ) {
    fprintf(stderr, "Za mało pamięci!\n");
    exit(ZA_MALO_PAMIECI);
  }
  nowy->wartosc = liczba;
  nowy->lewy = NULL;
  nowy->prawy = NULL;

  return nowy;
}

Wezel *wstaw(Wezel *wezelek, int liczba){

  if (wezelek==NULL){
      wezelek = nowyWezel(liczba);
  }
  else{
      if (wezelek->wartosc > liczba){
          wezelek->lewy = wstaw(wezelek->lewy, liczba);
      }
      else{
          wezelek->prawy = wstaw(wezelek->prawy, liczba);
      }
  }
  return wezelek;
}
void preorder(Wezel *wezelek){
        /*wypisz preorder (korzen, lewe, prawe)*/
  printf("%d\n", wezelek->wartosc);
  if (wezelek->lewy !=NULL)
     preorder(wezelek->lewy);

  if (wezelek->prawy !=NULL)
     preorder(wezelek->prawy);
}


void inorder(Wezel *wezelek){//1pkt
        /*wypisz inorder (lewe, korzen, prawe)*/
        if (wezelek->lewy != NULL)
                inorder(wezelek->lewy);
        printf("%d\n", wezelek->wartosc);
        if (wezelek->prawy != NULL)
                inorder(wezelek->prawy);
}

void postorder(Wezel *wezelek){//1pkt
        /*wypisz postorder (lewe, prawe, korzen)*/
        if (wezelek->lewy != NULL)
                postorder(wezelek->lewy);
        if (wezelek->prawy != NULL)
                postorder(wezelek->prawy);
        printf("%d\n", wezelek->wartosc);
}

Wezel* szukaj(Wezel* wezelek, int liczba){//2pkt
        /*znajdz i zwroc element o podanym kluczu*/
        if(wezelek != NULL) {

                if(wezelek->wartosc == liczba)
                        return wezelek;

                else if(wezelek->lewy != NULL) {
                        if(wezelek->wartosc == liczba)
                                return wezelek;
                        szukaj(wezelek->lewy, liczba);
                }
                else if(wezelek->prawy != NULL) {
                        if(wezelek->wartosc == liczba);
                                return wezelek;
                        szukaj(wezelek->prawy, liczba);
                }
        }
        else
                return wezelek;
}
int wysokosc(Wezel *wezelek) {//2pkt
        /*oblicz i zwroc wysokosc drzewa*/

        if(wezelek != NULL) {
                if(wezelek->lewy != NULL) {
                        lh++;
                        wysokosc(wezelek->lewy);
                }
                if(wezelek->prawy != NULL) {
                        ph++;
                        wysokosc(wezelek->prawy);
                }
        }
        else {
                printf("Brak wezla!\n");
                exit(-1);
        }
        if(lh > ph)
                h = lh;
        else
                h = ph;
        return h;

}

Wezel *znajdzMin(Wezel *wezelek){//2pkt
        /*znajdz najmniejszy element drzewa*/
        if(wezelek != NULL) {
                if(wezelek->lewy != NULL) {
                        return znajdzMin(wezelek->lewy);
                }
        }
        return wezelek;
}
int main() {
        Wezel *element = NULL;
        int i, liczba;

        int dane[] = {10,5,15,3,13,18,1,4,16,17};

        for(i = 0; i < 10; i++) {
                korzen = wstaw(korzen, dane[i]);
        }

        postorder(korzen);
        printf("Jaki element chcesz znalezc? \n");
        scanf("%d", &liczba);

        element = szukaj(korzen, liczba);
        if(element)
                printf("Znaleziono element, ktory zawiera wartosc: %d\n", element->wartosc);
        else
                printf("Nie znaleziono elementu, ktory zwiera wartosc: %d\n", liczba);

        int wys;
        wys = wysokosc(korzen);
        printf("Wysokosc drzewa: %d\n", wys);

        element = znajdzMin(korzen);
        printf("Minimum: %d\n", element->wartosc);

        return 0;
}
