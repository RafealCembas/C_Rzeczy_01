#include <stdio.h>                                                                                                                                                               
int j, k;
int *ptr;
int main(void)
{
  j = 1;
  k = 2;
  ptr = &k;
  printf("\n");

  printf("1. j ma wartosc %d i jest przechowywany pod adresem %p\n", j, &j);//%p pointer address
  printf("2. k ma wartosc %d i jest przechowywany pod adresem %p\n", k, &k);
  printf("3. ptr ma wartosc %p i jest przechowywany po adresem %p\n", ptr, &ptr);
  printf("4. Wartosc, na ktora wskazyje ptr to  %d\n", *ptr);
  printf("5. Rozmiar int  %ld bajtow\n", sizeof(int));
  printf("\n");
  printf("6. Zobacz roznice: ptr: %p,  ptr + 1: %p\n", ptr, ptr + 1);
}
