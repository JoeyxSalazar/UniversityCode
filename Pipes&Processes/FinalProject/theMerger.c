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

void printData(char **arr, const int len) {
	for(int i=0;i<len;i++) {
        fprintf(stdout,"%s\n",arr[i]);
    }
}

void printDatanum(char **arr, const int len, int num) {
	for(int i=0;i<len;i++) {
        printf("%i",num);
        printf("%s\n",arr[i]);
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
int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

void bsortNums(char **arr, const int len) {
	for(int i=0;i<len;i++) {
		for(int j=0;j<len-i-1;j++) {
            arr[j]++; arr[j+1]++;
            if (strcmp(arr[j],arr[j+1])>0) {
				char *tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
            arr[j]--; arr[j+1]--;
		}
	}
}

void merge(vector *one, vector *two, char **three)
{
    int w1 = 0, w2 = 0, k = 0;
    char **arr1, **arr2; arr1 = one->array; arr2 = two->array;
    while(w1 < one->amtIdx && w2 < two->amtIdx)
    {
        char *hold1 = malloc(strlen(arr1[w1]));
        strcpy(hold1, arr1[w1]+1);
        char *hold2 = malloc(strlen(arr2[w2]));
        strcpy(hold2, arr2[w2]+1);
        if(strcmp(hold1, hold2) < 0)
        {
            three[k] = arr1[w1]; k++; w1++;
        }
        else
        {
            three[k] = arr2[w2]; k++; w2++;
        }
    }
    while(w1 < one->amtIdx)
    {
        three[k] = arr1[w1]; k++; w1++;
    }
    while(w2 < two->amtIdx)
    {
        three[k] = arr2[w2]; k++; w2++;
    }
}

void theMerger(char * fin)
{
    char hold[lenMax]; int strsize =0; 
    memset((void *)hold, '\0',lenMax);

    vector one; vector two;
    createVec(&one); createVec(&two);
    char c; char comp; int count = 0;

    while((c = getc(stdin)) != EOF)
    {
        if(c == 10)
        {
            if(hold[0] == comp)
            {
                insert(&one, hold);
            }
            else insert(&two, hold);
            memset((void *)hold, '\0', lenMax);
            strsize = 0;
        }
        else
        {
            if(count == 0)
            {
                comp = c;
            }
            hold[strsize] = c;
            strsize++;
        }
        count++;
    }
    //printData(one.array, one.amtIdx); printf("\n"); printData(two.array, two.amtIdx);
    bsortNums(one.array,one.amtIdx); bsortNums(two.array, two.amtIdx);
    //printData(one.array, one.amtIdx); printf("\n"); printData(two.array, two.amtIdx);
    char **three; three = (char **)malloc(sizeof(char *) * lines);
    int total = one.amtIdx + two.amtIdx;
    merge(&one, &two, three);
    //printData(three, one.amtIdx + two.amtIdx);
    if(strcmp(fin,"NULL") == 0) printData(three, total);
    else{
        //printf("Write to file\n");
        FILE *fout = fopen(fin, "w");
        for(int i =0; i < total; i++)
        {
            fprintf(fout,"%s\n",three[i]);
        }
        fclose(fout);
    }
}

int main(int argc, char *argv[])
{
    theMerger(argv[1]);
    return 0;
}

