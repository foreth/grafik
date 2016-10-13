#include "scheduler.h"


int main()
{
	Shop rossmann;

	rossmann.addEmployee(1, "Magdalena", "Pastuszak", ASSISTANT, FULL);
	rossmann.addEmployee(2, "Katarzyna", "Maj", REGULAR, FULL);
	rossmann.addEmployee(3, "Joanna", "Budzik", MANAGER, FULL);
	rossmann.addEmployee(4, "Anna", "Poranna", REGULAR, FULL);
	rossmann.addEmployee(5, "Marzena", "Zzalasu", REGULAR, FULL);
	rossmann.addEmployee(6, "Maja", "Kwiatkowska", ASSISTANT, FULL);
	
	rossmann.listEmployees();

	rossmann.makeSchedule(9, 2016);

	rossmann.listEmployees();

}