#include <stdio.h>
#include "TheHeader.h"


int main () {
    int options;

    loginPage();

    while (options!=5){

    printf("\n======MENU=======\n");
    printf("1   Activity 1: Sum of an Array\n");
    printf("2   Unnamed\n");
    printf("3   Unnamed\n");
    printf("4   Unnamed\n");
    printf("5   Exit\n");
    printf("Enter Selection: ");
    scanf("%d", &options);

    
    switch (options){
        case 1:  array1();
                 break;
        case 2:  printf("To Be Announced\n");
                 break;
        case 3: printf("To Be Announced\n");
                 break;
        case 4: printf("To Be Announced\n");
                 break;
        case 5: 
                 break;
        default: printf("Error Selection\n");
                 break;

                     }
                        }       

                        
    printf("Exitting app\n");                    
    printf("Thank you\n");
                 
   
    
    return 0;


    
}