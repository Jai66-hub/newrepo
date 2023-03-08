#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	
	pid_t	pid;
	int		status = 0;
	char	data[1000];
	char	command[1000];
	char	TimestampBefore[250];
	char	TimestampAfter[250];
	FILE	*Ipfp = NULL;
	FILE	*OPfp = NULL;
	time_t	begin, end;

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
		return 0;
	}

	while (fgets(data, 1000, Ipfp) != NULL)
	{
		strcpy(command, data);

		begin = time(NULL);
		pid = fork();

		if (pid == 0)
		{
			printf("this is child\n");
			execlp(command, command, (char *)NULL);
			exit(0);
		}
		else if (pid > 0)
		{
			printf("this is parent\n");
			waitpid(pid,&status);
			end = time(NULL);
			if (WIFEXITED(status))
			{
				printf("child exited normally");
			}
			else {
				printf("child process not terminated normally");
			}
			status = 0;

			fprintf(OPfp,"%s\t%s\t%s\n", command, ctime(&begin), ctime(&end));
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
