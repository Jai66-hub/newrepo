#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


int UABNumber(int n);
float *arrayDetails(int *arr,int size);
void intro332532(int n);
bool checkprimeornot(int n);
int reverseNum(int n3);
int smallerThanIndex(int *numbers,int size);

int main()
{


    int  Value =0;
    float *OutputArrray = NULL;
    int PosNum = 0;
    int  reverseNumber = 0;
    int totalCntValue = 0;
    int arrSize = 0;
    int *Inputarr = 0;
    int arrloop =0;

    // UABNumber program

    printf("\nPlease Enter any number for UABNUmber program\n") ;
    scanf("%d", &Value);

    if(UABNumber(Value))
    {
        printf("\n%d is a UABNumber", Value);
    }
    else
    {
        printf("\n%d is not UABNumber", Value);
    }

    // arrayDetails  program

    printf("\n\nEnter the size of array for arrayDetails program\n");
    scanf("%d",&arrSize);

    Inputarr = (int *)malloc(sizeof(Inputarr)* arrSize);

    printf("Enter the array data elements with space\n");

    for(arrloop =0 ; arrloop < arrSize ; arrloop++)
    {
        scanf("%d",&Inputarr[arrloop]);
    }

    OutputArrray = arrayDetails(Inputarr,arrSize);

    for(int i=0; i < 6; i++)
    {
      printf("%f ", OutputArrray[i]);
    }

    // intro332532  program
    printf("\n\nEnter a positive integer value for intro332532 program\n");
    scanf("%d", &PosNum);

    intro332532(PosNum);


    // reverseNum program
    Value =0;

    printf("\n\nPlease Enter Positive number for reverseNum program\n") ;
    scanf("%d", &Value);

    reverseNumber = reverseNum(Value);

    if(reverseNumber)
    {
        printf("Reversed Number is :%d\n",reverseNumber);
    }

    // smallerThanIndex program
    arrSize = 0;
    Inputarr = NULL;

    printf("\n\nEnter the size of array for smallerThanIndex program\n");
    scanf("%d",&arrSize);

    Inputarr = (int *)malloc(sizeof(int)* arrSize);

    printf("Enter the array numbers with space\n");

    for(arrloop =0 ; arrloop < arrSize ; arrloop++)
    {
        scanf("%d",&Inputarr[arrloop]);
    }

    totalCntValue = smallerThanIndex(Inputarr,arrSize);

    printf("TOtal count value is %d\n", totalCntValue);


    return 0;
}

int UABNumber(int n)
{
    int LoopCnt =0, n2 =0 ,Sum =0;

    if(n <= 0)
    {
        printf("Please provide Valid Input\n");
        return false;
    }

    n2 = n;

    for(LoopCnt = 1; LoopCnt < n2 ; LoopCnt++)
    {
        if(n2 % LoopCnt == 0)
        Sum = Sum + LoopCnt ;
    }

    if (Sum == n2)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

float *arrayDetails(int *arr,int size)
{
    float       *OutArray = NULL;
    int         minVal =0 , maxVal =0 , minIndex =0, maxIndex =0;
    int         sumofArrNumbers = 0 ;
    float       meanValue = 0;


    OutArray = (float *)malloc(6);

    minVal = arr[0];
    maxVal = arr[0];

    for(int  loop =1 ; loop < size; loop++)
    {
        if(arr[loop] > maxVal)
        {
            maxVal = arr[loop];
            maxIndex = loop;
        }

        if(arr[loop] < minVal)
        {
            minVal = arr[loop];
            minIndex = loop;
        }
    }

    //finding mean
    for(int meanloop = 0; meanloop < size; meanloop++)
    {
      sumofArrNumbers += arr[meanloop];
    }
    meanValue = sumofArrNumbers / (float)size;

    OutArray[0] = size;
    OutArray[1] = minVal;
    OutArray[2] = minIndex;
    OutArray[3] = meanValue;
    OutArray[4] = maxVal;
    OutArray[5] = maxIndex;

    return OutArray;
}

void intro332532(int n)
{

    if((n <= 0))
    {
        printf("Please provide Valid input\n");
        return;
    }

    if((n % 5 ==0) && (n % 3 == 0))
    {
        printf("UAB CS 332&532\n");
        return;
    }
    else if(n % 5 == 0)
    {
        printf("UAB\n");
        return;
    }
    else if(n % 3 == 0)
    {
        printf("CS\n");
        return;
    }

    if(checkprimeornot(n))
    {
        printf("GO Blazers\n");
    }
    else
    {
        printf("Value is :%d\n", (n*n*n));
    }

    return;
}

bool checkprimeornot(int n)
{
    int LoopCnt;
    int IsPrime = 1;

    if(n == 1)
        return false;

   for(LoopCnt = 2; LoopCnt < n; LoopCnt++)
   {
      if((n % LoopCnt) == 0)
      {
         IsPrime = 0;
      }
   }

   if (IsPrime == 1)
      return true;
   else
      return false;
}

int reverseNum(int n3)
{

    int inputNumb, revOrderNum = 0;

    if(n3 <= 0)
    {
        printf("Please provide Valid Input\n");
        return 0;
    }

    inputNumb = n3;

    while (inputNumb != 0)
    {
        revOrderNum = revOrderNum * 10;
        revOrderNum = revOrderNum + inputNumb % 10;
        inputNumb = inputNumb / 10;
    }

    return revOrderNum;
}

int smallerThanIndex(int *numbers,int size)
{
    int arrloop =0, totalCnt =0;

    for(arrloop =0; arrloop < size; arrloop++)
    {
        if((*(numbers + arrloop)) < arrloop)
        {
            totalCnt++;
        }
    }

    return totalCnt;
}
