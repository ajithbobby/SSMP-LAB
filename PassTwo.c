#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int start,loc,length,flag1,flag2,finaddr,tstart,oplen,i,count,oplen2;
	char code1[100],op1[100],op2[100],op[100],label[100],opcode[100],operand[100],opcode1[100],mcode[100],mcode1[100],symbol[100];
	char location[100],disp[100],code[100],address[100],len[100];
	FILE *f1,*f2,*f3,*f4,*f5;
	f1 = fopen("objcode.txt","w");
	f2 = fopen("optab.txt","r");
	f3 = fopen("intermediate.txt","r");
	f4 = fopen("symtab.txt","r");
	f5 = fopen("length.txt","r");
	fscanf(f5,"%s",len);
	length = atoi(len); 
	fscanf(f3,"%s %s %s %s %s",address,len,label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		start = atoi(operand);
		finaddr = length+start;
		fprintf(f1,"H^%s^00%s^00%d\n",label,operand,finaddr);	
		fscanf(f3,"%s %s %s %s %s",address,len,label,opcode,operand);
	}
	tstart = start;
	fprintf(f1,"T^00%d^%d^",tstart,length);
	while(strcmp(opcode,"END")!=0)
	{
		fseek(f2, SEEK_SET, 0);
		fscanf(f2,"%s %s",opcode1,mcode1);
		while(!feof(f2))
		{
			flag1 = 0;
			if(strcmp(opcode,opcode1)==0)
			{	
				flag1 = 1;
				//printf("%s %s",opcode1,mcode1);
				break;
			}
			fscanf(f2,"%s %s",opcode1,mcode1);
		}
		if(flag1 == 1)
		{
			fscanf(f4,"%s %s",symbol,location);
			while(!feof(f4))
			{
				flag2 = 0;
				if(strcmp(operand,symbol)==0)
				{
					flag2 = 1;
					break;
				}
				fscanf(f4,"%s %s",symbol,location);
			}
			if(flag2==1)
				strcpy(disp,location);
			else if(strcmp(operand,"-")==0)
				strcpy(disp,"0000");
			else
				printf("Symbol error");
			//addr to 6digit obj code
			strcpy(code,disp);
			fprintf(f1,"%s%s^",mcode1,code);
		}
		else if((strcmp(opcode,"BYTE")==0))
		{
			oplen = strlen(operand)-3;
			count = 0;
			for(i=2;i<oplen+2;i++)
			{
				//itoa(operand[i],op,16);
				sprintf(op,"%x",operand[i]);
				fprintf(f1,"%s",op);
				count++;
				if(count==3)
				{
					count = 0;
					fprintf(f1,"^");
				}
			}
		}
		else if(strcmp(opcode,"WORD")==0)
		{
			//itoa(atoi(operand),op1,10);
			sprintf(op1,"%s",operand);
			fprintf(f1,"^00000%s",op1);
		}
		fscanf(f3,"%s %s %s %s %s",address,len,label,opcode,operand);
	}
	fprintf(f1,"\nE^00%d\n",start);
	fclose(f1);
	fclose(f2);
	fclose(f3);	
}
