#include <stdio.h>
#include "include/stockage.h"

int main(int argc, char const *argv[])
{
	int value;


	create_database("test.db");
	select_setting("version", &value);
	printf("%d\n", value);
	return 0;
}