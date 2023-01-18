#include <stdio.h>
#include <stdlib.h>

int smallerThanIndex()
{ 
    int arrSize = 0, arrloop =0, totalCnt =0;
    int *arr = NULL;
    printf("Enter the number of elements for array\n");
    scanf("%d",&arrSize);
    
    arr = (int *)malloc(sizeof(int)* arrSize);
    
    printf("Enter the array numbers\n");
    
    for(arrloop =0 ; arrloop < arrSize ; arrloop++)
    {
        scanf("%d",&arr[arrloop]);
    }
    //printf("\n");

    for(arrloop =0; arrloop < arrSize; arrloop++)
    {
        if((*(arr + arrloop)) < arrloop)
        {
            totalCnt++;
        }
    }
    
    return totalCnt;
}

int main()
{
    int totalCntValue = 0;
    
    totalCntValue = smallerThanIndex();
    
    printf("TOtal count value is %d\n", totalCntValue);  

    return 0;
}
