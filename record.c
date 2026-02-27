#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    int id;
    char lastname[50];
    char firstname[50];
    int age;
    char course[50];
    char sub1[50];
    double grade1;
    char sub2[50];
    double grade2;
} pluckerton;


// Flush stdin completely before every fgets call
void flushInput(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



int getLastID() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        return 100000;  // first ID if file does not exist
    }

    int id, age;
    char lastname[50], firstname[50], course[50], sub1[50], sub2[50];
    double grade1, grade2;

    int lastID = 99999;  // so first becomes 100000

    while (fscanf(fp,"%d|%49[^|]|%49[^|]|%d|%49[^|]|%49[^|]|%lf|%49[^|]|%lf",
        &id, lastname, firstname, &age, course, sub1, &grade1, sub2, &grade2) == 9)
    {
        if (id > lastID)
            lastID = id;
    }

    fclose(fp);
    return lastID + 1;   // next available ID
}


void displayESP(pluckerton student[], int count){
    printf("\n+--------+--------------------+--------------------+-----+----------+----------+-------+----------+-------+\n");
    printf("| %-6s | %-18s | %-18s | %-3s | %-8s | %-8s | %-5s | %-8s | %-5s |\n",
           "ID", "Last Name", "First Name", "Age", "Course", "Sub1", "G1", "Sub2", "G2");
    printf("+--------+--------------------+--------------------+-----+----------+----------+-------+----------+-------+\n");

    for (int a = 0; a < count; a++)
    {
        printf("| %06d | %-18s | %-18s | %-3d | %-8s | %-8s | %-5.2f | %-8s | %-5.2f |\n",
               student[a].id,
               student[a].lastname,
               student[a].firstname,
               student[a].age,
               student[a].course,
               student[a].sub1,
               student[a].grade1,
               student[a].sub2,
               student[a].grade2);
    }
    printf("+--------+--------------------+--------------------+-----+----------+----------+-------+----------+-------+\n");
}


void displayAllFromFile(){
    pluckerton student[200];
    int count = 0;

    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL){
        printf("No records found.\n");
        return;
    }

    while(count < 200 && fscanf(fp,"%d|%49[^|]|%49[^|]|%d|%49[^|]|%49[^|]|%lf|%49[^|]|%lf",
        &student[count].id,
        student[count].lastname,
        student[count].firstname,
        &student[count].age,
        student[count].course,
        student[count].sub1,
        &student[count].grade1,
        student[count].sub2,
        &student[count].grade2) == 9)
    {
        count++;
    }

    fclose(fp);

    if(count == 0){
        printf("No records in file.\n");
        return;
    }

    displayESP(student, count);
}


void searchID()
{
    pluckerton student[100];
    int count = 0;
    int searchid;
    int found = 0;

    FILE *fp = fopen("students.txt", "r"); //--FILENAME
    if (fp == NULL) {
        printf("No records found (cannot open students.txt).\n");
        return;
    }

    // Read pipe-delimited format: id|lastname|firstname|age|course|sub1|grade1|sub2|grade2
    while (count < 100 && fscanf(fp, "%d|%49[^|]|%49[^|]|%d|%49[^|]|%49[^|]|%lf|%49[^|]|%lf",
           &student[count].id,
           student[count].lastname,
           student[count].firstname,
           &student[count].age,
           student[count].course,
           student[count].sub1,
           &student[count].grade1,
           student[count].sub2,
           &student[count].grade2) == 9)
    {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("No records loaded from file.\n");
        return;
    }

    printf("\nEnter ID to search: ");
    scanf("%d", &searchid);
    flushInput();

    for (int a = 0; a < count; a++) {
        if (student[a].id == searchid) {
            found = 1;
            printf("\n========== STUDENT FOUND ==========\n");
            printf("ID:         %06d\n", student[a].id);
            printf("Last Name:  %s\n", student[a].lastname);
            printf("First Name: %s\n", student[a].firstname);
            printf("Age:        %d\n", student[a].age);
            printf("Course:     %s\n", student[a].course);
            printf("Subject 1:  %s\n", student[a].sub1);
            printf("Grade 1:    %.2f\n", student[a].grade1);
            printf("Subject 2:  %s\n", student[a].sub2);
            printf("Grade 2:    %.2f\n", student[a].grade2);
            break;
        }
    }

    if (!found) {
        printf("ID not found.\n");
    }
}

void StudentRecord(){

   // srand(time(NULL));
    //int randomNum = rand() % 900000 + 100000;
    int randomNum = getLastID();

    FILE *fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int n;
    printf("\nHow many students to enter? ");
    scanf("%d", &n);
    flushInput(); // clear leftover \n after scanf

    if (n <= 0 || n > 100) {
        printf("Invalid number.\n");
        fclose(fp);
        return;
    }

    pluckerton *student = (pluckerton *)malloc(n * sizeof(pluckerton));
    if (student == NULL) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }

    for (int a = 0; a < n; a++)
    {
        student[a].id = randomNum++;

        printf("\n============================\n");
        printf("Student %d of %d\n", a + 1, n);
        printf("ID No: %06d\n", student[a].id);

        // Use scanf %s for single-word fields (no spaces expected) to avoid newline issues
        printf("Enter First Name: ");
        scanf(" %49[^\n]", student[a].firstname);
        flushInput();

        printf("Enter Last Name: ");
        scanf(" %49[^\n]", student[a].lastname);
        flushInput();

        printf("Enter Age: ");
        scanf("%d", &student[a].age);
        flushInput();

        printf("Enter Course: ");
        scanf(" %49[^\n]", student[a].course);
        flushInput();

        printf("Enter Subject 1: ");
        scanf(" %49[^\n]", student[a].sub1);
        flushInput();

        printf("Enter Grade 1: ");
        scanf("%lf", &student[a].grade1);
        flushInput();

        printf("Enter Subject 2: ");
        scanf(" %49[^\n]", student[a].sub2);
        flushInput();

        printf("Enter Grade 2: ");
        scanf("%lf", &student[a].grade2);
        flushInput();

        printf("\nCredentials Have Been Recorded!\n");

        // Write cleanly — all fields are single tokens, space-separated
        fprintf(fp, "%d|%s|%s|%d|%s|%s|%.2f|%s|%.2f\n",
                student[a].id,
                student[a].lastname,
                student[a].firstname,
                student[a].age,
                student[a].course,
                student[a].sub1,
                student[a].grade1,
                student[a].sub2,
                student[a].grade2);
    }

    fclose(fp);
    free(student);
    displayAllFromFile();
}

void RECORD(){
    int scans = 0;
    while(scans != 4){
        printf("\n======= RECORD MENU =======\n");
        printf("1. Search\n");
        printf("2. Enter Record\n");
        printf("3. Display Records\n");
        printf("4. EXIT\n");
        printf("Enter Selection: ");
        scanf("%d", &scans);
        flushInput();

        switch(scans){
            case 1:
                searchID();
                break;
            case 2:
                StudentRecord();
                break;
            case 3:
              displayAllFromFile();
            break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }


}
