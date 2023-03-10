#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int start,loc,length,flag;
	char label[100],opcode[100],operand[100],opcode1[100],mcode[100],mcode1[100];
	FILE *f1,*f2,*f3,*f4,*f5;
	f1 = fopen("input.txt","r");
	f2 = fopen("optab.txt","r");
	f3 = fopen("intermediate.txt","w");
	f4 = fopen("symtab.txt","w");
	f5 = fopen("length.txt","w");
	fscanf(f1,"%s %s %s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		start = atoi(operand);
		length=0;
		loc = start;
		fprintf(f3,"- - %s %s %s\n",label,opcode,operand);
		fscanf(f1,"%s %s %s",label,opcode,operand);
	}
	else
		loc = 0;
	while(strcmp(opcode,"END")!=0)
	{
		if((strcmp(label,"-")!=0)&&(strcmp(opcode,"START")!=0)&&(strcmp(opcode,"END")!=0))
		{
			fprintf(f4,"%s %x\n",label,loc+3096);
		}
		fseek(f2, SEEK_SET, 0);
		fscanf(f2,"%s %s",opcode1,mcode1);
		while(!feof(f2))
		{
			flag = 0;
			if(strcmp(opcode,opcode1)==0)
			{	
				flag = 1;
				length = 3;
				break;
			}
			fscanf(f2,"%s %s",opcode1,mcode1);
		}
		if(flag == 0)
		{
			if(strcmp(opcode,"RESB")==0)
			{
				length = atoi(operand);
			}
			else if(strcmp(opcode,"RESW")==0)
			{
				length = atoi(operand)*3;
			}
			else if(strcmp(opcode,"WORD")==0)
			{
				length = 3;
			}
			else if(strcmp(opcode,"BYTE")==0)
			{
				if(operand[0]=='C')
				{
					length = strlen(operand)-2;
				}
				else if(operand[0] == 'X')
					length++;
			}
			else if(opcode[0] == '+')
			{
				length=4;	
			}
			else
			{
				length = 3;
			}
		}
		if(strcmp(opcode,"END")!=0)
		{
			printf("%x %d %s %s %s\n",loc+3096,length,label,opcode,operand);	
			fprintf(f3,"%x %d %s %s %s\n",loc+3096,length,label,opcode,operand);
		}
		fscanf(f1,"%s %s %s",label,opcode,operand);
		loc+=length;
	}
	printf("%x - %s %s %s\n",loc+3096,label,opcode,operand);
	fprintf(f3,"%x - %s %s %s\n",loc+3096,label,opcode,operand);
	fprintf(f5,"%d",loc-start);
	printf("Length=%d",loc-start);
	fclose(f1);
	fclose(f2);
	fclose(f3);	
}
