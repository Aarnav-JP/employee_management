#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#define endl "\n"
using namespace std;
struct s_employee
{
    string employee_name;
    int employee_age;
    string employee_designation;
    float employee_salary;
};

void flush()
{
    int c = 0;
    while ((c == getchar()) != '\n' and c != EOF)
        ;
}
int main()
{
    FILE *employeefile;
    FILE *employeefiletmp;
    int choice;
    string next_choice;
    string employeename;
    long long int sizeofemployeerecord;
    struct s_employee employee;
    const char *filename = "EMPLOYEE.DAT";

    //attempt to open a .dat file straightaway
    //if the file doesnt exit then we create one

    employeefile = fopen(filename, "rb+");

    if (employeefile == NULL)
    {
        employeefile = fopen(filename, "wb+");

        if (employeefile == NULL)
            cout << "Unable to open " << filename;
        exit(1);
    }
    sizeofemployeerecord = sizeof(employee);

    while (1)
    {
        cout << "==================================================" << endl;
        cout << "1. Add new employee." << endl;
        cout << "2. Modify employee data." << endl;
        cout << "3. Delete an employee." << endl;
        cout << "4. Print employee details." << endl;
        cout << "5. To Exit." << endl;
        fflush(stdin);

        cout << "Enter the operation of your choice: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            fseek(employeefile, 0, SEEK_END);
            next_choice = "y";
            while (next_choice == "y")
            {

                cout << "=================================================" << endl;
                cout << "Enter the name of the employee: ";
                getline(cin >> ws, employee.employee_name);
                cout << endl;
                cout << "Enter the age of the employee: ";
                cin >> employee.employee_age;
                cout << endl;
                cout << "Enter the designation of the employee: ";
                getline(cin >> ws, employee.employee_designation);
                cout << endl;
                cout << "Enter the salary of the employee: ";
                cin >> employee.employee_salary;
                cout << endl;
                fwrite(&employee, sizeofemployeerecord, 1, employeefile);
                cout << "The data for " << employee.employee_name << " has been recorded." << endl;
                cout << "Would you like to enter new record? (y / n): ";
                cin >> next_choice;
                cout << "=================================================" << endl;
            }

            break;
        case 2:
            cout << "=================================================" << endl;
            next_choice = "y";
            while (next_choice == "y")
            {
                cout << "Enter the employee name you want to modify: ";
                getline(cin >> ws, employeename);
                // rewind(employeefile);
                //other way of doing above thing
                fseek(employeefile, 0L, SEEK_SET);
                while (fread(&employee, sizeof(employee), 1, employeefile) == 1)
                {
                    if (employee.employee_name == employeename)
                    {
                        cout << "Enter the name of new employee: ";
                        getline(cin >> ws, employee.employee_name);
                        cout << endl;
                        cout << "Enter the age of new employee: ";
                        cin >> employee.employee_age;
                        cout << endl;
                        cout << "Enter the designation of new employee: ";
                        getline(cin >> ws, employee.employee_designation);
                        cout << endl;
                        cout << "Enter the salary of new employee: ";
                        cin >> employee.employee_salary;
                        cout << endl;

                        fseek(employeefile, -sizeofemployeerecord, SEEK_CUR);
                        fwrite(&employee, sizeofemployeerecord, 1, employeefile);
                        break;
                    }
                }
                cout << endl;
                cout << "The data of " << employeename << " has been modified." << endl;
                cout << "Would you like to modify another record ? (y / n): ";
                cin >> next_choice;
            }
            break;
        case 3:
            next_choice = "y";
            while (next_choice == "y")
            {
                cout << "Enter the employee Name you want to delete: ";
                getline(cin >> ws, employeename);

                employeefiletmp = fopen("temp.dat", "wb");
                rewind(employeefile);
                while (fread(&employee, sizeofemployeerecord, 1, employeefile) == 1)
                {
                    if (employee.employee_name != employeename)
                    {
                        fwrite(&employee, sizeofemployeerecord, 1, employeefiletmp);
                    }
                }
                fclose(employeefile);
                fclose(employeefiletmp);
                remove("EMPLOYEE.DAT");
                rename("temp.dat", "EMPLOYEE.DAT");
                fopen("EMPLOYEE.DAT", "wb+");

                cout << "The data of " << employeename << " has been deleted." << endl;
                cout << endl;
                cout << "Would you like to delete another record ? (y / n): ";
                cin >> next_choice;
            }

            break;
        case 4:
            fseek(employeefile, 0, SEEK_SET);
            while (fread(&employee, sizeofemployeerecord, 1, employeefile) == 1)
            {
                cout << "=================================================" << endl;
                cout << "Employee name: " << employee.employee_name << endl;
                cout << "Age of Employee is: " << employee.employee_age << endl;
                cout << "Designation of employee :" << employee.employee_designation << endl;
                cout << "Salary of Employee: " << employee.employee_salary << endl;
                cout << "=================================================" << endl;
            }
            break;
        case 5:
            exit(0);

        default:
            break;
        }
    }

    return 0;
}