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
NODE*first,*last;
void accept_info()
{
   NODE*p;
   int i;
   printf("Enter no of processess:");
   scanf("%d",&n);
   for(i=0;i<n;i++)
   {
      p=(NODE*)malloc(sizeof(NODE));
      printf("Enter process name:");
      scanf("%s",p->pname);
      printf("Enter arrival time:");
      scanf("%d",&p->at);
      printf("Enter first CPU burst time:");
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
   printf("pname\t at\t bt\t ct\t tat\t wt\t\n");
   p=first;
   while(p!=NULL)
   {
       int tat=p->ct-p->at;
       int wt=tat-p->bt;
       avg_tat +=tat;
       avg_wt +=wt;
       printf("%s\t %d\t %d\t %d\t %d\t %d\n",p->pname,p->at,p->bt,p->ct,tat,wt);
       p=p->next;
   }
   printf("Avg TAT=%f\t AVG WT=%f\n",avg_tat/n,avg_wt/n);
}
void print_input()
{
   NODE*p;
   p=first;
   printf("pname\t at\t bt\n");
   while(p!=NULL)
   {
      printf("%s\t %d\t %d\n",p->pname,p->at,p->bt1);
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
         if(p->at>q->at)
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
NODE*get_fcfs()
{
   NODE*p;
   p=first;
   while(p!=NULL)
   {
      if(p->at<=time && p->bt1!=0)
         return p;
      p=p->next;
   }
   return NULL;
}
struct gantt_chart
{
   int start;
   char pname[30];
   int end;
}s[100],s1[100];
int k;
void fcfs()
{
   int prev=0,n1=0;
   NODE*p;
   while(n1!=n)
   {
      p=get_fcfs();
      if(p==NULL)
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
         time+=p->bt1;
         s[k].start=prev;
         strcpy(s[k].pname,p->pname);
         s[k].end=time;
         prev=time;
         k++;
         p->ct=time;
         p->bt1=0;
         n1++;
      }
      
      sort();
   }
}
void print_gantt_chart()
{
   int i,j,m;
   s1[0]=s[0];
   for(i=1,j=0;i<k;i++)
   {
      if(strcmp(s[i].pname,s1[j].pname)==0)
         s1[j].end=s[i].end;
      else
         s1[++j]=s[i];
   }
   printf("%d",s1[0].start);
   for(i=0;i<=j;i++)
   {
      m=(s1[i].end-s1[i].start);
      for(k=0;k<m/2;k++)
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
   fcfs();
   print_output();
   print_gantt_chart();
   return 0;
}
/*OUTPUT
ty60@pc21:~/Desktop/Ty60/OS/Assignment no.3$ cc fcfs.c
ty60@pc21:~/Desktop/Ty60/OS/Assignment no.3$ ./a.out
Enter no of processess:5
Enter process name:p1
Enter arrival time:1
Enter first CPU burst time:5
Enter process name:p2
Enter arrival time:0
Enter first CPU burst time:3
Enter process name:p3
Enter arrival time:2
Enter first CPU burst time:2
Enter process name:p4
Enter arrival time:3
Enter first CPU burst time:4
Enter process name:p5
Enter arrival time:18
Enter first CPU burst time:2
pname	 at	 bt	 ct	 tat	 wt	
p2	 0	 3	 3	 3	 0
p1	 1	 5	 8	 7	 2
p3	 2	 2	 10	 8	 6
p4	 3	 4	 14	 11	 7
p5	 18	 2	 20	 2	 0
Avg TAT=6.200000	 AVG WT=3.000000
0-p2--3--p1---8-p3-10--p4--14--*--18-p5-20
*/
