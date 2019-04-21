#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int dev;
	int num;
	char buff[1024];

	dev = open("/dev/sysprog_device",O_RDWR);
	if(dev == -1)
	{
		perror("Failed open because ");
		return 1;
	}

	for(int i=0; i<3; i++)
	{
		printf("Input the number\n");
		scanf("%s", buff);
		
		write(dev, buff, strlen(buff));
		read(dev, buff, strlen(buff));
		
		printf("The accumulated number in kernel space is %s\n\n", buff);
	}
	
	
	
	close(dev);

	exit(EXIT_SUCCESS);
}

