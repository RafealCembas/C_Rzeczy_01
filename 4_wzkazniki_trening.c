#include <stdio.h>
void zmien(int a, int *pb)
{
  printf("W funkcji zmienne = %d, %d\n", a, *pb);
  a = a + 2; /* Zmieniona zostaje kopia */
  *pb = *pb + 2; /* Docelowo zmieniona zostaje zmienna */
  printf("W funkcji zmienne + 2 = %d, %d\n", a, *pb);
  /* Kopia zmiennej i wskaźnika znikają przy wyjściu z 
  funkcji, ale zostaje zmieniona wartość drugiej zmiennej */                                                                                                      
}

int main()
{ 
  int a = 5, b = 6;
  printf("W programie zmienne = %d, %d\n", a, b);
  zmien(a, &b); /* Do funkcji trafia kopia zmiennej */
  printf("W programie po zmien = %d, %d\n", a, b);
}
