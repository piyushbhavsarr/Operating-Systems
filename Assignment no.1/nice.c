#include<stdio.h>
#include<unistd.h>
int main()
{
	int pid,retnice;
	printf("Press DEL to stop process\n");
	pid=fork();
	for(;;)
	{
		if (pid==0)
		{
			retnice=nice(-5);
			printf("Child gets higher CPU priority %d \n",retnice);
			sleep(1);
		}
		else
		{
			retnice=nice(4);
			printf("Parent gets lower CPU priority %d \n",retnice);
			sleep(1);
		}
	}
}

/*OUTPUT
ty60@pc21:~/Desktop/OS$ cc nice.c
ty60@pc21:~/Desktop/OS$ ./a.out
Press DEL to stop process
Parent gets lower CPU priority 4 
Child gets higher CPU priority -1 
Parent gets lower CPU priority 8 
Child gets higher CPU priority -1 
Child gets higher CPU priority -1 
Parent gets lower CPU priority 12 
Child gets higher CPU priority -1 
Parent gets lower CPU priority 16 
Child gets higher CPU priority -1 
Parent gets lower CPU priority 19 
Child gets higher CPU priority -1 
Parent gets lower CPU priority 19 
Parent gets lower CPU priority 19 
Child gets higher CPU priority -1 
Child gets higher CPU priority -1 
Parent gets lower CPU priority 19 

*/
