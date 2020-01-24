#include <stdio.h>                                                                                                                                           
#include <string.h>


int main(void){
  char strA[80] = "A string to be used for demonstration purposes";
  char strB[80];

  char *pA;
  char *pB;

  puts(strA); //int puts(const char *s), Funkcja wysyła na standardowe wyjście napis s, a następnie znak nowej linii.;
  pA = strA;
  puts(pA);

  pB = strB;
  putchar('\n');

  while(*pA != '\0'){
    *pB++ = *pA++;
  }

  *pB = '\0';
  puts(strB);
  return 0;
}
