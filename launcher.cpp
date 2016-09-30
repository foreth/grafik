#include "scheduler.h"


int main()
{
	Shop rossmann;

	rossmann.addEmployee(1, "Magdalena", "Pastuszak", ASSISTANT, THREE);
	rossmann.addEmployee(2, "Katarzyna", "Maj", REGULAR, HALF);
	rossmann.addEmployee(3, "Joanna", "Budzik", MANAGER, FULL);
	
	rossmann.listEmployees();

	rossmann.makeSchedule(9, 2016);


}