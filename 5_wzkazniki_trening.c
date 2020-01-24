#include<stdio.h>                                                                                                                                                 
/*czy program sie skompiluje???*/
void zmien(int *a){
  *a  = *a + 2;
}

main(){
  int a = 3;
  int *ptr = &a;

  zmien(a);/*przekazane przez wartosć czy przez wskaźnik?*/
  printf("zmienna a po pierwszym wywolaniu = %d\n", a);

  zmien(*ptr);/*przekazane przez wartosć czy przez wskaźnik?*/
  printf("zmienna a po drugim wywolaniu = %d\n", a);

  zmien(&a);/*przekazane przez wartosć czy przez wskaźnik?*/
  printf("zmienna a po trzecim wywolaniu = %d\n", a);

  zmien(ptr);/*przekazane przez wartosć czy przez wskaźnik?*/
  printf("zmienna a po czwartym wywolaniu = %d\n", a);
}
