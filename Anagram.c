#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define ROZMIAR 15

bool czyAnagramy(const char *A, const char *B) {
        unsigned literyA['Z' - 'A' + 1];
        unsigned literyB['Z' - 'A' + 1];
        int c = 0, u = 0, spr = 0;

        while(A[c] != '\0') {
                literyA[toupper(A[c]) - 'A']++;
                literyB[toupper(B[c]) - 'A']++;
                spr += A[c] - B[c];

                if(spr != 0)
                        u++;
                else
                        u = 0;
                c++; 
        }

        if(u != 0)
                return false;
        return true;
}

int main(void){
        char slowoA[ROZMIAR], slowoB[ROZMIAR];

        printf("Podaj dwa słowa: ");
        scanf("%s%s", slowoA, slowoB);

        if(czyAnagramy(slowoA, slowoB) )
                printf("To są anagramy\n");
        else
                printf("To nie są anagramy\n");

        return 0;
}
