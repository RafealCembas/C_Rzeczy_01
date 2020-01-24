#include <stdio.h>
int main(void){

  int my_array[] = {1,23,17,4,-5,100};

  int i;
  int * ptr;
  ptr = &my_array[0]; //ustaw wskaznik na pierwszy element tablicy 
  //ptr = my_array;   // nazwa tablicy to adres jej pierwszego elementu

  printf("\n\n");

    printf("1. my_array[0] = %d\n", my_array[0]);
    printf("2. *ptr = %d\n ", *ptr);

    printf("3. *ptr*3 = %d\n\n ", *ptr*3);
    printf("4. *ptr = %d\n ", *ptr);

    printf("5. *ptr++ = %d\n\n ", *ptr++);
    printf("6. *ptr = %d\n ", *ptr);

    printf("7. *ptr-- = %d\n\n ", *ptr--);
    printf("8. *ptr = %d\n ", *ptr);

    printf("9. *ptr+1 = %d\n\n ", *ptr+1);
    printf("10. *ptr = %d\n ", *ptr);

    printf("11. *(ptr+1) = %d\n\n ", *(ptr+1));
    printf("12. *ptr = %d\n ", *ptr);

    printf("13. *ptr :P = %d\n ", *&*ptr+1*3);
}

