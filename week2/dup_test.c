#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd, fd2;
    char buf[80];

    fd = open("./week2_dup_data", O_CREAT | O_WRONLY, 0755);

	 write(fd, "Hello\n",strlen("Hello\n"));

	 fd2 = dup(fd);
  
	 write(fd2, "Hi\n",strlen("Hi\n"));

    close(fd);

	 write(fd2, "니하오~\n", strlen("니하오~\n"));

	 close(fd2);

	 return 0;
}
