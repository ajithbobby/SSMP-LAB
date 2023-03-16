#include<stdio.h>
#include<stdlib.h>
struct node
{
	char f_name[10];
	int p_size,p_alloc;
}ob[10];
int lim,block[20],block_alloc[20],ind[10];
void insert()
{
	int i;
	printf("Enter the number of files:");
	scanf("%d",&lim);
	for(i=0;i<lim;i++)
	{
		printf("Enter the file name:");
		scanf("%s",ob[i].f_name);
		printf("Enter the size:");
		scanf("%d",&ob[i].p_size);
		ob[i].p_alloc=0;
	}
}
void sequential()
{
	int count=0,n=0,i,prev=0;
	for(i=0;i<lim;i++)
	{
		count=ob[i].p_size+n;
		if(ob[i].p_size<20-n)
		{
			while(n<count)
			{
				block[n]=n;
				n++;
			}
			ob[i].p_alloc=1;
		}
		else
		{
			ob[i].p_alloc=0;
		}
	}
}
void linked()
{
	int l_lim=0,count=0,d=0,r,i;
	for(i=0;i<20;i++)
	{
		block_alloc[i]=0;
	}
	for(i=0;i<lim;i++)
	{
		l_lim=ob[i].p_size+d;
		if(ob[i].p_size<=20-d)
		{
			while(d<l_lim)
			{
				r=rand()%20;
				//printf("%d\t",r);
				if(block_alloc[r]==0)
				{
					block[d]=r;
					d++;
					count++;
					block_alloc[r]=1;
				}
			}
			ob[i].p_alloc=1;
		}
		else
		{
			ob[i].p_alloc=0;
		}
	}
}
void indexed()
{
	int l_lim=0,count=0,d=0,r,i,k=0;
	for(i=0;i<20;i++)
	{
		block_alloc[i]=0;
	}
	for(i=0;i<lim;i++)
	{
		l_lim=ob[i].p_size+d;
		if(ob[i].p_size<=(20-(d+k)))
		{
			while(1)
			{
				r=rand()%20;
				if(block_alloc[r]==0)
				{
					ind[k]=r;
					k++;
					block_alloc[r]=1;
					break;
				}
			}
			while(d<l_lim)
			{
				r=rand()%20;
				//printf("%d\t",r);
				if(block_alloc[r]==0)
				{
					block[d]=r;
					d++;
					count++;
					block_alloc[r]=1;
				}
			}
			ob[i].p_alloc=1;
		}
		else
		{
			ob[i].p_alloc=0;
		}
	}
}
void display()
{
	int d=0,count=0,i;
	printf("\nFile name\tSize\tAlloted blocks");
	for(i=0;i<lim;i++){
		printf("\n%s\t\t%d\t",ob[i].f_name,ob[i].p_size);
		if(ob[i].p_alloc==1){
			count=count+ob[i].p_size;
			while(d<count){
				printf("%d ",block[d++]);
			}
		}
		else{
			printf("Cannot be allocated");
		}
	}
}
void display_indexed(){
	int d=0,count=0,i,j=0;
	printf("\nIndex\tFile name\tSize\tAlloted blocks");
	for(i=0;i<lim;i++){
		printf("\n%d\t%s\t\t%d\t",ind[j++],ob[i].f_name,ob[i].p_size);
		if(ob[i].p_alloc==1){
			count=count+ob[i].p_size;
			while(d<count){
				printf("%d ",block[d++]);
			}
		}
		else{
			printf("Cannot be allocated");
		}
	}
}
void main(){
	int ch;
	while(1){
		printf("\n------------------------------------------------------");
		printf("\n1.Sequential\t2.Linked\t3.Indexed\t4.Exit");
		printf("\n------------------------------------------------------");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				insert();
				sequential();
				display();
				break;
			case 2:
				insert();
				linked();
				display();
				break;
			case 3:
				insert();
				indexed();
				display_indexed();
				break;
			case 4: 
				exit(0);
		}
	}
}
