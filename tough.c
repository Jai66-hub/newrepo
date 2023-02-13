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

char    gfilestr[50];
int     gdepth                  = 0;
int     gfilesize               = 0;
bool    gsmallsEnab             = false;
bool    gbigSEnab               = false;
bool    gsmallFEnab             = false;
bool    gsmalltEnb              = false;
char    gstrtoption[50];

int main(int argc,char **argv)
{

        int     option                  = 0;

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
                                strcpy(gstrtoption,optarg);
                                gsmalltEnb = true;
                                break;
                }
        }


        printf("optiin val :%d\n",optind);
        if(optind < argc)
        {
                if(gsmallFEnab)
                {
                        gdepth = atoi(argv[optind]);
                        optind++;
                }
        }

        printf("optiin val :%d\n",optind);

        if(argv[optind] == NULL)
                printDirList(".",0);
        else
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

        strftime(lastacctime, 32, "%d-%m-%Y %H:%M:%S", localtime(&st.st_atime));
//      strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&attrib.st_mtime));

        return lastacctime;
}

int printDirList(char *path,int optionSel)
{

        struct dirent *files;
        DIR *dir = NULL;

        char *fullpath = NULL;
        int pathlen = 0;
        char formatstrs[50] = {0};
        char formatstrS[256]= {0};
        char formatstrf[256]= {0};
        char fullinfo[500]= {0};
        int filesize = 0;
        int retVal =0;
        char *fileperm = NULL;
        char *lastaccesstime =NULL;
        char *substr = NULL;


//      printf("received path %s\n",path);

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

                if(gsmallFEnab & gsmallsEnab)
                {
                        substr = strstr(files->d_name,gfilestr);
                        if((files->d_type != DT_DIR) && (filesize  <= gfilesize) && (substr !=NULL))
                                 printf("\t%s   \t%s\n", files->d_name,formatstrS);
                }
                else if(gsmallsEnab)
                {
                        if((files->d_type != DT_DIR) && (filesize  <= gfilesize))
                                printf("\t%s   \t%s\n", files->d_name,formatstrS);
                }
                else if(gsmallFEnab)
                {
                        substr = strstr(files->d_name,gfilestr);
                        if(substr !=NULL)
                                printf("\t%s   \t%s\n", files->d_name,formatstrS);
                }
                else
                {
                                printf("\t%s   \t%s\n", files->d_name,formatstrS);
                }

                memset(formatstrS,'\0',sizeof(formatstrS));

                printDirList(fullpath,1);

        }

        free(fullpath);
        fullpath = NULL;
        closedir(dir);
        return 0;
}
                        
