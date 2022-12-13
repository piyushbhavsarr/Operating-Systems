#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int pid=fork();
	if(pid>0)
	{
		printf("\n\nParent Process.\n");
		printf("ID : %d \n\n",getpid());
	}
	else if(pid==0)
	{
		printf("Child Process\n");
		printf("ID : %d \n",getpid());
		printf("Parent-ID :%d \n", getppid());
		sleep(10);
		printf("Child Process\n");
		printf("ID : %d \n",getpid());
		printf("\nParent-ID :%d \n\n", getppid());
	}
	else
		printf("\nFailed to create Child Process!");
	return 0;
}

/*OUTPUT
ty60@pc21:~/Desktop/OS$ cc orphan.c
ty60@pc21:~/Desktop/OS$ ./a.out


Parent Process.
ID : 9948 

Child Process
ID : 9949 
Parent-ID :9948 
ty60@pc21:~/Desktop/OS$ Child Process
ID : 9949 

Parent-ID :1164 

*/
