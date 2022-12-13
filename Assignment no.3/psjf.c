#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct process_info
{
	char pname[20];
    	int at,bt,ct,bt1;
    	struct process_info*next;
}NODE;

int n;
NODE *first,*last;

void accept_info()
{
	NODE *p;
  	int i;
  	printf("Enter number of process:");
 	scanf("%d",&n);
  
	for(i=0;i<n;i++)
  	{
        	p=(NODE*)malloc(sizeof(NODE));
        
        	printf("\nEnter process name:");
        	scanf("%s",p->pname);
        	printf("\nEnter arrival time:");
        	scanf("%d",&p->at);
        	printf("Enter CPU burst time:");
        	scanf("%d",&p->bt);
        
        	p->bt1=p->bt;
        	p->next=NULL;
        	if(first==NULL)
         		first=p;
        	else
           		last->next=p;
        	last=p;
   	}
}

void print_output()
{
	NODE *p;
     	float avg_tat=0,avg_wt=0;
     	printf("\nPname \t at \t bt \t ct \t tat \t wt \n");
     
     	p=first;
     	while(p!=NULL)
     	{
		int tat=p->ct-p->at;
          	int wt=tat-p->bt;
          	avg_tat+=tat;
          	avg_wt+=wt;
          
          
          	printf("%s \t %d \t %d \t %d \t %d \t %d \n",p->pname,p->at,p->bt,p->ct,tat,wt);
      		p=p->next;
     	}
     	printf("\nAverage TAT =%f\t Average WT=%f\n",avg_tat/n,avg_wt/n);    
}

void print_input()
{
	NODE *p;
    	p=first;
    	printf("\npname \t at \t bt \n");
    	while(p!=NULL)
    	{
    		printf("%s \t %d \t %d \n",p->pname,p->at,p->bt1);
        	p=p->next;    
     	}
}

void sort()
{
    	NODE *p,*q;
    	int t;
    	char name[20];
    	p=first;
    	while(p->next!=NULL)
    	{
     		q=p->next;
        	while(q!=NULL)
        	{
           		if (p->at > q->at)
           		{
             			strcpy(name,p->pname);
             			strcpy(p->pname,q->pname);
             			strcpy(q->pname,name);
           
             			t=p->at;
             			p->at=q->at;
             			q->at=t;
           
             			t=p->bt;
             			p->bt=q->bt;
             			q->bt=t;
           
             			t=p->ct;
             			p->ct=q->ct;
             			q->ct=t;
           
             			t=p->bt1;
             			p->bt1=q->bt1;
             			q->bt1=t;
           
          		}
          		q=q->next;
    		}
    		p=p->next;
  	}
}

int time;
NODE *get_sjf()
{
	NODE *p,*min_p=NULL;
   	int min=9999;
   	p=first;
   	while(p!=NULL)
   	{
         	if(p->at<=time && p->bt1!=0 && p->bt1<min)
         	{
             		min=p->bt1;
             		min_p=p;
         	}
         	p=p->next;
   	}
   	return min_p;
}

struct gantt_chart
{
	int start;
	char pname[30];
	int end;
}s[100],s1[100];

int k;

void sjfp()
{
	int prev=0,n1=0;
    	NODE *p;
    	while(n1!=n)
    	{
       		p=get_sjf();
       		if (p==NULL)
       		{
           		time++;
           		s[k].start=prev;
           		strcpy(s[k].pname,"*");
           		s[k].end=time;
           		prev=time;
           		k++;
        	}
        	else
        	{
           		time++;
           		s[k].start=prev;
           		strcpy(s[k].pname,p->pname);
           		s[k].end=time;
           
           		prev=time;
           		k++;
           		p->ct=time;
           		p->bt1--;
           		if (p->bt1==0)
               			n1++;
        	}
        	print_input();
        	sort();
     }
}

void print_gantt_chart()
{
      int i,j,m;
      s1[0]=s[0];
      
      for(i=1,j=0;i<k;i++)
      {
          if (strcmp(s[i].pname,s1[j].pname)==0)
              s1[j].end=s[i].end;
          else
              s1[++j]=s[i];
      }
      printf("%d",s1[0].start);
      for(i=0;i<=j;i++)
      {
         m=(s1[i].end-s1[i].start);
         for (k=0;k<m/2;k++)
              printf("-");
        printf("%s",s1[i].pname);
        for(k=0;k<(m+1)/2;k++)
            printf("-");
        printf("%d",s1[i].end);
      }
}

int main()
{
	accept_info();
   	sort();
   	sjfp();
   	print_output();
   	print_gantt_chart();
   
   	return 0;
}
/*OUTPUT
ty60@pc21:~/Desktop/Ty60/OS/Assignment no.3$ cc psjf.c
ty60@pc21:~/Desktop/Ty60/OS/Assignment no.3$ ./a.out
Enter number of process:5

Enter process name:p1

Enter arrival time:1
Enter CPU burst time:8

Enter process name:p2

Enter arrival time:2
Enter CPU burst time:2

Enter process name:p3

Enter arrival time:0
Enter CPU burst time:1

Enter process name:p4

Enter arrival time:2
Enter CPU burst time:10

Enter process name:p5

Enter arrival time:4
Enter CPU burst time:3

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 8 
p2 	 2 	 2 
p4 	 2 	 10 
p5 	 4 	 3 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 7 
p2 	 2 	 2 
p4 	 2 	 10 
p5 	 4 	 3 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 7 
p2 	 2 	 1 
p4 	 2 	 10 
p5 	 4 	 3 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 7 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 3 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 7 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 2 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 7 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 1 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 7 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 6 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 5 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 4 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 3 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 2 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 1 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 10 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 9 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 8 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 7 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 6 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 5 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 4 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 3 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 2 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 1 
p5 	 4 	 0 

pname 	 at 	 bt 
p3 	 0 	 0 
p1 	 1 	 0 
p2 	 2 	 0 
p4 	 2 	 0 
p5 	 4 	 0 

Pname 	 at 	 bt 	 ct 	 tat 	 wt 
p3 	 0 	 1 	 1 	 1 	 0 
p1 	 1 	 8 	 14 	 13 	 5 
p2 	 2 	 2 	 4 	 2 	 0 
p4 	 2 	 10 	 24 	 22 	 12 
p5 	 4 	 3 	 7 	 3 	 0 

Average TAT =8.200000	 Average WT=3.400000
0p3-1p1-2-p2-4-p5--7---p1----14-----p4-----24
*/
