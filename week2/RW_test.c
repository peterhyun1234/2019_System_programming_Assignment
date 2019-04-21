#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LEN 100
#define TFN "stdentRecord.txt"

typedet struct student
{
	char name[MAX_LEN+1];
	int stu_num;
	int score;
}Student;

void writeOp();
void readOp();

int main()
{

	writeOP();
	readOP();

	return 0;
}

void writeOP()
{
int fd = 0;
Student student[3] = {
	{"존",1004, 100},
	{"박",1005,75},
	{"남",1006,50}
};

fd = open(TPN, O_WRONLY|O_CREAT|O_TRUNC,0777);

if(fd == -1)
{
perror("Fail open\n");
exit(1);
}

int wd =0 ;
wd = write(fd, student, sizeof(student));
if(wd == -1)
{
	perror("Fail write\n");
	exit(1);
}

printf("Success to write!!\n");

close(fd);

}


void readOP()
{

	int fd = 0;
	Student stu;
	fd = open(TPN, O_WRONLY);

	if(fd == -1)
	{
	perror("Fail open\n");
	exit(1);
	}

	int rd =0 ;
	while((rd =  read(fd, &stu, sizeof(Student)))>0)
	{
		printf("student name  :%s\n", stu.name);
		printf("student num   :%d\n", stu.stu_num);
		printf("student score :%d\n", stu.score);
	}


	close(fd);

}
