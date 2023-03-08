#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{

	pid_t	ChildPid;
	int	ChildStatus = 0;
	char	data[250] = { 0 };
	char	command[250] = { 0 };
	FILE	*Ipfp = NULL;
	FILE	*OPfp = NULL;
	time_t	beginTime, endTime;
	char	argumnets[10][250] = { 0 };
	char	*args = NULL;
	int	argcnt = 0;

	Ipfp = fopen(argv[1], "r");

	if (Ipfp == NULL)
	{
		printf("file open failed\n");
		return 0;
	}

	OPfp = fopen("output.log", "w+");

	if (OPfp == NULL)
	{
		printf("Unable to create a log file\n");
		fclose(Ipfp);
		Ipfp = NULL;
		return 0;
	}

	while (fgets(data, 250, Ipfp) != NULL)
	{
		strcpy(command, data);
		argcnt = 0;
		memset(argumnets, 0, sizeof argumnets);
		args = strtok(command, " ");
		strcpy(argumnets[argcnt], args);
		while (args != NULL)
		{
			args = strtok(NULL, " ");
			argcnt++;
			if(args != NULL)
				strcpy(argumnets[argcnt], args);
		}

		beginTime = time(NULL);
		ChildPid = fork();

		if (ChildPid == 0)
		{
			printf("this is child\n");
			execvp(argumnets[0], argumnets);
			exit(0);
		}
		else if (ChildPid > 0)
		{
			printf("this is parent\n");
			waitpid(ChildPid, &ChildStatus);
			endTime = time(NULL);
			if (WIFEXITED(ChildStatus))
			{
				printf("child exited normally");
			}

			ChildStatus = 0;

			fprintf(OPfp, "%s\t%s\t%s\n", command, ctime(&beginTime), ctime(&endTime));
		}
		else
		{
			perror("fork");
			fclose(Ipfp);
			Ipfp = NULL;
			fclose(OPfp);
			OPfp = NULL;
			exit(0);
		}
	}

	fclose(Ipfp);
	Ipfp = NULL;
	fclose(OPfp);
	OPfp = NULL;

	return 0;
}
