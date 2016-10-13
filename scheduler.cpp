#include "scheduler.h"
#include <cstdlib>
#include <ctime>

Employee::Employee(int id, string first_name, string last_name, positions position, times time)
{
	this->id = id;
	this->first_name = first_name;
	this->last_name = last_name;
	this->position = position;
	this->time = time;
	this->working_hours = 0;

	switch (time)
	{
	case FULL: time_multiplier = 1; break;
	case THREE: time_multiplier = 3.0 / 4; break;
	case HALF: time_multiplier = 1.0 / 2; break;
	case QUATER: time_multiplier = 1.0 / 4; break;
	}
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

	cout << "Free days: ";

	for (short free_day : free_days)
		cout << free_day << " ";

	cout << endl;
}

//####################################################################################################

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

	for (Employee emp : employee_list)
		emp.setWorkingHours(chosen_month.getWorkingHours() * emp.getTimeMultiplier());

	assignFreeDays(chosen_month.getDaysInMonth()); // losuje dni z wolnej puli - rownomierna dystrybucja


	// algorytm przyznawania godzin pracownikom...
	
	// POSORTOWAC TUTAJ PRACOWNIKOW WEDLUG TEGO, CZY MAJ¥ PREFERENCJE/¯YCZENIA oraz ewentualnie wed³ug priorytetu tych ¿yczeñ


	for (Employee emp : employee_list)
	{


		for (Day d : chosen_month.getDayList())
		{
			//dla danego dnia...

			//if (d.getDay() == firstFreeDay || d.getDay() == secondFreeDay)	// gdy aktualny dzien jest wolny to przeskocz do kolejnego dnia
			//	continue;

			for (WorkHour wh : d.getTime())
			{
				//dla danej godziny...


			}
		}

		//while (emp.setWorkingHours > 0)
		//{
		//	
		//}
	}


}

void Shop::assignFreeDays(short days_in_month) // Employee and Shop and Month friend
{
	vector<short> week_standard_backup = { 1, 2, 3, 4, 5, 6, 7 };
	vector<short> week_last_backup;

	vector<short> week_this = week_standard_backup;

	short last_days = days_in_month - 4 * 7;

	for (int i = 0; i < last_days; i++)
		week_last_backup.push_back(i + 1);


	for (int i = 0; i < 4; i++)			// dla pierwszych 4 tygodni
	{
		for (Employee& emp : employee_list)
		{		
				short random_index = rand() % week_this.size() + 1;  // 1-7
				short free_day = week_this[random_index - 1];
				emp.free_days.push_back(i * 7 + free_day);		//  1-7 8-14 15-21 22-28
				week_this.erase(week_this.begin() + random_index - 1);

				if (week_this.empty())							// trick majacy na celu rownomierna dystrybuje wolnych dni
					week_this = week_standard_backup;

				random_index = rand() % week_this.size() + 1;  // 1-7									// to samo...
				free_day = week_this[random_index - 1];
				emp.free_days.push_back(i * 7 + free_day);		//  1-7 8-14 15-21 22-28
				week_this.erase(week_this.begin() + random_index - 1);

				if (week_this.empty())
					week_this = week_standard_backup;
		}

		week_this = week_standard_backup;
	}

	//dla ostatniego tygodnia

	week_this = week_last_backup;

	for (Employee& emp : employee_list)
	{

		short random_index = rand() % week_this.size() + 1;  // 1-7
		short free_day = week_this[random_index - 1];
		emp.free_days.push_back(4 * 7 + free_day);		//  1-7 8-14 15-21 22-28
		week_this.erase(week_this.begin() + random_index - 1);

		if (week_this.empty())
			week_this = week_standard_backup;
	}
}



//####################################################################################################

Month::Month(short month, short year)
{
	this->days_in_month = 31;		// pobrac pozniej ile ten miesiac ma dni
	days first_day = SATURDAY;		// pobrac jaki jest pierwszy dzien
	
	short help_day = short(first_day);

	for (short day = 0; day < days_in_month; day++)
	{
		day_list.push_back(Day(days(help_day)));
		day_list[day].setDate( day + 1 );

		help_day++;
		help_day %= 7;
	}

	short tWeekendDays = 0;

	for (Day d : day_list)
	{
		if (d.getDay() == SATURDAY || d.getDay() == SUNDAY)
		{
			tWeekendDays++;
		}
	}

	this->weekend_days = tWeekendDays;
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

short Month::getWorkingHours()
{
	short working_days = 0;
	
	for (Day this_day : day_list)
	{
		if (!(this_day.getDay() == SATURDAY || this_day.getDay() == SUNDAY))
			working_days++;
	}
	
	return working_days*8;
}

//####################################################################################################

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

//####################################################################################################

Time::Time(short hour, short minute)
{
	this->hour = hour;
	this->minute = minute;
}

//####################################################################################################

