#pragma once

const int SIZE_STR = 20;
const int SIZE_PHONE_NUM = 10;
const char pathEmployee[] = "DataEmployees.txt";
const char pathTemp[] = "Temp.txt";

struct Employee
{
	char firstName[SIZE_STR];
	char lastName[SIZE_STR];
	char phoneNumber[SIZE_PHONE_NUM];
	double salary;
};

enum actionsCodeMain
{
	CodeAddEmployee = 1, CodeDelEmployee, CodeMenuReport, CodeExitProgram
};
enum actionsCodeReport
{
	CodePrintAllEmployee = 1, CodePrintInfoEmployee, CodeSearchSalaryRange, CodeExitReport
};

void PrintInfoStruct(Employee point);
char* Lowercase(char* str);

void AddEmployee(const char pathEmployee[]);
void DelEmployee(const char pathEmployee[], const char pathTemp[]);

void PrintAllEmployee(const char pathEmployee[]);
void PrintInfoEmployee(const char pathEmployee[]);
void SearchSalaryRange(const char pathEmployee[]);

void PrintMenuMain();
void PrintMenuReport();

void allocation();