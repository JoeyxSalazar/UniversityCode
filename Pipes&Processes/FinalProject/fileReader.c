#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
//#include <io.h>
#include <sys/types.h>
//#include <sys/wait.h>
#define lenMax 15
#define lines 200

void fileReader(char *fin)
{
    FILE *file = fopen(fin,"r");
    char line[lenMax];
    if (fin)
    {
        memset((void *)line, '\0', lenMax);
        while ((fscanf(file, "%s", line) != EOF))
        {
            fprintf(stdout, "%s\n",line);
            memset((void *)line, '\0', lenMax);
        }
    }
    fclose(file);
}

int main(int argc, char *argv[])
{    
    fileReader(argv[0]);
    return 0;
}

