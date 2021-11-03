#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifdef DEBUG
#define PDEBUG 1
#else
#define PDEBUG 0
#endif

#define DPRINT(fmt, ...) do { if (PDEBUG) fprintf(stderr, "%s:%d:%s(): "fmt,\
        __FILE__, __LINE__, __func__, ##__VA_ARGS__); } while (0)

#define ALEN 250
#define LLEN 50

int readData(char *fname, char **arr, const int len)
{
    char line[LLEN];
    int count = 0;
    FILE *fin = fopen(fname, "r");
    if (fin)
    {
        memset((void *)line, '\0', LLEN);
        while ((count < len) && (fscanf(fin, "%s", line) != EOF))
        {
            arr[count] = strdup(line);
            memset((void *)line, '\0', LLEN);
            count++;
        }
    }
    fclose(fin);
    return count;
}

int readPipe(int *pipe, char **arr, const int len)
{
    char line[LLEN];
    int count = 0;

    memset((void *)line, '\0', LLEN);
    while ((count < len) && (read(*pipe, line, LLEN) != EOF))
    {
        arr[count] = strdup(line);
        memset((void *)line, '\0', LLEN);
        count++;
    }
    return count;
}

void printData(char **arr, const int len) {
	for(int i=0;i<len;i++) printf("%s\n",arr[i]);
}

void bsort(char **arr, const int len) {
	for(int i=0;i<len;i++) {
		for(int j=0;j<len-i-1;j++) {
			if (strcmp(arr[j],arr[j+1])>0) {
				char *tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}

void writeFile(char **data, int i, int len)
{
    char *fname = (char *)malloc(sizeof(char *) * 8 + sizeof(int));
    sprintf(fname, "file%i.txt", i);
    FILE *file = fopen(fname,"w");
    for (int k = 0; k < len  ; k++)
    {
        fprintf(file, "%s\n",data[k]); 
    }
    fclose(file);
}

void writetochild3(int pipe, int half)
{
    char **f1;
	f1 = (char **)malloc(sizeof(char *)*ALEN);
    int f1len = readData("file1.txt", f1, half);
    char **f2;
	f2 = (char **)malloc(sizeof(char *)*ALEN);
    int f2len = readData("file2.txt", f2, half);

    for (int k = 0; k < half ; k++)
    {
        write(pipe, f1[k], LLEN); // writing to pipe 3
    }
    for (int k = 0; k < half ; k++)
    {
        write(pipe, f2[k], LLEN); // writing to pipe 3
    }
    close(pipe);
}

void mergeData(char **data, char **f1, char **f2, int l)
{
    int f1c, f2c, n =0;
    while(f1c < l && f2c)
    {
        if(strcmp(f1[f1c], f2[f2c]) < 0)
        {
            data[n] = f1[f1c];
            n++; f1c++;
        }
        else
        {
            data[n] = f2[f2c];
            n++; f2c++;
        }
    }
    /*
    while(f1c < l)
    {
        data[n] = f1[f1c];
        n++; f1c++;
    }
    while(f2c < l)
    {
        data[n] = f2[f2c];
        n++; f2c++;
    }
   */
}




void runChild3(int *pipe3, char **f1, char **f2)
{
    char **data;
	data = (char **)malloc(sizeof(char *)*ALEN);
	DPRINT("child reading data\n"); 
    int len = readPipe(pipe3,data,ALEN);
    /*
    char **f1;
	f1 = (char **)malloc(sizeof(char *)*ALEN); //***************Couldnt get to work this way
    for(int i=0; i < 250; i++)
    {
        f1[i] = data[i];
    }
    char **f2;
	f2 = (char **)malloc(sizeof(char *)*ALEN);
    for(int i =125; i < 250; i++)
    {
        f2[i-125] = data[i];
    }
    */
    //merge
    FILE *file = fopen("file3.txt","w");
    mergeData(data, f1, f2, len/2);
    for (int k = 0; k < len  ; k++)
    {
        fprintf(file, "%s\n",data[k]); // writing to file 3
    }
    fclose(file);
    //printData(data,len);
    free(data);
    free(f1);
    free(f2);
}

void runChildCode(int *pipe, int length, int i) {

	DPRINT("child starting\n");

	char **data;
	data = (char **)malloc(sizeof(char *)*ALEN);
	DPRINT("child reading data\n"); 
    int len = readPipe(pipe,data,length);
	bsort(data,len);
    //printData(data,len);
    writeFile(data,i,len);
	for(int i=0;i<len;i++) free(data[i]);
	free(data);
	DPRINT("child done\n");
}



int main()
{
    int pid; //three different children
    int pipes[3][2]; //three pipes, each with descriptors
    for(int i=0; i <3; i++)
    {
        pipe(pipes[i]);
    }

    char **data1;
    data1 = (char **)malloc(sizeof(char*) * ALEN);
    //int len = readData("d1.dat",data1,ALEN);
    int len = readData("d2.dat",data1,ALEN);
    //int len = readData("d3.dat",data1,ALEN);
    //int len = readData("d4.dat",data1,ALEN);
    int half = len/2;

    printf("Length: %i\n",len);
//******************************************************************child 1
    pid = fork();
    if (pid==0) { // child code
        int mypid = getpid();
        DPRINT("child(%d): started\n",mypid);
        runChildCode(&pipes[0][0], half, 1);
        DPRINT("child(%d): end\n",mypid);
        exit(0);
    } 
//****************************************************************parent of child 1
    int mypid = getpid();
	DPRINT("parent(%d):continue\n",mypid);
    for (int k = 0; k < half ; k++)
    {
        write(pipes[0][1], data1[k], LLEN); // writing to pipe 1
    }
    close(pipes[0][1]);
    waitpid(pid, NULL, 0);


//******************************************************************child 2
    pid = fork();
    if (pid==0) { // child code
        int mypid = getpid();
        DPRINT("child(%d): started\n",mypid);
        runChildCode(&pipes[1][0], half, 2);
        DPRINT("child(%d): end\n",mypid);
        exit(0);
    } 
//****************************************************************parent of child 2
    mypid = getpid();
	DPRINT("parent(%d):continue\n",mypid);
    for (int k = half; k < len  ; k++)
    {
        write(pipes[1][1], data1[k], LLEN); // writing to pipe 2
    }
    close(pipes[1][1]);
    waitpid(pid, NULL, 0);
//***************************************************************child 3
    //close(pipes[0][0])
    char **f1;
	f1 = (char **)malloc(sizeof(char *)*(ALEN/2));
    int f1len = readData("file1.txt", f1, half);
    char **f2;
	f2 = (char **)malloc(sizeof(char *)*(ALEN/2));
    int f2len = readData("file2.txt", f2, half);
    pid = fork();
    if (pid==0) { // child code
        int mypid = getpid();
        DPRINT("child(%d): started\n",mypid);
        runChild3(&pipes[2][0],f1, f2);
        DPRINT("child(%d): end\n",mypid);
        exit(0);
    } 
//***************************************************************parent of child 3
    mypid = getpid();
	DPRINT("parent(%d):continue\n",mypid);
    writetochild3(pipes[2][1],half);
    waitpid(pid, NULL, 0);

    return 0;
}