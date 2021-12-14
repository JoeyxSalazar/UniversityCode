#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
//#include <io.h>
#include <sys/types.h>
#include <sys/wait.h>
#define lenMax 15
#define lines 200

int power2(int n)
{
    if(n <= 0)
        return 1;
    if(n == 1)
        return 2;
    int out = 2;
    for(int i=0; i < n - 1; i++)
    {
        out = out * 2;
    }
    return out;
} 

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

void mergeBoth(int s1, int s2, char **arr1, char **arr2, char **three)
{
    int w1 = 0, w2 = 0, k = 0;
    while(w1 < s1 && w2 < s2)
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
    while(w1 < s1)
    {
        three[k] = arr1[w1]; k++; w1++;
    }
    while(w2 < s2)
    {
        three[k] = arr2[w2]; k++; w2++;
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

    vector one; vector two; vector three; vector four;
    createVec(&one); createVec(&two);createVec(&three); createVec(&four);
    char c; char comp; int count = 0;

    while((c = getc(stdin)) != EOF)
    {
        if(c == 10)
        {
            if(hold[0] == '1')
            {
                insert(&one, hold);
            }
            else if(hold[0] == '2')insert(&two, hold);
            else if(hold[0] == '3')insert(&three, hold);
            else insert(&four, hold);
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
    bsortNums(one.array,one.amtIdx); bsortNums(two.array, two.amtIdx);
    char **first; first = (char **)malloc(sizeof(char *) * lines);
    int total1 = one.amtIdx + two.amtIdx;

    bsortNums(three.array,three.amtIdx); bsortNums(four.array, four.amtIdx);
    char **second; second = (char **)malloc(sizeof(char *) * lines);
    int total2 = three.amtIdx + four.amtIdx;

    merge(&one, &two, first);
    merge(&three, &four, second);
    bsortNums(first, total1); bsortNums(second, total2);

    char **third; third = (char **)malloc(sizeof(char *) * lines);
    mergeBoth(total1, total2, first, second, third);

    //printData(three, one.amtIdx + two.amtIdx);
    if(strcmp(fin,"NULL") == 0) printData(third, total1 + total2);
    else{
        //printf("Write to file\n");
        FILE *fout = fopen(fin, "w");
        for(int i =0; i < total1 + total2; i++)
        {
            fprintf(fout,"%s\n",third[i]);
        }
        fclose(fout);
    }
}

int main(int argc, char *argv[])
{
    theMerger(argv[1]);
    return 0;
}

