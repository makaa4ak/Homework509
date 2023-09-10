#include <iostream>
#include "DZ1.h"
using namespace std;

int main()
{
	int UserChoice;
	bool returnToMain = false;

	while (true)
	{
		PrintMenuMain();
		cout << "\nChoose option: ";
		cin >> UserChoice;
		cin.ignore(255, '\n');

		switch (UserChoice)
		{
		case CodeAddEmployee:
			AddEmployee(pathEmployee);
			break;
		case CodeDelEmployee:
			DelEmployee(pathEmployee, pathTemp);
			break;
		case CodeMenuReport:
			returnToMain = false;
			do
			{
				system("cls");
				PrintMenuReport();
				cout << "\nChoose option: ";
				cin >> UserChoice;
				cin.ignore(255, '\n');
				cout << endl;
				switch (UserChoice)
				{
				case CodePrintAllEmployee:
					PrintAllEmployee(pathEmployee);
					break;
				case CodePrintInfoEmployee:
					PrintInfoEmployee(pathEmployee);
					break;
				case CodeSearchSalaryRange:
					SearchSalaryRange(pathEmployee);
					break;
				case CodeExitReport:
					cout << "Returning to main menu...";
					returnToMain = true;
					break;
				default:
					cout << "You entered the wrong action code. Try again" << endl;
					break;
				}
				if (!returnToMain)
					system("pause");
			} while (!returnToMain);
			break;
		case CodeExitProgram:
			cout << "Thanks for using our program!" << endl;
			return 0;
		default:
			cout << "\nYou entered the wrong action code. Try again";
		}
		cout << endl;
		system("pause");
		system("cls");
	}
}


void PrintMenuMain()
{
	allocation();
	cout << "\tMain menu:" << endl;
	cout << "[" << CodeAddEmployee << "] - Add new employee" << endl;
	cout << "[" << CodeDelEmployee << "] - Delete employee" << endl;
	cout << "[" << CodeMenuReport << "] - Open report menu" << endl;
	cout << "[" << CodeExitProgram << "] - Exit the program" << endl;
	allocation();
}
void PrintMenuReport()
{
	allocation();
	cout << "\tReport options:" << endl;
	cout << "[" << CodePrintAllEmployee << "] - Print full list of employee" << endl;
	cout << "[" << CodePrintInfoEmployee << "] - Print information about the employee" << endl;
	cout << "[" << CodeSearchSalaryRange << "] - Search by salary range" << endl;
	cout << "[" << CodeExitReport << "] - Go back to main menu" << endl;
	allocation();
}


void PrintInfoStruct(Employee point)
{
	allocation();
	printf("Full name: %s %s\n", point.firstName, point.lastName);
	printf("Phone number: %s\n", point.phoneNumber);
	printf("Salary: %f\n", point.salary);
	allocation();
}
char* Lowercase(char* str)
{
	for (int i = 0; i < str[i] != '\0'; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	return str;
}


void AddEmployee(const char pathEmployee[])
{
	allocation();
	FILE* file;
	errno_t code = fopen_s(&file, pathEmployee, "ab");
	if (code == 0)
	{
		Employee point;
		cout << "First name: ";
		cin >> point.firstName;
		cout << "Last name: ";
		cin >> point.lastName;
		bool correctInput = false;
		while (correctInput == false)
		{
			cout << "Phone number: ";
			cin >> point.phoneNumber;
			if (strlen(point.phoneNumber) != 10)
				cout << "Incorrect phone number input. Try again. (Example: 0635635904)" << endl;
			else
				correctInput = true;
		}
		cout << "Salary: ";
		cin >> point.salary;
		fwrite(&point, sizeof(Employee), 1, file);
		fclose(file);
	}
	else
		cout << "Error. Code: " << code << endl;
	allocation();
}
void DelEmployee(const char pathEmployee[], const char pathTemp[])
{
	allocation();
	FILE* file;
	FILE* temp;
	bool isFind = false;

	errno_t fileCode = fopen_s(&file, pathEmployee, "rb");
	errno_t tempCode = fopen_s(&temp, pathTemp, "wb");

	if (fileCode == 0 && tempCode == 0)
	{
		char firstName[SIZE_STR];
		char lastName[SIZE_STR];
		cout << "First name: ";
		cin >> firstName;
		cout << "Last name: ";
		cin >> lastName;

		Lowercase(firstName);
		Lowercase(lastName);

		Employee point;
		while (!feof(file))
		{
			if (fread(&point, sizeof(Employee), 1, file))
			{
				Employee pointTemp = point;
				Lowercase(pointTemp.firstName);
				Lowercase(pointTemp.lastName);
				if (strcmp(firstName, pointTemp.firstName) == 0 && strcmp(lastName, pointTemp.lastName) == 0)
					isFind = true;
				else
					fwrite(&point, sizeof(Employee), 1, temp);
			}
		}
		fclose(file);
		fclose(temp);
	}

	if (isFind)
	{
		char userAnswer;
		bool confirmation = false;
		while (confirmation == false)
		{
			cout << "Are you sure you want to remove this employee? (y/n): ";
			cin >> userAnswer;
			if (userAnswer == 'N' || userAnswer == 'n')
				return;
			else if (userAnswer == 'Y' || userAnswer == 'y')
				confirmation = true;
		}

		fileCode = fopen_s(&file, pathEmployee, "wb");
		tempCode = fopen_s(&temp, pathTemp, "rb");
		if (fileCode == 0 && tempCode == 0)
		{
			Employee point;
			while (!feof(temp))
			{
				if (fread(&point, sizeof(Employee), 1, temp))
					fwrite(&point, sizeof(Employee), 1, file);
			}
			fclose(file);
			fclose(temp);
			cout << "The employee was removed from the book" << endl;
		}
	}
	else
		cout << "The employee was not found in the book" << endl;
	allocation();
}


void PrintAllEmployee(const char pathEmployee[])
{
	allocation();
	FILE* file;
	errno_t code = fopen_s(&file, pathEmployee, "rb");
	if (code == 0)
	{
		Employee point;
		int counter = 1;
		while (!feof(file))
		{
			if (fread(&point, sizeof(Employee), 1, file))
			{
				printf("\tEmployee #%d\n", counter++);
				PrintInfoStruct(point);
				cout << endl;
			}
		}
		fclose(file);
		if (counter == 1)
		{
			cout << "No employees in the list" << endl;
		}
	}
	else
		cout << "Error. Code: " << code << endl;
	allocation();
}
void PrintInfoEmployee(const char pathEmployee[])
{
	allocation();
	FILE* file;
	errno_t code = fopen_s(&file, pathEmployee, "rb");
	if (code == 0)
	{
		bool isFind = false;
		char lastName[SIZE_STR];
		cout << "Enter last name employee: ";
		cin >> lastName;
		cout << endl;
		Lowercase(lastName);

		Employee point;
		while (!feof(file))
		{
			if (fread(&point, sizeof(Employee), 1, file))
			{
				Employee pointTemp = point;
				Lowercase(pointTemp.lastName);
				if (strcmp(lastName, pointTemp.lastName) == 0)
				{
					PrintInfoStruct(point);
					cout << endl;
					isFind = true;
				}
			}
		}
		if (!isFind)
			cout << "No employee with that last name was found" << endl;
		fclose(file);
	}
	else
		cout << "Error. Code: " << code << endl;
	allocation();
}
void SearchSalaryRange(const char pathEmployee[])
{
	allocation();
	FILE* file;
	errno_t code = fopen_s(&file, pathEmployee, "rb");
	if (code == 0)
	{
		bool isFind = false;
		int MinRange;
		int MaxRange;
		cout << "Enter the minimum salary range: ";
		cin >> MinRange;
		cout << "Enter the maximum salary range: ";
		cin >> MaxRange;
		cout << endl;

		Employee point;
		int counter = 1;
		while (!feof(file))
		{
			if (fread(&point, sizeof(Employee), 1, file))
			{
				if (point.salary >= MinRange && point.salary <= MaxRange)
				{
					printf("\tEmployee #%d\n", counter++);
					PrintInfoStruct(point);
					cout << endl;
					isFind = true;
				}
			}
		}
		if (!isFind)
			cout << "No employee with that range of salary was found" << endl;
		fclose(file);
	}
	else
		cout << "Error. Code: " << code << endl;
	allocation();
}

void allocation()
{
	for (int i = 0; i <= 20; i++)
	{
		cout << "-";
	}
	cout << endl;
}