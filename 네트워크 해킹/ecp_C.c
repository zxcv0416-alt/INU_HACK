#include <stdio.h>

int main() {

    int num1;

    printf("숫자1 : ");
    scanf("%d", &num1);
     
    printf("일의자리 숫자는 %d\n", num1 % 10);
}