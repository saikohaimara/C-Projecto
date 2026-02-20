#include <stdio.h>
#include <ctype.h>

void array1()  {
    int a2[2][5];
    int a11, a12;
    char decision1;

    while(decision1!='N'){
    int start=0, sum=0;
    printf("\n2. Sum of Two Dimensional Array\n");
    printf("Enter 10 Numbers:\n");

    for (a11 = 0; a11 < 2; a11++) {
        for (a12 = 0; a12 < 5; a12++) {
            start++;
            printf("#%d No. : ",start);
            scanf("%d", &a2[a11][a12]);
        }
    }

    for (a11 = 0; a11 < 2; a11++) { //0 &1 =2
        for (a12 = 0; a12 < 5; a12++) { //0-4 =5
            sum += a2[a11][a12];
        }
    }

    printf("Sum of the arrays is: %d\n", sum);
    printf("Do you wish to Continue? Y/N: ");
    scanf(" %c",&decision1 );
    decision1= toupper(decision1);
        if(decision1=='Y'){

        }
        else {
            break;
        }  
    }     
}


