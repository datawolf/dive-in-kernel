#include <stdio.h>
#include <string.h>

int main()
{
	const char *name = "ext2.fs";
	const char *dot = strchr(name, '.');
	int len = dot ? dot - name : strlen(name);

	return 0;

}
