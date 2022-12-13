#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void make_toks(char *s,char *tok[])
{
	int i=0;
	char *p;
	p=strtok(s, " ");
	while (p!=NULL)
	{
		tok[i++]=p;
		p=strtok(NULL," ");
	}
	tok[i]=NULL;
}

void count(char *fn,char op)
{
	int fh,cc=0,wc=0,lc=0;
	char c;
	fh=open(fn,O_RDONLY);
	if (fh==1)
	{
		printf("File %s not found \n ",fn);
		return;
	}
	
	while (read (fh,&c,1>0))
	{
		if (c==' ')
			wc++;
		else if (c=='\n')
		{
			wc++;
			lc++;
		}
		cc++;
	}
	close(fh);
	switch(op)
	{
		case 'c' : printf("Number of characters : %d \n ",cc-1);
			   break;
			   
		case 'w' : printf("Number of words : %d \n ",wc);
			   break;
			   
		case 'l' : printf("Number of Lines : %d \n ",lc+1);
			   break;
	}
}

int main()
{
	char buff[80],*args[10];
	int pid;
	
	while(1)
	{
		printf("myshell$");
		fflush(stdin);
		fgets(buff,80,stdin);
		buff[strlen(buff)-1]='\0';
		make_toks(buff,args);
		if (strcmp(args[0],"count")==0)
			count(args[2],args[1][0]);
		else
		{
			pid=fork();
			if (pid > 0)
				wait();
			else
			{
				if (execvp(args[0],args)==-1)
					printf("Bad Command\n");
			}
		}
	}
	return 0;
}
/*OUTPUT
ty60@pc24:~/Desktop/Ty60/OS/Assignment no.2/Set A$ ./a.out
myshell$ count c myshell.c
Number of characters : 1185 
 myshell$ count w myshell.c
Number of words : 162 
 myshell$ count l myshell.c
Number of Lines : 85 

*/
