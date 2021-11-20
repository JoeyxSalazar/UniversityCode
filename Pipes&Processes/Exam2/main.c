#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


void print(char in[4])
{
    for(int i=0; i < 4; i++)
    {
        printf("%c",in[i]);
    }printf("\n");
}

unsigned int Oper2(char in[4])
{
    unsigned int res = 0;
    res = res | (in[1] << 24);
    res = res | (in[3] << 16);
    res = res | (in[2] << 8);
    res = res | in[0];
    return res;
}

void runChild2(int pipe)
{
    char hold[4];
    unsigned int res = 0;
    while((read(pipe,&hold,4)) != EOF)
    {
        if(hold[0] == 13 && hold[1] == 13 && hold[2] == 13 && hold[3] == 13 )
        {
            break;
        }
        unsigned int ir=Oper2(hold);
        printf("ir:%u\n",ir);
        res+=ir;
    }
    res = res % 4294967296;
    printf("Final Result: %u\n",res);
}

void Oper1(char *in, char *out)
{
    out[0] = (in[0] | in[1]) & (in[2] | in[3]);
    out[1] = in[2];
    out[2] = in[1];
    out[3] = in[1] & in[2] & in[3];
}


void runChild1(int inpipe, int outpipe)
{
    char ch; int c=0;
    char hold[4];
    printf("Output: \n");
    while((read(inpipe,&ch, 1)) != EOF)
    {
        if(ch == 13)
        {
            while(c != 4)
            {
                hold[c] = 'z';
                c++;
            }
            print(hold);
            char send[4];
            Oper1(hold, send);
            write(outpipe,&send,4);
            break;
        }
        else
        {
            hold[c] = ch;
            c++;
            if(c == 4)
            {
                print(hold);
                char send[4];
                Oper1(hold, send);
                write(outpipe,&send,4);
                c = 0;
            }
        }
    }
    write(outpipe,"\r\r\r\r",4);  
}


int main()
{
  
    int pids[2];
    int pipes[2][2];
    for(int i =0; i < 2; i++)
    {
        pipe(pipes[i]);
    }   
//Child one
    pids[0] = fork();
    if(pids[0] == 0)
    {
        close(pipes[1][0]);
        close(pipes[0][1]);
        runChild1(pipes[0][0],pipes[1][1]);
        close(pipes[0][0]);
        close(pipes[1][1]);
        exit(0);
    }
//Child two
    pids[1] = fork();
    if(pids[1] == 0)
    {
        close(pipes[0][0]);
        close(pipes[0][1]);
        close(pipes[1][1]);
        runChild2(pipes[1][0]);
        close(pipes[1][0]);
        exit(0);
    } 
//Parent
    close(pipes[0][0]);
    close(pipes[1][0]);
    close(pipes[1][1]);
    char c;
    while((c = getc(stdin))!=EOF)
    {
        write(pipes[0][1],&c,1);
    }
    write(pipes[0][1],"\r",1);
    waitpid(pids[0],NULL,0);
    waitpid(pids[1],NULL,0);
    close(pipes[0][1]);
    return 0; 
}
/*
jes409@rabbit:~/FourthSemester/SysPro/THExam2 % a.out < test.txt
Output:
abcd

zzz
ir:1667261027
ir:2054847098
Final Result: 3722108125


jes409@rabbit:~/FourthSemester/SysPro/THExam2 % a.out < test2.txt
Output: 
The     
quic    
k br    
own     
fox     
jump    
ed o    
ver     
the
lazy
 dog
.
zz
ir:1696622692
ir:1767994721
ir:1646272610
ir:1847621486
ir:2015391592
ir:1835038077
ir:538993765
ir:1914725746
ir:1696622692
ir:2053136745
ir:1868850276
ir:2047478314
Final Result: 3748879532
*/