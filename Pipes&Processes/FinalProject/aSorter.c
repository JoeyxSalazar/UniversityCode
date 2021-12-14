#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
//#include <io.h>
#include <sys/types.h>
#include <sys/wait.h>
#define lenMax 50
#define lines 300
 

typedef struct{
    char **array;
    int amtIdx;
    int size;
} vector;

void createVec(vector *vec)
{
    vec->array = malloc(sizeof(char) * lenMax);
    vec->amtIdx = 0;
    vec->size = 1;
}

void insert(vector *vec, char str[lenMax])
{
    if(vec->amtIdx == vec->size)
    {
        vec->size *= 2;
        vec->array = realloc(vec->array, vec->size * sizeof(char)*lenMax);
    }
    vec->array[vec->amtIdx++] = strdup(str);
}

void printDatanum(char **arr, const int len, int num) {
	for(int i=0;i<len;i++) {
        fprintf(stdout, "%i",num);
        fprintf(stdout,"%s\n",arr[i]);
    }
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

void aSorter(int num)
{
    char hold[lenMax]; int strsize =0; 
    memset((void *)hold, '\0',lenMax);
    vector one;
    createVec(&one);
    
    char c;
    while((c = getc(stdin))!=EOF)
    {
        if(c == 10) //new line detected
        {
            hold[strsize] = '\0';
            insert(&one, hold);
            memset((void *)hold, '\0',lenMax);
            strsize = 0;
        }
        else
        {
            hold[strsize] = c; 
            strsize++;
        }
    }
    bsort(one.array,one.amtIdx); 
    printDatanum(one.array, one.amtIdx, num);
}

int main(int argc, char *argv[])
{
    int in = atoi(argv[1]);
    aSorter(in);
    return 0;
}