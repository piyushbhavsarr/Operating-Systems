#include<stdio.h>
struct times
{
	int p,art,but,wtt,tat,rnt;
};

void sortart(struct times a[],int pro)
{
	int i,j;
	struct times temp;
	for (i=0;i<pro;i++)
	{
		for (j=i+1;j<pro;j++)
		{
			if (a[i].art > a[j].art)
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
		
	}
	return;
}

int main()
{
	int i,j,pro,time,remain,flag=0,ts;
	struct times a[100];
	float avgwt=0,avgtt=0;
	printf("Round robin scheduling algorithm\n");
	printf("Enter number of processes : ");
	scanf("%d",&pro);
	remain=pro;
	for (i=0;i<pro;i++)
	{
		printf("Enter arrival time for process %d :",i+1);
		scanf("%d",&a[i].art);
		printf("Enter burst time for process %d :",i+1);
		scanf("%d",&a[i].but);
		a[i].p=i;
		a[i].rnt=a[i].but;
	}
	sortart(a,pro);
	printf("Enter time quantum : ");
	scanf("%d",&ts);
	printf("\n*********************************************\n");
	printf("Gantt Chart \n");
	printf("0");
	
	for (time=0,i=0;remain!=0;)
	{
		if (a[i].rnt<=ts && a[i].rnt>0)
		{
			time=time+a[i].rnt;
			printf("->[p%d]<-%d",a[i].p,time);
			a[i].rnt=0;
			flag=1;
		}
		else if (a[i].rnt>0)
		{
			a[i].rnt=a[i].rnt-ts;
			time=time+ts;
			printf("->[p%d]<-%d",a[i].p,time);
		}
		if (a[i].rnt==0 && flag==1)
		{
			remain--;
			a[i].tat=time-a[i].art;
			a[i].wtt=time-a[i].art-a[i].but;
			avgwt=avgwt+time-a[i].art-a[i].but;
			avgtt=avgtt+time-a[i].art;
			flag=0;
		}
		if (i==pro-1)
			i=0;
		else if (a[i+1].art<=time)
			i++;
		else
			i=0;			
	}
	printf("\n\n");
	printf("\n**************************************\n");
	printf("PID \t AT \t BT \t TAT \t WT \n");
	printf("\n*************************************\n");
	for (i=0;i<pro;i++)
	{
		printf("P%d \t %d \t %d \t %d \t %d \n",a[i].p,a[i].art,a[i].but,a[i].tat,a[i].wtt);
	}
	printf("\n*************************************\n");
	avgwt=avgwt/pro;
	avgtt=avgtt/pro;
	printf("\n Average waiting time : %2f \n",avgwt);
	printf("\n Average turnaround time : %2f ",avgtt);	
}
/*OUTPUT
ty60@pc24:~/Desktop/Ty60/OS/Assignment no.3/Set C$ cc roundrobin.c
ty60@pc24:~/Desktop/Ty60/OS/Assignment no.3/Set C$ ./a.out
Round robin scheduling algorithm
Enter number of processes : 3
Enter arrival time for process 1 :1
Enter burst time for process 1 :3
Enter arrival time for process 2 :2
Enter burst time for process 2 :2
Enter arrival time for process 3 :0
Enter burst time for process 3 :5
Enter time quantum : 2

*********************************************
Gantt Chart 
0->[p2]<-2->[p0]<-4->[p1]<-6->[p2]<-8->[p0]<-9->[p2]<-10


**************************************
PID 	 AT 	 BT 	 TAT 	 WT 

*************************************
P2 	 0 	 5 	 10 	 5 
P0 	 1 	 3 	 8 	 5 
P1 	 2 	 2 	 4 	 2 

*************************************

 Average waiting time : 4.000000 

 Average turnaround time : 7.333333
*/
