#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
//#include <io.h>
#include <sys/types.h>
#include <sys/wait.h>


//myStarter2 fileReader file1.txt file2.txt file3.txt file4.txt aSorter theMerger file5.txt
int main(int argc, char *argv[])
{

    int pids[11];
    int pipes[7][2];
    for(int i=0; i< 7; i++)
    {
        pipe(pipes[i]);
    }
    
    //Child One--------------->fileReader1
    pids[0] = fork();
    if(pids[0] == 0)
    {
        close(pipes[0][0]); 
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); close(pipes[4][1]);
        close(pipes[5][0]); close(pipes[5][1]);
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[0][1], STDOUT_FILENO);            //connecting to pipe 1
        char *childoneargs[] = {argv[1],argv[2],NULL};
        execvp(argv[1],childoneargs);
        exit(0);
    }
    //Child Two------------>fileReader2
    pids[1] = fork();
    if(pids[1] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); 
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); close(pipes[4][1]);
        close(pipes[5][0]); close(pipes[5][1]);
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[1][1], STDOUT_FILENO);           //connecting to pipe 2
        char *childtwoargs[] = {argv[1],argv[3], NULL};
        execvp(argv[1],childtwoargs);
        exit(0);
    }
    //Child Three------------>fileReader3
    pids[2] = fork();
    if(pids[2] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); 
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); close(pipes[4][1]);
        close(pipes[5][0]); close(pipes[5][1]);
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[2][1], STDOUT_FILENO);           //connecting to pipe 3
        char *child3[] = {argv[1],argv[4], NULL};
        execvp(argv[1],child3);
        exit(0);
    }
    //Child Four------------>fileReader4
    pids[3] = fork();
    if(pids[3] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); 
        close(pipes[4][0]); close(pipes[4][1]);
        close(pipes[5][0]); close(pipes[5][1]);
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[3][1], STDOUT_FILENO);           //connecting to pipe 4
        char *child4[] = {argv[1],argv[5], NULL};
        execvp(argv[1],child4);
        exit(0);
    }
    //Child Five------------>aSorter1
    pids[4] = fork();
    if(pids[4] == 0)
    {
                            close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); 
        close(pipes[5][0]); close(pipes[5][1]);
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[0][0], STDIN_FILENO);            //reading pipe 1 as input
        dup2(pipes[4][1], STDOUT_FILENO);           //writing to pipe 5
        char *child5[] = {argv[6],"1",NULL};
        execvp(argv[6],child5);
        exit(0);
    }
    //Child Six------------>aSorter2
    pids[5] = fork();
    if(pids[5] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
                            close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); 
        close(pipes[5][0]); close(pipes[5][1]);
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[1][0], STDIN_FILENO);        //reading pipe 2 as input
        dup2(pipes[4][1], STDOUT_FILENO);       //writing to pipe 5
        char *child6[] = {argv[6],"2",NULL};
        execvp(argv[6],child6);
        exit(0);
    }
    //Child Seven------------>aSorter3
    pids[6] = fork();
    if(pids[6] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
                            close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); close(pipes[4][1]);
        close(pipes[5][0]); 
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[2][0], STDIN_FILENO);        //reading pipe 3 as input
        dup2(pipes[5][1], STDOUT_FILENO);       //writing to pipe 6
        char *child7[] = {argv[6],"3",NULL};
        execvp(argv[6],child7);
        exit(0);
    }
    //Child Eight------------>aSorter4
    pids[7] = fork();
    if(pids[7] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
                            close(pipes[3][1]);
        close(pipes[4][0]); close(pipes[4][1]);
        close(pipes[5][0]); 
        close(pipes[6][0]); close(pipes[6][1]);
        dup2(pipes[3][0], STDIN_FILENO);        //reading pipe 4 as input
        dup2(pipes[5][1], STDOUT_FILENO);       //writing to pipe 6
        char *child8[] = {argv[6],"4",NULL};
        execvp(argv[6],child8);
        exit(0);
    }

    //Child Nine------------>theMerger1
    pids[8]= fork();
    if(pids[8] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
                            close(pipes[4][1]);
        close(pipes[5][0]); close(pipes[5][1]);
        close(pipes[6][0]); 
        dup2(pipes[4][0],STDIN_FILENO);         //read from pipe 5
        dup2(pipes[6][1],STDOUT_FILENO);        //send to pipe 7
        char *child9[] = {argv[7],"NULL",NULL};
        execvp(argv[7],child9);
        exit(0);
    }

    //Child Ten------------>theMerger2
    pids[9]= fork();
    if(pids[9] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); close(pipes[4][1]);
                            close(pipes[5][1]);
        close(pipes[6][0]); 
        dup2(pipes[5][0],STDIN_FILENO); //read from pipe 6
        dup2(pipes[6][1],STDOUT_FILENO); //send to pipe 7
        char *child10[] = {argv[7],"NULL", NULL};
        execvp(argv[7],child10);
        exit(0);
    }

    //Child Elleven------------>theMerger3
    pids[9]= fork();
    if(pids[9] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]);
        close(pipes[3][0]); close(pipes[3][1]);
        close(pipes[4][0]); close(pipes[4][1]);
        close(pipes[5][0]); close(pipes[5][1]);
                            close(pipes[6][1]);
        dup2(pipes[6][0],STDIN_FILENO); //read from pipe 7
        char *child11[] = {argv[7],argv[8],NULL};
        execvp(argv[7],child11);
        exit(0);
    }

    //Parent
    close(pipes[0][0]); close(pipes[0][1]);
    close(pipes[1][0]); close(pipes[1][1]);
    close(pipes[2][0]); close(pipes[2][1]);
    close(pipes[3][0]); close(pipes[3][1]);
    close(pipes[4][0]); close(pipes[4][1]);
    close(pipes[5][0]); close(pipes[5][1]);
    close(pipes[6][0]); close(pipes[6][1]);

    waitpid(pids[10],NULL, 0);
    return 0;
}