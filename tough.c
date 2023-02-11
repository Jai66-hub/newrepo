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
int checkDirorNot(char *path);
int getsizeoffile(char *filename);
char* getfilepermissions(char *filepath);
char *getlastaccesstime(char *filepath);

// global variables

char    gstr[50];
int     gdepth          = 0;
int     gfilesize       = 0;
bool    gsmallsEnab             = false;
bool    gbigSEnab                = false;
bool    gsmallFEnab             = false;

int main(int argc,char **argv)
{


        int     option                  = 0;
        int     fileIndex               = 0;
        int     argIndex                = 0;
        int     Val                     = 0;
        int     depth                   = 0;
        bool    fileNameprovided        = false;
        bool    smallsEnab              = false;
        bool    bigSEnab                = false;
        bool    isFirstParam            = false;
        int     loop                    = 1;
        char    str[50];



        while((option = getopt(argc, argv, ":Ssf")) != -1)
        {

                switch(option)
                {
                        case 'S':
                                gbigSEnab = true;
                                break;
                        case 's':
                                if(loop == 1)
                                        gfilesize = atoi(argv[loop+1]);
                                else if(loop == 2)
                                        gfilesize = atoi(argv[loop+3]);
                                else if(loop == 3)
                                        gfilesize = atoi(argv[loop+3]);

                                gsmallsEnab = true;
                                break;
                        case 'f':
                                if(loop == 1)
                                {
                                        strcpy(gstr,argv[loop+1]);
                                        gdepth = atoi(argv[loop+2]);
                                }
                                else if(loop == 2)
                                {
                                        strcpy(gstr,argv[loop+2]);
                                        gdepth = atoi(argv[loop+3]);
                                }
                                else
                                {
                                        strcpy(gstr,argv[loop+2]);
                                        gdepth = atoi(argv[loop+3]);
                                }

                                gsmallFEnab = true;
                                break;
                }
                loop++;

        }

        while(optind < argc)
                optind++;

        optind -= 1;

        printDirList(argv[optind],0);

        return 0;
}


int checkDirorNot(char *filename)
{
        int size = 0;
        struct stat checkfordir;

        stat(filename, &checkfordir);

        return S_ISREG(checkfordir.st_mode);
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

        strftime(lastacctime, 32, "%c", localtime(&st.st_atime));

        return lastacctime;
}

int printDirList(char *path,int optionSel)
{

        struct dirent *files;
        DIR *dir = NULL;

        char *fullpath = NULL;
        int pathlen = 0;
        char formatstrs[50];
        char formatstrS[256];
        char formatstrf[256];
        char fullinfo[500];
        int filesize = 0;
        int retVal =0;
        char *fileperm = NULL;
        char *lastaccesstime =NULL;

        if(path == NULL)
                strcpy(path,".");

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

                if(gbigSEnab)
                {
                        fileperm = getfilepermissions(fullpath);
                        lastaccesstime = getlastaccesstime(fullpath);
                        sprintf(formatstrS,"[%d %s %s]",filesize,fileperm,lastaccesstime);

                }

                if(gsmallFEnab)
                {

                }
                if(gsmallsEnab)
                {
                        filesize = getsizeoffile(fullpath);
                        if((files->d_type != DT_DIR) && (filesize  <= gfilesize))
                        {
                                printf("\t%s   %s\n", files->d_name,formatstrS);
                        }
                }
                else
                {
                        printf("\t%s   %s\n", files->d_name,formatstrS);
                }

                printDirList(fullpath,1);

        }

        free(fullpath);
        fullpath = NULL;
        closedir(dir);
        return 0;
}
