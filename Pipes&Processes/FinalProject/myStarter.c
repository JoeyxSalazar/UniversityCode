#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
//#include <io.h>
#include <sys/types.h>
#include <sys/wait.h>

//myStarter fileReader file1.txt file2.txt aSorter theMerger file3.txt
int main(int argc, char *argv[])
{

    int pids[5];
    int pipes[3][2];
    for(int i=0; i< 3; i++)
    {
        pipe(pipes[i]);
    }
    
    //Child One--------------->fileReader1
    pids[0] = fork();
    if(pids[0] == 0)
    {
        close(pipes[0][0]); //close pipe1 read
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]); close(pipes[2][1]); 
        dup2(pipes[0][1], STDOUT_FILENO); //connecting to pipe 1
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
        dup2(pipes[1][1], STDOUT_FILENO); //connecting to pipe 2
        char * childtwoargs[] = {argv[1],argv[3], NULL};
        execvp(argv[1],childtwoargs);
        exit(0);
    }
    //Child Three------------>aSorter1
    pids[2] = fork();
    if(pids[2] == 0)
    {
        close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][0]);
        dup2(pipes[0][0], STDIN_FILENO); //reading pipe 1 as input
        dup2(pipes[2][1], STDOUT_FILENO);
        char *childthreeargs[] = {argv[4],"1",NULL};
        execvp(argv[4],childthreeargs);
        exit(0);
    }
    //Child Four------------>aSorter2
    pids[3] = fork();
    if(pids[3] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][1]);
        close(pipes[2][0]);
        dup2(pipes[1][0], STDIN_FILENO); //reading pipe 2 as input
        dup2(pipes[2][1], STDOUT_FILENO);
        char *childfourargs[] = {argv[4],"2",NULL};
        execvp(argv[4],childfourargs);
        exit(0);
    }
    //Child Five------------>theMerger
    pids[4] = fork();
    if(pids[4] == 0)
    {
        close(pipes[0][0]); close(pipes[0][1]);
        close(pipes[1][0]); close(pipes[1][1]);
        close(pipes[2][1]);
        dup2(pipes[2][0],STDIN_FILENO);
        char *childfiveargs[] = {argv[5],argv[6],NULL};
        execvp(argv[5], childfiveargs);
        exit(0);
    }

    //Parent
    close(pipes[0][0]); close(pipes[0][1]);
    close(pipes[1][0]); close(pipes[1][1]);
    close(pipes[2][0]); close(pipes[2][1]);
    
    waitpid(pids[4], NULL, 0);
    return 0;
}