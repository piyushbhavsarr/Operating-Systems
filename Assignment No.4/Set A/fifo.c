#include<stdio.h>
#define MAX 20
int frames[MAX],ref[MAX],mem[MAX][MAX],faults,sp,m,n;

void accept()
{
	int i;
	printf("Enter Number of frames : ");
	scanf("%d",&n);
	
	printf("Enter Number of references : ");
	scanf("%d",&m);
	
	printf("Enter references string : ");
	for (i=0;i<m;i++)
	{
		printf("[%d] : ",i);
		scanf("%d",&ref[i]);
	}
}

void disp()
{
	int i,j;
	for (i=0;i<m;i++)
		printf("%3d",ref[i]);
	printf("\n\n");
	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
		{
			if (mem[i][j])
				printf("%3d",mem[i][j]);
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("Total Page Faults : %d \n",faults);
}

int search(int pno)
{
	int i;
	for (i=0;i<n;i++)
	{
		if(frames[i]==pno)
			return i;
	}
	return -1;
}

void fifo()
{
	int i,j;
	for(i=0;i<m;i++)
	{
		if(search(ref[i])==-1)
		{
			frames[sp]=ref[i];
			sp=(sp+1)%n;
			faults++;
			for (j=0;j<n;j++)
				mem[j][i]=frames[j];
		}
	}
}

int main()
{
	accept();
	fifo();
	disp();
	return 0;
}
/*OUTPUT
ty60@pc22:~/Desktop/Ty60/OS/Assignment No.4/Set A$ cc fifo.c
ty60@pc22:~/Desktop/Ty60/OS/Assignment No.4/Set A$ ./a.out
Enter Number of frames : 3 
Enter Number of references : 16
Enter references string : [0] : 12
[1] : 15
[2] : 12
[3] : 18
[4] : 6
[5] : 8
[6] : 11
[7] : 12
[8] : 19
[9] : 12
[10] : 6
[11] : 8
[12] : 12
[13] : 15
[14] : 19
[15] : 8
 12 15 12 18  6  8 11 12 19 12  6  8 12 15 19  8

 12 12  12  6  6  6 12 12  12  8  8  8 19 19
  15  15 15  8  8  8 19  19 19 12 12 12  8
    18 18 18 11 11 11   6  6  6 15 15 15
Total Page Faults : 14 
*/
