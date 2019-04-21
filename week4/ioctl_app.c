#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC_NUMBER 'j';
#define IOCTL_CMD_SUM           _IOWR( IOCTL_MAGIC_NUMBER, 0, int)
#define IOCTL_CMD_READ           _IOWR( IOCTL_MAGIC_NUMBER, 1, int)
#define IOCTL_CMD_WRITE           _IOWR( IOCTL_MAGIC_NUMBER, 2, int)

int main(int argc, char *argv[])
{
	int fd;
	int num;

	fd = open("/dev/ioctl_dev",O_RDWR);
	if(fd == -1)
	{
		perror("Failed open because ");
		return 1;
	}

	for(int i=0; i<3; i++)
	{
		printf("Input the number\n");
		scanf("%d", num);
		ioctl(fd, IOCTL_CMD_SUM, &num);	
		printf("The accumulated number in kernel space is %d\n\n", num);
	}
	
	
	
	close(fd);

	exit(EXIT_SUCCESS);
}

