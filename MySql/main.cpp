#include"mysql.h"

int main()
{
	DataBase* d1 = new DataBase;
	d1->Connect("localhost", "root", "hb75127512", "test", 0);
	d1->Query("t_student");


	return 0;
}