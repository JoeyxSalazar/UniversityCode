#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
//#include <io.h>
#include <sys/types.h>
//#include <sys/wait.h>
#define lenMax 50
#define lines 300

void fileReader(char *fin)
{
    sleep(8);
    FILE *file = fopen(fin,"r");
    char line[lenMax];
    if (file)
    {
        memset((void *)line, '\0', lenMax);
        while ((fscanf(file, "%s", line) != EOF))
        {
            fprintf(stdout, "%s\n",line);
            memset((void *)line, '\0', lenMax);
        }
    }
    else
        printf("Error reading file\n");
    fclose(file);
    
}

int main(int argc, char *argv[])
{    
    fileReader(argv[1]);
    return 0;
}

   