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

Slist	getfields(char *line);
int		sortPrice(const void *PrevVal, const void *NxtVal);
int		sortHostname(const void *PrevVal, const void *NxtVal);
void	sortByPrice(Slist *list, int listCnt);
void	sortByHostName(Slist *list, int listCnt);
void	SortandWritedatatoFile(Slist *list, char *header, int listcnt, int SortOption /* 1-price sort, 2 - hostanme sort*/);


int main()
{
	Slist	*list = NULL;
	char	data[1000];
	char	cpdata[1000];
	int		cnt = 0;
	FILE	*Ipfp = NULL;
	int		dataCnt = 0;

	Ipfp = fopen("listings.csv", "r");

	if (Ipfp == NULL)
	{
		printf("file open failed\n");
		return 0;
	}

	fgets(data, 1000, Ipfp); // dummu read to escape header 
	strcpy(cpdata, data);

	while (fgets(data, 1000, Ipfp) != NULL)
		cnt++;

	list = (Slist*)malloc(sizeof(Slist)*cnt);

	dataCnt = cnt;

	fseek(Ipfp, 0, SEEK_SET);
	cnt = 0;
	fgets(data, 1000, Ipfp); // dummu read to escape header

	while(fgets(data, 1000, Ipfp) != NULL)
	{
		list[cnt] = getfields(data);
		cnt += 1;
	}

	//sort by price 
	SortandWritedatatoFile(list, cpdata, dataCnt, 1 /* 1-price sort, 2 - hostanme sort*/);

	// sort by hostname
	SortandWritedatatoFile(list, cpdata, dataCnt, 2 /* 1-price sort, 2 - hostanme sort*/);

	free(list);
	list = NULL;
	fclose(Ipfp);
	Ipfp = NULL;

	return 0;
}

void SortandWritedatatoFile(Slist *list,char *header,int listcnt,int SortOption /* 1-price sort, 2 - hostanme sort*/)
{
	FILE *Opfp = NULL;

	if(SortOption ==1)
	{
		sortByPrice(list, listcnt); // sort by price
		Opfp = fopen("priceSortedlist.csv", "w+");
	}
	else
	{
		sortByHostName(list, listcnt); // sort by hostanme
		Opfp = fopen("hostNameSortedlist.csv", "w+");
	}

	if (Opfp == NULL)
	{
		printf("Unable to create a file");
		return;
	}

	fprintf(Opfp, "%s", header);

	for (int loop = 0; loop < listcnt; loop++)
	{
		fprintf(Opfp, "%d,%d,%s,%s,%s,%f,%f,%s,%d,%d,%d,%d,%d\n", list[loop].id, list[loop].host_id,
			list[loop].hostname, list[loop].neighbourhood_group, list[loop].neighbourhood, list[loop].latitude,
			list[loop].longitude, list[loop].room_type, list[loop].price, list[loop].minimum_nights, list[loop].number_of_reviews,
			list[loop].calculated_host_listings_count, list[loop].availability_365);
	}

	fclose(Opfp);
	Opfp = NULL;

	return;
}

void sortByPrice(Slist *list, int listCnt)
{
	qsort(list, listCnt, sizeof(Slist), sortPrice);
}

int sortPrice(const void *PrevVal, const void *NxtVal)
{
	const Slist *list1 = (Slist *)PrevVal;
	const Slist *list2 = (Slist *)NxtVal;
	return ((list2->price) - (list1->price));
}

void sortByHostName(Slist *list, int listCnt)
{
	qsort(list, listCnt, sizeof(Slist), sortHostname);
}

int sortHostname(const void *PrevHoststr, const void *NextHostStr)
{
	const Slist *list1 = (Slist *)PrevHoststr;
	const Slist *list2 = (Slist *)NextHostStr;
	return strcmp(list1->hostname, list2->hostname);
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
