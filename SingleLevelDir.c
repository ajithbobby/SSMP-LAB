#include<string.h>
#include<stdlib.h>
#include<stdio.h>
struct file{
	char dir_name[10];
	char file_name[10][10];
	int file_count;
}dir;
void main(){
	int ch,i,j,flag=-1;
	char temp[10];
	printf("Enter directory name:");
	scanf("%s",dir.dir_name);
	dir.file_count=0;
	while(1){
		printf("\n-------------------------------------------------------------------------");
		printf("\n1.Create file\t2.Delete file\t3.Search file\t4.List all files   5.Exit");
		printf("\n-------------------------------------------------------------------------");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				printf("Enter the file name:");
				scanf("%s",dir.file_name[dir.file_count++]);
				break;
			case 2:
				flag=-1;
				printf("Enter the name of the file to delete:");
				scanf("%s",temp);
				for(i=0;i<dir.file_count;i++){
					if(strcmp(temp,dir.file_name[i])==0){
						printf("\nFile deleted!!");
						flag=1;
						for(j=i;j<dir.file_count;j++)
							strcpy(dir.file_name[j],dir.file_name[j+1]);
						dir.file_count--;
					}
				}
				if(flag==-1)
					printf("File not found!!");
				break;
			case 3:
				printf("Enter the file name to search:");
				scanf("%s",temp);
				for(i=0;i<dir.file_count;i++){
					if(strcmp(temp,dir.file_name[i])==0){
						printf("File found!!");
						printf("\nLocation:%s/%s",dir.dir_name,dir.file_name[i]);
						break;
					}
				}
				if(i==dir.file_count)
					printf("File not found!!");
				break;
			case 4:
				if(dir.file_count==0)
					printf("\nNo files found");
				for(i=0;i<dir.file_count;i++){
					printf("\n%s/%s",dir.dir_name,dir.file_name[i]);
				}
				break;
			case 5:
				exit(0);
			default:
				printf("\nWrong input");
		}
	}
}
