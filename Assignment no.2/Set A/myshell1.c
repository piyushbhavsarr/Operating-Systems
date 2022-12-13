#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fp;
char cmd[50],inst[50];

void count()
{
	char inst[50],opt[10],fn[10],ch,ch1;
	int c=0,ln=0,wc=0;
	sscanf(cmd,"%s %s %s",inst,opt,fn);
	fp=fopen(fn,"r");
	
	if(fp==NULL)
	{
		printf("File does not exist \n");
		exit(0);
	}
	else
	{
		while(!feof(fp))
		{
			ch=fgetc(fp);
			c++;
			if (ch==' ' || ch=='\n' || ch==',' || ch=='\t')
				wc++;
			if (ch=='\n')
				ln++;
		}
	}
	fclose(fp);
	
	if (strcmp(opt,"l")==0)
		printf("Number of lines are %d ",ln); 
	else if (strcmp(opt,"w")==0)
		printf("Number of words are %d ",wc);
	else if (strcmp(opt,"c")==0)
		printf("Number of characters %d",c);
}

void typeline()
{
	int n=0,i,x,opt;
	char line[100][100],fn[10],op[50];
	sscanf(cmd,"%s %s %s",inst,op,fn);
	fp=fopen(fn,"r");
	if (fp==NULL)
		printf("File Doesnot Exist ");
	else
	{
		while (!feof(fp))
		{
			fgets(line[n],80,fp);
			n++;
		}
	}
	fclose(fp);
	
	if(op[0]=='a')
	{
		printf("\n All lines in file are : ");
		for (i=0;i<n;i++)
			printf("\n %s",line[i]);
	}
	else
	{
		opt=atoi(op);
		if (opt>0)
			x=0;
		else
		{
			x=n+opt-1;
			opt=n;
		}
		for (i=x;i<opt;i++)
			puts(line[i]);
	}
}
int main()
{
	int i,status=0;
	char op[50],tok[50];
	pid_t pid;
	while (strcmp(tok,"exit")!=0)
	{
		printf("\n\nmyshell$");
		i=-1;
		do
		{
			i++;
			cmd[i]=getchar();
		}while (cmd[i]!='\n');
		cmd[i++]='\0';
		sscanf(cmd,"%s",tok);
		if (strcmp(tok,"count")==0)
			count();
		else if (strcmp(tok,"typeline")==0)
				typeline();
		/*else if (strcmp(tok,"search"==0)
				search();*/
		else
		{
			pid=fork();
			if (pid==0)
			{
				system(cmd);
				exit(0);
			}
			pid=waitpid(pid,&status,0);
		}
	}
	return;
}

/*OUTPUT 1
ty60@pc22:~/Desktop/Ty60/OS/Assignment no.2/Set A$ cc myshell1.c
myshell1.c: In function ‘main’:
myshell1.c:69:8: warning: implicit declaration of function ‘fork’ [-Wimplicit-function-declaration]
   69 |    pid=fork();
      |        ^~~~
myshell1.c:75:8: warning: implicit declaration of function ‘waitpid’ [-Wimplicit-function-declaration]
   75 |    pid=waitpid(pid,&status,0);
      |        ^~~~~~~
myshell1.c:78:2: warning: ‘return’ with no value, in function returning non-void
   78 |  return;
      |  ^~~~~~
myshell1.c:45:5: note: declared here
   45 | int main()
      |     ^~~~
ty60@pc22:~/Desktop/Ty60/OS/Assignment no.2/Set A$ ./a.out


myshell$count c nice.c
Number of characters 1025

myshell$count w nice.c
Number of words are 207 

myshell$count l nice.c
Number of lines are 46 

OUTPUT 2
ty60@pc22:~/Desktop/Ty60/OS/Assignment no.2/Set A$ cc myshell1.c
myshell1.c: In function ‘main’:
myshell1.c:107:8: warning: implicit declaration of function ‘fork’ [-Wimplicit-function-declaration]
  107 |    pid=fork();
      |        ^~~~
myshell1.c:113:8: warning: implicit declaration of function ‘waitpid’ [-Wimplicit-function-declaration]
  113 |    pid=waitpid(pid,&status,0);
      |        ^~~~~~~
myshell1.c:116:2: warning: ‘return’ with no value, in function returning non-void
  116 |  return;
      |  ^~~~~~
myshell1.c:83:5: note: declared here
   83 | int main()
      |     ^~~~
ty60@pc22:~/Desktop/Ty60/OS/Assignment no.2/Set A$ ./a.out


myshell$ typeline a try.c

 All lines in file are : 
 NAME : SHRUTI

 Roll NO : 06

 Mobile NO : 36523652983

 uifbgiud

 sifdphid

 sncsioxs

 cisodhsio

 

myshell$ typeline 3 try.c
NAME : SHRUTI

Roll NO : 06

Mobile NO : 36523652983



myshell$ typeline -4 try.c
uifbgiud

sifdphid

sncsioxs

cisodhsio


*/
