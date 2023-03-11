/*
Name:
Blazer ID:
Project #:
To Compile: run the 'make' command in terminal to compile the program
To run:   run using the object file --   eg:-  " ./search -s 1024 " or " ./search -f ead 1 projects " etc.
*/
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int printDirList(char *path,int optionSel);
int getsizeoffile(char *filename);
char* getfilepermissions(char *filepath);
char *getlastaccesstime(char *filepath);
bool checksymbolfileornot(char *filename);
char *getsymbolfilename(char *filename);
void getCmdArgs(char *commd);
void execommand(char *filename);
void getECmdArgs(char *commd);
void runEcommand();
// global variables

char    gfilestr[20];
int     gdepth                  = 0;
int     gfilesize               = 0;
bool    gsmallsEnab             = false;
bool    gbigSEnab               = false;
bool    gsmallFEnab             = false;
bool    gsmalltEnb              = false;
bool    gsmalleEnb              = false;
bool    gbigEEnb                = false;
char    gstrtoption[10];
int     gfileselection          = 0; // 1 - dir , 2 - regular files
int     gTabIndCnt              = 0;
char    command[50] = {0};
char	*argumnets[250];
char    Ecommand[50] = {0};
char	*Eargumnets[250];
int     gcnt =0,gcnt1=0;
FILE    *Op = NULL;

int main(int argc,char **argv)
{

        int     option                  = 0;
        char    strtoption[10];
        int     (*printDirFuncPtr)(char *,int);
        
        while((option = getopt(argc, argv, "Ss:t:f:e:E:")) != -1)
        {

                switch(option)
                {
                        case 'S':
                                gbigSEnab = true;
                                break;
                        case 's':
                                gfilesize = atoi(optarg);
                                gsmallsEnab = true;
                                break;
                        case 'f':
                                strcpy(gfilestr,optarg);
                                gsmallFEnab = true;
                                break;
                        case 't':
                                strcpy(strtoption,optarg);
                                gsmalltEnb = true;
                                break;
                        case 'e':
                                strcpy(command,optarg);
                                getCmdArgs(command);
                                gsmalleEnb = true;
                                break;
                        case 'E':
                                strcpy(Ecommand,optarg);
                                Op = fopen("test.txt","w+");
                                if(Op == NULL)
                                {
                                    printf("Unable to create a file to store file names \"E\" command doesnt work\n");
                                }
                                else
                                {
                                    getECmdArgs(Ecommand);
                                    gbigEEnb   = true;
                                }
                                break;
                }
        }

        if(optind < argc)
        {
                // get the depth argument if -f option paramter is selected 
                if(gsmallFEnab)
                {
                        gdepth = atoi(argv[optind]);
                        optind++;
                }
        }
        
        // get the -t argument and enable flag 
        if(gsmalltEnb)
        {
                if(strcmp(strtoption,"d")==0)
                        gfileselection = 1;
                else
                        gfileselection = 2;
        }

        // used for tab indentation logic 
        gTabIndCnt = 1;

        // simple use of function pointer
        printDirFuncPtr = printDirList;

        // calling printDirList funciton over a function pointer
        if(argv[optind] == NULL)
                printDirFuncPtr(".",0);
        else
                printDirFuncPtr(argv[optind],0);

        if(gbigEEnb)
        {
            if(Op != NULL)
            {
                fclose(Op); // close file once everthig written 
                Op=NULL;
                runEcommand();
            }    
        }

        return 0;
}

void getCmdArgs(char *commd)
{
    char *args = NULL;
    int argcnt = 0;
    
    args = strtok(commd," ");
    argumnets[0] = args;
	while (args != NULL)
	{
		args = strtok(NULL," ");
		argcnt++;
		if(args != NULL)
		{
           argumnets[argcnt] = args;
		}
	}
	gcnt = argcnt;
    argumnets[argcnt+1] = NULL;    
}

void getECmdArgs(char *commd)
{
    char *args = NULL;
    int argcnt = 0;
    
    args = strtok(commd," ");
    Eargumnets[0] = args;
	while (args != NULL)
	{
		args = strtok(NULL," ");
		argcnt++;
		if(args != NULL)
		{
           Eargumnets[argcnt] = args;
		}
	}
	gcnt1 = argcnt;
}

void execommand(char *filename)
{
    pid_t	ChildPid;
	int	ChildStatus = 0;
	argumnets[gcnt] = filename;
	ChildPid = fork();
	if (ChildPid == 0)
	{
	 	execvp(argumnets[0], argumnets);
		exit(0);
	}
	else if (ChildPid > 0)
	{
		waitpid(ChildPid, &ChildStatus,0);
		sleep(1);
	}
}


void runEcommand()
{
    pid_t ChildPid;
	int	ChildStatus = 0;
	char	data[250] = { 0 };
    FILE *Ip = NULL;
    Ip = fopen("test.txt","r+");
    if(Ip == NULL)
    {
        printf("Unable to open file");
        return;
    }

	while (fgets(data, 250, Ip) != NULL)
	{
	        data[strlen(data) - 1] = '\0';
	        Eargumnets[gcnt1] = data;
	        gcnt1++;
	}
	
	Eargumnets[gcnt1] = NULL;    

	ChildPid = fork();
	if (ChildPid == 0)
	{
	 	execvp(Eargumnets[0], Eargumnets);
		exit(0);
	}
	else if (ChildPid > 0)
	{
		waitpid(ChildPid, &ChildStatus,0);
	}
	
	fclose(Ip);
	Ip= NULL;
}

// get the size of file
int getsizeoffile(char *filename)
{
        int size = 0;
        struct stat checkfordir;
        stat(filename, &checkfordir);
        size = checkfordir.st_size;
        return size;
}

// get the file permissions 
char* getfilepermissions(char *filepath)
{
        struct stat st;
        char *permmode = malloc(sizeof(char) * 10);
        if(stat(filepath, &st) == 0)
        {
                mode_t permissons = st.st_mode;
                permmode[0] = (permissons & S_IRUSR) ? 'r' : '-';
                permmode[1] = (permissons & S_IWUSR) ? 'w' : '-';
                permmode[2] = (permissons & S_IXUSR) ? 'x' : '-';
                permmode[3] = (permissons & S_IRGRP) ? 'r' : '-';
                permmode[4] = (permissons & S_IWGRP) ? 'w' : '-';
                permmode[5] = (permissons & S_IXGRP) ? 'x' : '-';
                permmode[6] = (permissons & S_IROTH) ? 'r' : '-';
                permmode[7] = (permissons & S_IWOTH) ? 'w' : '-';
                permmode[8] = (permissons & S_IXOTH) ? 'x' : '-';
                permmode[9] = '\0';
                return permmode;
        }
        else
        {
                return NULL;
        }
}

// get the last access time of a file 
char *getlastaccesstime(char *filepath)
{
        struct stat st;
        char *lastacctime = malloc(sizeof(char) * 32);
        strftime(lastacctime, 32, "%d-%m-%Y %H:%M:%S", localtime(&st.st_atime));
        return lastacctime;
}

// To check whether provided file is having symbolic link or not 
bool checksymbolfileornot(char *filename)
{
        struct stat st;
        lstat(filename, &st);
        if(S_ISLNK(st.st_mode))
                return true;
        else
                return false;
}

// To get the filename of the which it is being redirected by symbolic link file 
char *getsymbolfilename(char *filename)
{
        char *symbfilename = malloc(sizeof(char) * 100);
        if(readlink(filename, symbfilename, 100) < 0)
        {
                perror("readlink() error");
                return NULL;
        }
        return symbfilename;
}

// A whole operational program for printing the directories/files list as per the optional arguments passed 
int printDirList(char *path,int optionSel)
{
        struct dirent *files;
        DIR *dir = NULL;
        char *fullpath = NULL;
        int pathlen = 0;
        char formatstrS[256]= {0};
        char symbolfilename[100] = {0};
        int filesize = 0;
        char *fileperm = NULL;
        char *lastaccesstime =NULL;
        char *substr = NULL;
        int tabIndlooCnt = 0;
        int tempTabIndCnt = 0;
        char *symbfile = NULL;

        dir = opendir(path);
        if (dir == NULL)
        {
                return 0;
        }
        pathlen = strlen(path);
        fullpath = (char *)malloc((pathlen*2));
        if(optionSel ==0)
                printf("%s\n",path);

        while ((files = readdir(dir)) != NULL)
        {
                if (strcmp(files->d_name, ".") == 0 || strcmp(files->d_name, "..") == 0)
                        continue;
                strcpy(fullpath,path);
                strcat(fullpath,"/");
                strcat(fullpath,files->d_name);
                filesize = getsizeoffile(fullpath);
                if(files->d_type == DT_DIR)
                        filesize = 0;
                else
                {
                        if(checksymbolfileornot(files->d_name))
                        {
                                symbfile = getsymbolfilename(files->d_name);
                                sprintf(symbolfilename,"(%s)",symbfile);
                        }
                }
                if(gbigSEnab)
                {
                        fileperm = getfilepermissions(fullpath);
                        lastaccesstime = getlastaccesstime(fullpath);
                        sprintf(formatstrS,"[%d %s %s]",filesize,fileperm,lastaccesstime);

                }
                if(gsmalltEnb && gsmallFEnab && gsmallsEnab)
                {
                        substr = strstr(files->d_name,gfilestr);

                        if((filesize  <= gfilesize) && (substr !=NULL))
                        {
                                if(gfileselection == 1)
                                {
                                        if(files->d_type == DT_DIR)
                                        {
                                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                        printf("\t");
                                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                        }
                                }
                                else if(gfileselection == 2)
                                {
                                        if(files->d_type != DT_DIR)
                                        {
                                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                        printf("\t");
                                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                        }
                                }
                                
                                if(gsmalleEnb)
                                    execommand(files->d_name);
                                    
                                if(gbigEEnb)
                                    fprintf(Op,"%s\n",files->d_name);
                        }
                }
                else if(gsmallFEnab && gsmallsEnab)
                {
                        substr = strstr(files->d_name,gfilestr);
                        if((files->d_type != DT_DIR) && (filesize  <= gfilesize) && (substr !=NULL))
                        {
                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                        printf("\t");
                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                
                                if(gsmalleEnb)
                                    execommand(files->d_name);
                                    
                                if(gbigEEnb)
                                    fprintf(Op,"%s\n",files->d_name);
                        }
                }
                else if(gsmallFEnab && gsmalltEnb)
                {
                        substr = strstr(files->d_name,gfilestr);
                        if((substr !=NULL))
                        {
                                if(gfileselection == 1)
                                {
                                        if(files->d_type == DT_DIR)
                                        {
                                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                        printf("\t");
                                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                        }
                                }
                                else if(gfileselection == 2)
                                {
                                        if(files->d_type != DT_DIR)
                                        {
                                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                        printf("\t");
                                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                                
                                                if(gsmalleEnb)
                                                    execommand(files->d_name);
                                                    
                                                if(gbigEEnb)
                                                    fprintf(Op,"%s\n",files->d_name);
                                        }
                                }
                        }
                }
                else if(gsmalltEnb && gsmallsEnab)
                {
                        if((filesize  <= gfilesize))
                        {
                                if(gfileselection == 1)
                                {
                                        if(files->d_type == DT_DIR)
                                        {
                                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                        printf("\t");
                                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                        }
                                }
                                else if(gfileselection == 2)
                                {
                                        if(files->d_type != DT_DIR)
                                        {
                                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                        printf("\t");
                                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                                
                                                if(gsmalleEnb)
                                                    execommand(files->d_name);
                                                    
                                                if(gbigEEnb)
                                                    fprintf(Op,"%s\n",files->d_name);
                                        }
                                }
                        }
                }
                else if(gsmallsEnab)
                {
                        if((files->d_type != DT_DIR) && (filesize  <= gfilesize))
                        {
                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                        printf("\t");
                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                
                                if(gsmalleEnb)
                                    execommand(files->d_name);
                                if(gbigEEnb)
                                    fprintf(Op,"%s\n",files->d_name);
                        }
                }
                else if(gsmallFEnab)
                {
                        substr = strstr(files->d_name,gfilestr);
                        if(substr !=NULL)
                        {
                                for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                        printf("\t");
                                printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                
                                if(gsmalleEnb)
                                    execommand(files->d_name);
                                if(gbigEEnb)
                                    fprintf(Op,"%s\n",files->d_name);
                        }
                }
                else if(gsmalltEnb)
                {
                        if(gfileselection == 1)
                        {
                                if(files->d_type == DT_DIR)
                                {
                                        for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                printf("\t");
                                        printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                }
                        }
                        else if(gfileselection == 2)
                        {
                                if(files->d_type != DT_DIR)
                                {
                                        for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                                printf("\t");
                                        printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                                }
                        }
                }
                else
                {
                        for(tabIndlooCnt = 0; tabIndlooCnt < gTabIndCnt; tabIndlooCnt++)
                                printf("\t");
                        printf("%s %s %s\n\n", files->d_name,symbolfilename,formatstrS);
                        
                        if(gsmalleEnb)
                        {
                                   if(files->d_type != DT_DIR) 
                                    execommand(files->d_name);
                        }
                        
                        if(gbigEEnb)
                        {
                                if(files->d_type != DT_DIR)
                                    fprintf(Op,"%s\n",files->d_name);
                        }
                                    
                }

                memset(formatstrS,'\0',sizeof(formatstrS));
                memset(symbolfilename,'\0',sizeof(symbolfilename));

                if(files->d_type == DT_DIR)
                {
                        tempTabIndCnt = gTabIndCnt;
                        gTabIndCnt++;
                        printDirList(fullpath,1);
                        gTabIndCnt = tempTabIndCnt;
                }

        }

        free(fullpath);
        fullpath = NULL;
        closedir(dir);
        return 0;
}
