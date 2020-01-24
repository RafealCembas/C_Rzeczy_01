#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
        int licznik;
        int mianownik;
}wymierna;

wymierna wynik;

int nwd(int a, int b) {
        if(a < 0)
                a = -a;
        if(b < 0)
                b = -b;
        if(b == 0)
                return a;
        else
                return nwd(b, (a%b));
}

wymierna skroc(wymierna wynik) {
        int gora, dol, podz;

        podz = nwd(wynik.licznik, wynik.mianownik);

        gora = wynik.licznik / podz;
        dol = wynik.mianownik / podz;

        wynik.licznik = gora;
        wynik.mianownik = dol;
        return wynik;
}

wymierna suma(wymierna A, wymierna B) {
        wynik.licznik = A.licznik * B.mianownik + B.licznik * A.mianownik;
        wynik.mianownik = A.mianownik * B.mianownik;

        wynik = skroc(wynik);
        return wynik;
}

wymierna roznica(wymierna A, wymierna B) {
        wynik.licznik = A.licznik * B.mianownik - B.licznik * A.mianownik;
        wynik.mianownik = A.mianownik * B.mianownik;

        wynik = skroc(wynik);
        return wynik;
}

wymierna iloczyn(wymierna A, wymierna B) {
        wynik.licznik = A.licznik * B.licznik;
        wynik.mianownik = A.mianownik * B.mianownik;

        wynik = skroc(wynik);
        return wynik;
}

wymierna iloraz(wymierna A, wymierna B) {
        wynik.licznik = A.licznik * B.mianownik;
        wynik.mianownik = A.mianownik * B.licznik;

        if(wynik.mianownik == 0) {
                printf("Dzielenie przez 0!\n");
                exit(0);
        }
        wynik = skroc(wynik);
        return wynik;
}

void wypiszWymierna(wymierna A) {
        if(A.mianownik == 0)
                printf("Dzielenie przez 0!\n");
        else
                printf("%d/%d\n", A.licznik, A.mianownik);
}

int main() {
        wymierna pierwsza, druga, trzecia, wynik;

        pierwsza.licznik = 2;
        pierwsza.mianownik = 3;
        wypiszWymierna(pierwsza);

        druga.licznik = 3;
        druga.mianownik = 4;
        wypiszWymierna(druga);

        wynik = suma(pierwsza, druga);
        wypiszWymierna(wynik);

        wynik = roznica(pierwsza, druga);
        wypiszWymierna(wynik);

        wynik = iloczyn(pierwsza, druga);
        wypiszWymierna(wynik);

        wynik = iloraz(pierwsza, druga);
        wypiszWymierna(wynik);

        trzecia.licznik = 2;
        trzecia.mianownik = 4;

        wynik = skroc(trzecia);
        wypiszWymierna(wynik);
}
