#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>



//Recursion for directories and print for files that match
int compare(char* dname, char* item)
{
	int y= strlen(item);
	int c = 0;
	for(int i=0; i<y; i++)
	{
		if(dname[i] == item[i])
			c++;
	}
	if(c == y)
		return 1;
	else
		return 0;
}

int find(char *given, char *item,int *c)
{
	DIR *dirp = NULL;
    struct dirent *d = NULL;
    char *filename = NULL;
    struct stat finfo;
    struct passwd *pw = NULL;
    struct group *gr = NULL;
    int set =1; 


    dirp = opendir(given);
    char *type, *owner, *grp;
    char *AccT, *ModT, *ChgT;
    int size, blksize;
    long int blks;
    int flag= 0;
    
 	//printf("%s %s %s %s\n\n","Searching for",item, "in",given);
    while(((d = readdir(dirp)) != NULL)){
        char *path = (char *)malloc(sizeof(char)*strlen(d->d_name));
        sprintf(path,"%s%s", given, d->d_name);
        if(d->d_name[0] != '.'){
	        if((lstat(path, &finfo) == 0)){
	            if (S_ISDIR(finfo.st_mode)) {
	                type = "Directory";
	                find(path,item,c);
	            }
	            else if (S_ISREG(finfo.st_mode)) { 
	                if ((finfo.st_mode & S_IXUSR) == S_IXUSR) {
	                    type = "Executable";
	                }
	                else
	                	type = "Regular";
	            }
	            else if (S_ISLNK(finfo.st_mode)) {
	                if ((finfo.st_mode & S_IFLNK) == S_IFLNK ){ 
	                    type = "Link";
	                }
	            }
	            else if (S_ISFIFO(finfo.st_mode)) { 
	                if ((finfo.st_mode & S_IFIFO) == S_IFIFO ){ 
	                     type = "FIFO";
	                }
	            }
	            //printf("%s","Determined what type");
	            pw = getpwuid(finfo.st_uid);
	            gr = getgrgid(finfo.st_gid);
	            size = finfo.st_size;
	            blks = finfo.st_blocks;
	            blksize = finfo.st_blksize;
	            if(compare(d->d_name, item) == 1)
	            {
		            printf("%s\n","**********************************");
		            printf("%s: %s\n","Path",path);
		            printf("%s: %s\n","Type", type);
		            printf("%s: %i %s\n","Size", size, "Bytes");
		            printf("%s: %i %s\n","Blks", blks, "Blocks");
		            printf("%s: %i %s\n","BlkSz",blksize, "Bytes");
		            printf("%s: %s\n","Ownr",pw->pw_name);
		            printf("%s: %s\n","Grup",gr->gr_name);
		            printf("%s: %s", "AccT",ctime(&finfo.st_atime));
		            printf("%s: %s", "ModT",ctime(&finfo.st_mtime));
		            printf("%s: %s", "ChgT",ctime(&finfo.st_ctime));
		            printf("%s\n","**********************************");
		            *c +=1;
		        }  	         
        	}	
        }
        
    }
}

int main(int argc, char *argv[]) {
	DIR *dirp = NULL;
    struct dirent *d = NULL;
    char *filename = NULL;
    struct stat finfo;
    struct passwd *pw = NULL;
    struct group *gr = NULL;
    int c=0;

    if (argc<2) {
        fprintf(stderr,"usage: %s <pathname>\n", argv[0]);
        return -1;
    }

    dirp = opendir(argv[1]);
    if (dirp == NULL) {
        fprintf(stderr,"Bad path: %s\n", argv[1]);
        return -1;
    }
    closedir(dirp);

//argv[1] is the path and argv[2] is the name to look for
find(argv[1], argv[2], &c);
printf("%s %i %s %s\n","Found", c,"occurences of",argv[2]);
}