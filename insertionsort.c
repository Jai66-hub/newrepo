#include <stdio.h>
#include <stdlib.h>

int insertionsort();

int main()
{
        insertionsort();
        return 0;
}

int insertionsort()
{

        int *arr = NULL;
        int N =0, loop =0;
        int NextElemt =0, prevelmnt = 0;

        printf("Enter the size of the array\n");
        scanf("%d",&N);

        arr = (int *)malloc(sizeof(int) * N);

        printf("Enter the array elements\n");

        for(loop =0; loop < N; loop++)
        {
                scanf("%d",&arr[loop]);
        }

        printf("Unsorted array\n");

        for(loop =0; loop < N; loop++)
        {
                printf("%d ",arr[loop]);
        }
        printf("\n");
        for (loop = 1; loop < N; loop++)
        {
                NextElemt = arr[loop];
                prevelmnt = loop - 1;

                for(prevelmnt = loop -1; (NextElemt < arr[prevelmnt] && prevelmnt >=0) ; prevelmnt--)
                {
                        arr[prevelmnt + 1] = arr[prevelmnt];
                }
                arr[prevelmnt+1] = NextElemt;
        }

        printf("Sorted array\n");

        for(loop =0; loop < N; loop++)
        {
                printf("%d ",arr[loop]);
        }
        printf("\n");

        return 0;
}
