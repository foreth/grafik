#include "scheduler.h"


Employee::Employee(int id, string first_name, string last_name, positions position, times time)
{
	this->id = id;
	this->first_name = first_name;
	this->last_name = last_name;
	this->position = position;
	this->time = time;
}

short Employee::getID()
{
	return id;
}

void Employee::printToConsole()
{
	cout << setw(18) << "Numer pracownika: " << id << endl;
	cout << setw(18) << "Imie: " << first_name << endl;
	cout << setw(18) << "Nazwisko: " << last_name << endl;

	cout << setw(18) << "Etat: ";

	switch (time)
	{
	case 0: cout << "1/4" << endl; break;
	case 1: cout << "1/2" << endl; break;
	case 2: cout << "3/4" << endl; break;
	case 3: cout << "pelny" << endl; break;
	default: cout << "niepoprawna pozycja" << endl;
	}
	cout << setw(18) << "Pozycja: ";

	switch (position)
	{
	case 0: cout << "sprzedawca/kasjer" << endl; break;
	case 1: cout << "asystent" << endl; break;
	case 2: cout << "zastepca kierownika" << endl; break;
	case 3: cout << "kierownik" << endl; break;
	default: cout << "niepoprawna pozycja" << endl;
	}
}

void Shop::addEmployee(Employee& employee)
{
	employee_list.push_back(employee);
}

void Shop::addEmployee(int id, string first_name, string last_name, positions position, times time)
{
	employee_list.push_back(Employee(id, first_name, last_name, position, time));
}

void Shop::deleteEmployee(Employee& employee)
{
	for (int i = 0; i < employee_list.size(); i++)
	{
		if (employee_list[i].getID() == employee.getID())
		{
			employee_list.erase(employee_list.begin() + i);
		}
	}
}

void Shop::deleteEmployee(short id)
{
	for (int i = 0; i < employee_list.size(); i++)
	{
		if (employee_list[i].getID() == id)
		{
			employee_list.erase(employee_list.begin() + i);
		}
	}
}

void Shop::listEmployees()
{
	for (Employee emp : employee_list)
	{
		emp.printToConsole();
	}
}

void Shop::makeSchedule(short month, short year)
{
	//okresl miesiac
	Month chosen_month(month, year); // konstuktor Month tworzy wektor dni w tym miesiacu

	chosen_month.printToConsole();

	// algorytm przyznawania godzin pracownikom...
	//..
	//..
}

Month::Month(short month, short year)
{
	this->days_in_month = 30;		// pobrac pozniej ile ten miesiac ma dni
	days first_day = THURSDAY;		// pobrac jaki jest pierwszy dzien
	
	short help_day = short(first_day);

	for (short day = 0; day < days_in_month; day++)
	{
		day_list.push_back(Day(days(help_day)));

		help_day++;
		help_day %= 7;
	}
}

void Month::printToConsole()
{

	for (Day this_day : day_list)
	{
		cout << this_day.toString();

		vector<WorkHour> temp = this_day.getTime();

		cout << "( ";

		for (WorkHour h : temp)
		{
			cout << h.getHour() << ", ";
		}

		cout << " )" << endl;

		/*if (this_day.getDay() == SUNDAY)
			cout << "\n";
		else
			cout << " ";*/

	}

	cout << endl;
}

Day::Day(days this_day)
{
	this->this_day = this_day;

	short open_hour = 7;
	short close_hour = 22;

	//utworzenie godzin
	for (int i = open_hour; i <= close_hour-1; i++)
	{
		time.push_back(WorkHour(i, 0));
	}
}

days Day::getDay()
{
	return this_day;
}

vector<WorkHour> Day::getTime()
{
	return time;
}

string Day::toString()
{
	switch (this_day)
	{
	case MONDAY: return "pn"; break;
	case TUESDAY: return "wt"; break;
	case WEDNESDAY: return "sr"; break;
	case THURSDAY: return "cz"; break;
	case FRIDAY: return "pt"; break;
	case SATURDAY: return "so"; break;
	case SUNDAY: return "nd"; break;
	}
}

Time::Time(short hour, short minute)
{
	this->hour = hour;
	this->minute = minute;
}


