#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd = 0;
	if(argc!= 3)
	{
		fprintf(stderr,"Usage: %s <file name> <acess mode>\n",argv[0]);
		fprintf(stderr, "acess mode is octet number, ex:0755\n");
		return 1;
	}

	mode_t mode =0;
	sscanf(argv[2], "0%o",mode);
	fd= open(argv[1],O_WRONLY|O_CREAT|O_EXCL,mode);
	if(fd == -1)
	{
		perror("failed open ");
		return 1;
	}
	printf("success open %s\n",argv[1]);
	close(fd);

	return 0;

}
