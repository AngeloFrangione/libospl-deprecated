#include <stdio.h>
#include <string.h>
#include "include/md5.h"

int main(int argc, char const *argv[])
{
	char hash[33];
	memset(hash, 0, 33);
	md5(argv[1], hash);
	printf("%s\n", hash);
	return 0;
}