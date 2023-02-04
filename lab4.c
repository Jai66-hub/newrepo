#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


int main(int Noofarg, char **argvalue)
{
        int ret = 0, noofbytes =0;
        char readbuff[256];
        FILE *firstfile = NULL , *secondfile = NULL;

        if(Noofarg < 3)
        {
                printf("\nplease provide 2 file input names\n");
                return -1;
        }

        ret = strcmp(argvalue[1],argvalue[2]);

        if(ret == 0)
        {
                printf("\nBoth the input file names are same, please provide different file names\n");
                return -1;
        }

        firstfile =  fopen(argvalue[1],"r+");

        if(firstfile == NULL)
        {
                printf("\nfirst file open error,provide proper file name with full path\n");
                return -1;
        }

        secondfile = fopen(argvalue[2],"r");

        if((secondfile == NULL))
        {
                printf("\nsecond file open error,provide proper file name with full path\n");
                fclose(firstfile);
                return -1;
        }

        fseek(firstfile,0,SEEK_END);

        while ((noofbytes = fread(readbuff, 1, 256, secondfile)) != 0)
        {

                fwrite(readbuff,1,noofbytes,firstfile);
        }

        fclose(firstfile);
        fclose(secondfile);

        return 0;
}
