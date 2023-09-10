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
	codeAddEmployee = 1, codeDelEmployee, codeMenuReport, codeExitProgram
};
enum actionsCodeReport
{
	codePrintAllEmployee = 1, codePrintInfoEmployee, codeSearchSalaryRange, codeExitReport
};

void printInfoStruct(Employee point);
char* lowercase(char* str);

void addEmployee(const char pathEmployee[]);
void delEmployee(const char pathEmployee[], const char pathTemp[]);

void printAllEmployee(const char pathEmployee[]);
void printInfoEmployee(const char pathEmployee[]);
void searchSalaryRange(const char pathEmployee[]);

void printMenuMain();
void printMenuReport();