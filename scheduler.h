#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

enum positions { REGULAR, ASSISTANT, CO_MANAGER, MANAGER };
enum times {QUATER, HALF, THREE, FULL};
enum days {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};

class Employee
{
	short id;
	string first_name;
	string last_name;
	positions position;
	times time;
	

public:

	Employee(int id, string first_name, string last_name, positions position, times time);
	short getID();
	void printToConsole();
};

class Shop
{
	vector<Employee> employee_list;
	short efficiency;						// it's a ghost variable now :) just an idea

public:
	void addEmployee(Employee& employee);
	void addEmployee(int id, string first_name, string last_name, positions position, times time);
	void deleteEmployee(Employee& employee);
	void deleteEmployee(short id);
	void listEmployees();
	void makeSchedule(short month, short year);
};

class Time
{
	short hour;
	short minute;

public:
	Time(short hour, short minute);
	short getHour(){ return hour; }
};

class WorkHour : public Time
{
	vector<Employee> employee_list;
public:
	WorkHour(short hour, short minute) : Time(hour, minute){ }
	WorkHour(short hour, short minute, Employee& employee) : Time(hour, minute){ employee_list.push_back(employee); }

	void addEmployee(Employee& employee){ employee_list.push_back(employee); }

};

class Day
{
	//vector<hour> hour_list;
	days this_day;
	vector<WorkHour> time;

public:
	Day(days this_day);
	days getDay();
	vector<WorkHour> getTime();
	string toString();
};

class Month
{
	vector<Day> day_list;
	short days_in_month;

public:
	Month(short month, short year);
	void printToConsole();
};

