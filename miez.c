#include <stdio.h>
#include <stdlib.h>


int main(void){
    char tomb[20] = {"elso", "masodik"};
    char test[20] = {"egy", "ketto"};

    for (int i = 0; i < 20; i++)
    {
        printf("%c %c", tomb[i], test[i]);
    }
    
    return 0;
}