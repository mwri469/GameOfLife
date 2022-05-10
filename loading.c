#include <stdio.h>

int main()
{
    
    printf("loading\n");
    int i = 0, j = 0;
    int modo = 100000000;
    int y = 1;
    while (y) {
        i++;
        if (!(i % modo)) {
            
            if (j % 4 == 0) {
                printf("\r                   \r");
                
            } else if  (j % 4 == 1) {
                printf(".");
            } else if (j % 4 == 2) {
                printf("   .");
            } else if (j % 4 == 3) {
                printf("   .");
            }
            j++;
        }
        if (i == 20*modo) {
            y = 0;
        }
    }
    printf("\nfinished!! Congrats!!");
    return 0;
}
