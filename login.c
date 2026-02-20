#include <stdio.h>
#include <string.h>
#include <conio.h>   // for getch()

void hideInput(char *password) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();   // get character without displaying

        // If Enter is pressed
        if (ch == 13) {   // 13 = Enter in conio
            password[i] = '\0';
            break;
        }
        // If Backspace is pressed
        else if (ch == 8) {   // 8 = Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // erase last *
            }
        }
        else {
            if (i < 29) {   // prevent overflow (password size is 30)
                password[i++] = ch;
                printf("*");
            }
        }
    }
}

void loginPage() {
    char username[20];
    char password[30];

    char realUser[] = "mrc2K5";
    char realPass[] = "pineapple900C";

    while (1) {
        printf("====== LOGIN PAGE =======\n");

        printf("Enter Username: ");
        scanf("%19s", username);

        printf("Enter Password: ");
        hideInput(password);

        printf("\n");

        int userVal1 = strcmp(username, realUser);
        int userVal2 = strcmp(password, realPass);

        if (userVal1 == 0 && userVal2 == 0) {
            printf("Login Successfully\n");
            break;
        }
        else if (userVal1 != 0 && userVal2 != 0) {
            printf("Invalid Username and Password!\n");
        }
        else if (userVal1 != 0) {
            printf("Invalid Username!\n");
        }
        else {
            printf("Invalid Password!\n");
        }
    }
}