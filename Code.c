#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
    char name[20];
    char gender[10];
    int age;
    int eid;
    float salary;
    char mobile[15];
    char address[20];
};

typedef struct Employee Employee;
Employee emp;
FILE *fp, *ft;
int recsize = sizeof(Employee);

void insert_record()
{
    int flag = 0, id;

    printf("Enter EID:");
    scanf("%d", &id);

    rewind(fp);
    while (fread(&emp, recsize, 1, fp) == 1)
    {
        if (emp.eid == id)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        fseek(fp, 0, SEEK_END);

        emp.eid = id;
        printf("Enter Name:");
        fflush(stdin);
        gets(emp.name);

        printf("Enter Gender:");
        fflush(stdin);
        gets(emp.gender);

        printf("Enter Salary:");
        scanf("%f", &emp.salary);

        printf("Enter Mobile Number:");
        fflush(stdin);
        gets(emp.mobile);

        printf("Enter Address:");
        fflush(stdin);
        gets(emp.address);

        fwrite(&emp, recsize, 1, fp);
        printf("\nRecord Saved Successfully...");
    }
    else
    {
        printf("\nSorry! Employee Id already exists...");
    }
}

void display_record()
{
    rewind(fp);
    printf("\nEID\tName\tGender\tSalary\tAddress\t  Mobile");
    printf("\n---------------------------------------------------------");

    while (fread(&emp, recsize, 1, fp) == 1)
    {
        printf("\n%d\t%s\t%s\t%.0f\t%s\t %s", emp.eid, emp.name, emp.gender, emp.salary, emp.address, emp.mobile);
    }
    printf("\n---------------------------------------------------------");
}

void search_record()
{
    char streid[15], str[15];
    int flag = 0;

    printf("\nEnter Employee ID or Mobile Number:");
    fflush(stdin);
    gets(str);

    rewind(fp);
    while (fread(&emp, recsize, 1, fp) == 1)
    {
        sprintf(streid, "%d", emp.eid);

        if (strcmp(emp.mobile, str) == 0)
        {
            flag = 1;
            printf("\nEID\tName\tGender\tSalary\tAddress\t  Mobile");
            printf("\n---------------------------------------------------------");
            printf("\n%d\t%s\t%s\t%.0f\t%s\t %s", emp.eid, emp.name, emp.gender, emp.salary, emp.address, emp.mobile);
            printf("\n");
            printf("\nRecord Search Successfull...");
            break;
        }
        else if (strcmp(streid, str) == 0)
        {
            flag = 1;
            printf("\nEID\tName\tGender\tSalary\tAddress\t  Mobile");
            printf("\n---------------------------------------------------------");
            printf("\n%d\t%s\t%s\t%.0f\t%s\t %s", emp.eid, emp.name, emp.gender, emp.salary, emp.address, emp.mobile);
            printf("\n");
            printf("\nRecord Search Successfull...");
            break;
        }
    }

    if (flag == 0)
    {
        printf("\nSorry! Employee's Record not found.");
    }
}

void delete_record()
{
    int id, flag = 0;
    Employee temp;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    // Open a temporary file for writing
    ft = fopen("temp.dat", "wb+");

    if (ft == NULL)
    {
        printf("Error while creating temporary file.");
        exit(2);
    }

    rewind(fp);

    while (fread(&emp, recsize, 1, fp) == 1)
    {
        if (emp.eid != id)
        {
            fwrite(&emp, recsize, 1, ft);
        }
        else
        {
            flag = 1; 
        }
    }

    fclose(ft);
    fclose(fp);

    // Replace the original file with the temp file
    remove("emp.dat");
    rename("temp.dat", "emp.dat");

    fp = fopen("emp.dat", "rb+");// Reopens file for further operations

    if (flag == 1)
    {
        printf("\nRecord deleted successfully...");
    }
    else
    {
        printf("\nSorry! No record found with the given Employee ID.");
    }
}

void modify_record()
{
    int flag = 0, id;

    printf("Enter Employee Id to Modify: ");
    scanf("%d", &id);

    rewind(fp);

    while (fread(&emp, recsize, 1, fp) == 1)
    {
        if (id == emp.eid)
        {
            printf("Enter New EID:");
            scanf("%d", &emp.eid);

            printf("Enter New Name:");
            fflush(stdin);
            gets(emp.name);

            printf("Enter New Gender:");
            fflush(stdin);
            gets(emp.gender);

            printf("Enter New Salary:");
            scanf("%f", &emp.salary);

            printf("Enter New Mobile Number:");
            fflush(stdin);
            gets(emp.mobile);

            printf("Enter New Address:");
            fflush(stdin);
            gets(emp.address);

            fseek(fp, -recsize, SEEK_CUR);
            fwrite(&emp, recsize, 1, fp);
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        printf("\nRecord Modified Successfully...");
    }
    else
    {
        printf("\nEmployee's ID does not exists...");
    }
}

int main()
{
    int choice;

    fp = fopen("emp.dat", "rb+");

    if (fp == NULL)
    {
        printf("File does not exists...");
        fp = fopen("emp.dat", "wb+");

        if (fp == NULL)
        {
            printf("\nError while creating file.");
            exit(0);
        }
        else
        {
            printf("\nFile created successfully...");
        }
    }
    else
    {
        printf("\nFile opened successfully...");
    }

    do
    {
        printf("\n\nPress 1 for Insert Record");
        printf("\nPress 2 for Display Record");
        printf("\nPress 3 for Search Record");
        printf("\nPress 4 for Delete Record");
        printf("\nPress 5 for Modify Record");
        printf("\nPress 0 for Exit");

        printf("\n\nEnter your choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert_record();
            break;

        case 2:
            display_record();
            break;

        case 3:
            search_record();
            break;

        case 4:
            delete_record();
            break;

        case 5:
            modify_record();
            break;

        case 0:
            exit(0);
            break;

        default:
            printf("Invalid choice.");
            break;
        }
    } while (1);

    return 0;
}