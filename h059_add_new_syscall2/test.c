#include <syscall.h>
#include <stdio.h>
int main(void)
{
	printf("%d\n",syscall(400));
	return 0;
}
