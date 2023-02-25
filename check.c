#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct listing
{
	int id;
	int host_id;
	int minimum_nights;
	int number_of_reviews;
	int calculated_host_listings_count;
	int availability_365;
	char *hostname;
	char *neighbourhood_group;
	char *neighbourhood;
	char *room_type;
	float latitude;
	float longitude;
	int price;
}Slist;

Slist getfields(char *line);

int compare(const void *PrevVal, const void *NxtVal)
{
	const Slist *orderA = (Slist *)PrevVal;
	const Slist *orderB = (Slist *)NxtVal;

	return ((orderB->price) - (orderA->price));
}

int main()
{
	Slist	*list = NULL;
	char	data[1000];
	char	cpdata[1000];
	int		cnt = 0;
	FILE	*Ipfp = NULL;
	FILE	*Opfp = NULL;


//	Ipfp = fopen("C:/Users/DummuJay/source/repos/ConsoleApplication1/Debug/listings.csv", "r");
	Ipfp = fopen("C:/Users/DummuJay/source/repos/ConsoleApplication1/ConsoleApplication1/listings.csv", "r");

	if (Ipfp == NULL)
	{
		printf("file open failed\n");
		return 0;
	}

	fgets(data, 1000, Ipfp); // dummu read to escape header 
	strcpy(cpdata, data);

	while (fgets(data, 1000, Ipfp) != NULL)
		cnt++;

	printf("Count value :%d\n", cnt);

	list = (Slist*)malloc(sizeof(Slist)*cnt);

	fseek(Ipfp, 0, SEEK_SET);
	cnt = 0;
	fgets(data, 1000, Ipfp); // dummu read to escape header

	while (fgets(data, 1000, Ipfp) != NULL)
	{
		list[cnt] = getfields(data);
		cnt += 1;
	}

	printf("Count value :%d\n", cnt);

	qsort(list, cnt+1, sizeof(Slist), compare);

	Opfp = fopen("sortedlist.csv", "w+");

	if (Opfp == NULL)
	{
		printf("Unable to create a file");
		return 0;
	}

	printf("Count value :%d", cnt);

	fprintf(Opfp, "%s", cpdata);

/*	for (int loop = 0; loop < cnt; loop++)
	{
		printf("%d,%d,%s,%s,%s,%f,%f,%s,%d,%d,%d,%d,%d\n", list[loop].id, list[loop].host_id,
			list[loop].hostname, list[loop].neighbourhood_group, list[loop].neighbourhood, list[loop].latitude,
			list[loop].longitude, list[loop].room_type, list[loop].price, list[loop].minimum_nights, list[loop].number_of_reviews,
			list[loop].calculated_host_listings_count, list[loop].availability_365);
	}*/

	for (int loop = 0; loop < cnt; loop++)
	{
		fprintf(Opfp, "%d,%d,%s,%s,%s,%f,%f,%s,%d,%d,%d,%d,%d\n", list[loop].id, list[loop].host_id,
			list[loop].hostname, list[loop].neighbourhood_group, list[loop].neighbourhood, list[loop].latitude,
			list[loop].longitude, list[loop].room_type, list[loop].price, list[loop].minimum_nights, list[loop].number_of_reviews,
			list[loop].calculated_host_listings_count, list[loop].availability_365);
	}

	free(list);
	list = NULL;
	fclose(Ipfp);
	Ipfp = NULL;
	fclose(Opfp);
	Opfp = NULL;
}

Slist getfields(char *line)
{
	Slist item;

	item.id = atoi(strtok(line, ","));
	item.host_id = atoi(strtok(NULL, ","));
	item.hostname = strdup(strtok(NULL, ","));
	item.neighbourhood_group = strdup(strtok(NULL, ","));
	item.neighbourhood = strdup(strtok(NULL, ","));
	item.latitude = atof(strtok(NULL, ","));
	item.longitude = atof(strtok(NULL, ","));
	item.room_type = strdup(strtok(NULL, ","));
	item.price = atoi(strtok(NULL, ","));
	item.minimum_nights = atoi(strtok(NULL, ","));
	item.number_of_reviews = atoi(strtok(NULL, ","));
	item.calculated_host_listings_count = atoi(strtok(NULL, ","));
	item.availability_365 = atoi(strtok(NULL, ","));

	return item;
}
