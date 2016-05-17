#include "A-star.h"



int main ()
{
	map test;
	test.read_From_File("abv.txt");
	test.printMap();
	bool tester = A_Star("abv.txt",0,1,0,11);
	system("PAUSE");
	return 0;
}


