#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int printDirList(char *path,int optionSel);
int getsizeoffile(char *filename);
char* getfilepermissions(char *filepath);
char *getlastaccesstime(char *filepath);
bool checksymbolfileornot(char *filename);
char *getsymbolfilename(char *filename);
// global variables

char    gfilestr[20];
int     gdepth                  = 0;
int     gfilesize               = 0;
bool    gsmallsEnab             = false;
bool    gbigSEnab               = false;
bool    gsmallFEnab             = false;
bool    gsmalltEnb              = false;
char    gstrtoption[10];
int     gfileselection          = 0; // 1 - dir , 2 - regular files
int     gTabIndCnt              = 0;

int main(int argc,char **argv)
{

        int     option                  = 0;
        char    strtoption[10];
        int     (*printDirFuncPtr)(char *,int);

        while((option = getopt(argc, argv, "Ss:t:f:")) != -1)
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
                }
        }

        if(optind < argc)
        {
                if(gsmallFEnab)
                {
                        gdepth = atoi(argv[optind]);
                        optind++;
                }
        }

        if(gsmalltEnb)
        {
                if(strcmp(strtoption,"d")==0)
                        gfileselection = 1;
                else
                        gfileselection = 2;
        }

        gTabIndCnt = 1;

        // simple use of function pointer
        printDirFuncPtr = printDirList;

        // calling printDirList funciton over a function pointer
        if(argv[optind] == NULL)
                printDirFuncPtr(".",0);
        else
                printDirFuncPtr(argv[optind],0);


        return 0;
}

int getsizeoffile(char *filename)
{
        int size = 0;
        struct stat checkfordir;

        stat(filename, &checkfordir);

        size = checkfordir.st_size;

        return size;
}

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

char *getlastaccesstime(char *filepath)
{
        struct stat st;
        char *lastacctime = malloc(sizeof(char) * 32);
        strftime(lastacctime, 32, "%d-%m-%Y %H:%M:%S", localtime(&st.st_atime));
        return lastacctime;
}

bool checksymbolfileornot(char *filename)
{
        struct stat st;
        lstat(filename, &st);

        if(S_ISLNK(st.st_mode))
                return true;
        else
                return false;
}

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
