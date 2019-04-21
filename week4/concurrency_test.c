#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_MAGIC_NUMBER 'j'
#define IOCTL_CMD_SUM           _IOWR( IOCTL_MAGIC_NUMBER, 0, int)
#define IOCTL_CMD_READ           _IOWR( IOCTL_MAGIC_NUMBER, 1, int)
#define IOCTL_CMD_WRITE           _IOWR( IOCTL_MAGIC_NUMBER, 2, int)

int main(void)
{
	int fd;
	int breakloop = 0;
	char input[8];
	int num;

	fd = open("/dev/ioctl_dev",O_RDWR);
	if(fd == -1)
	{
		perror("Failed open because ");
		return 1;
	}

	while(!breakloop)
	{
		printf("Please enter the operation(w/r/q) : ");		
		scanf("%s", input);
		
		switch(input[0])
		{
		
			case 'q' :
				breakloop = 1;
				break;
			
			case 'w' : 
				printf("Enter the data to write : ");
				scanf("%d", &num);
				ioctl(fd,IOCTL_CMD_WRITE, &num);
				break;

			case 'r' :
				ioctl(fd, IOCTL_CMD_READ, &num);
				printf("The data in device is %d\n", num);
				break;

		}
	}
	close(fd);
	return 0;
}
