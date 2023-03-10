#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *file;
    int i, j,start_addr;
    char name[10],line[50],temp[10];
    file = fopen("object.txt", "r");
    fscanf(file, "%s", line);
    printf("Enter program name: ");
    scanf("%s", name);
    for (i = 2, j = 0; i < 8, j < strlen(name); i++, j++)
    {
        if (name[j] != line[i])
        {
            printf("Invalid program name.\n");
            return;
        }
    }
    printf("\nLocation\tObject code\n");
    do
    {
        fscanf(file, "%s", line);
        if (line[0] == 'T')
        {
            for (i = 2, j = 0; i < 8, j < 6; i++, j++)
                temp[j] = line[i];
            temp[j] = '\0';
            start_addr = atoi(temp);
            i = 12;
            while (line[i] != '$')
            {
                if (line[i] != '^')
                {
                    printf("00%d\t\t%c%c\n", start_addr, line[i], line[i + 1]);
                    start_addr++;
                    i += 2;
                }
                else
                    i++;
            }
        }
        if (line[0] == 'E')
        {
            printf("\nExecution address: ");
            for (i = 2; i < 8; i++)
                printf("%c", line[i]);
            break;
        }
    } while (!feof(file));
    fclose(file);
}
