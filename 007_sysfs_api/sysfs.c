#define	 _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char **argv)
{
	int num, index;
	int num_fs;
	const char *fsname = "ext4";
	char buf[40];
	unsigned int fs_index = 0;

	num_fs = syscall(SYS_sysfs, 3);
	printf("The total  number of file system in the kernel is %d.\n", num);

	index  = syscall(SYS_sysfs, 1, fsname);
	printf("The ext4 file system type index is %d\n", index);

	for (; fs_index < num_fs + 1; fs_index++){
		num = syscall(SYS_sysfs, 2, fs_index, buf);
		if (num == -1 )
			perror("syscall");
		else
			printf("The file system which index is %d  identifier string is : %s\n",fs_index,  buf);
	}

	return 0;
}
