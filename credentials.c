#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sqlext.h>
#include <string.h>

typedef struct {
    int ID;
    char FirstName[50];
    char LastName[50];
    int age;
    char Subject1[50];
    float grade1;
    char Subject2[50];
    float grade2;
    char Subject3[50];
    float grade3;
} DATACOLLECTION;

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    DATACOLLECTION student;
    char buffer[100];

    // ---------------- Input Section ----------------
    printf("Enter Student ID: ");
    fgets(buffer, sizeof(buffer), stdin);
    student.ID = atoi(buffer);

    printf("Enter First Name: ");
    fgets(student.FirstName, sizeof(student.FirstName), stdin);
    removeNewline(student.FirstName);

    printf("Enter Last Name: ");
    fgets(student.LastName, sizeof(student.LastName), stdin);
    removeNewline(student.LastName);

    printf("Enter Age: ");
    fgets(buffer, sizeof(buffer), stdin);
    student.age = atoi(buffer);

    printf("Enter Subject 1: ");
    fgets(student.Subject1, sizeof(student.Subject1), stdin);
    removeNewline(student.Subject1);
    printf("Enter Grade 1: ");
    fgets(buffer, sizeof(buffer), stdin);
    student.grade1 = atof(buffer);

    printf("Enter Subject 2: ");
    fgets(student.Subject2, sizeof(student.Subject2), stdin);
    removeNewline(student.Subject2);
    printf("Enter Grade 2: ");
    fgets(buffer, sizeof(buffer), stdin);
    student.grade2 = atof(buffer);

    printf("Enter Subject 3: ");
    fgets(student.Subject3, sizeof(student.Subject3), stdin);
    removeNewline(student.Subject3);
    printf("Enter Grade 3: ");
    fgets(buffer, sizeof(buffer), stdin);
    student.grade3 = atof(buffer);

    // ---------------- ODBC Section ----------------
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLHSTMT hStmt;
    SQLRETURN ret;
    char query[1000];

    // Allocate environment
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);

    // Allocate connection
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Connect to SQL Server (replace UID/PWD)
    ret = SQLDriverConnect(
        hDbc,
        NULL      ,
        (SQLCHAR*)"DRIVER={ODBC Driver 18 for SQL Server};SERVER=DESKTOP-3LKBAHE\\SQLEXPRESS;"
                  "DATABASE=TestDB;Trusted_Connection=Yes",
                
        SQL_NTS,
        NULL,
        0,
        NULL,
        SQL_DRIVER_COMPLETE
    );

    if (SQL_SUCCEEDED(ret)) {
        printf("Connected to SQL Server!\n");
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        sprintf(query,
            "INSERT INTO Students VALUES (%d,'%s','%s',%d,'%s',%f,'%s',%f,'%s',%f)",
            student.ID, student.FirstName, student.LastName, student.age,
            student.Subject1, student.grade1,
            student.Subject2, student.grade2,
            student.Subject3, student.grade3
        );

        ret = SQLExecDirect(hStmt, (SQLCHAR*)query, SQL_NTS);
        if (SQL_SUCCEEDED(ret))
            printf("Data inserted successfully!\n");
        else
            printf("Insert failed!\n");

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        SQLDisconnect(hDbc);
    } else {
        printf("Connection failed!\n");
    }

    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
