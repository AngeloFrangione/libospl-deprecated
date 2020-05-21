#include <stdio.h>
#include "include/stockage.h"

int main(int argc, char const *argv[])
{
	char value[10] = {0};


	create_database("test.db");
	delete_setting("test.db", "name");
	insert_setting("test.db", "version", "0.1.0");
	select_setting("test.db", "version", value);
	printf("%s\n", value);
	update_setting("test.db", "version", "0.52");
	select_setting("test.db", "version", value);
	printf("%s\n", value);
	return 0;
}