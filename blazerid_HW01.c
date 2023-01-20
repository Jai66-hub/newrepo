#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


bool UABNumber(int n);
float *arrayDetails();
void intro332532(int n);
bool checkprimeornot(int n);
int reverseNum(int n3);
int smallerThanIndex();

int main()
{


    int  Value =0;
    float *OutputArrray = NULL;
    int PosNum = 0;
    int  reverseNumber = 0;
    int totalCntValue = 0;

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

    OutputArrray = arrayDetails();

    for(int i=0; i < 6; i++)
    {
      printf("%f ", OutputArrray[i]);
    }

    // intro332532  program
    printf("\n\nEnter a positive integer value for intro332532 program\n");
    scanf("%d", &PosNum);

    intro332532(PosNum);

    Value =0;

    // reverseNum program

    printf("\n\nPlease Enter Positive number for reverseNum program\n") ;
    scanf("%d", &Value);

    reverseNumber = reverseNum(Value);

    if(reverseNumber)
    {
        printf("Reversed Number is :%d\n",reverseNumber);
    }

    // smallerThanIndex program

    totalCntValue = smallerThanIndex();

    printf("TOtal count value is %d\n", totalCntValue);


    return 0;
}

bool UABNumber(int n)
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
        return true;
    }
    else
    {
        return false;
    }

}

float *arrayDetails()
{
    int *Inputarr = NULL;//[]= {-8, -23 , 18 , 103 , 0 , 1 , -4  , 631, 3 , -41 , 5 };
    float *OutArray = NULL;
    int arrSize = 0, arrloop =0 ,minVal =0 , maxVal =0 , minIndex =0, maxIndex =0;
    int sumofArrNumbers = 0 ;
    float meanValue = 0;

    printf("\n\nEnter the number of elements for array for arrayDetails program\n");
    scanf("%d",&arrSize);

    Inputarr = (int *)malloc(sizeof(Inputarr)* arrSize);

    printf("Enter the array numbers\n");

    for(arrloop =0 ; arrloop < arrSize ; arrloop++)
    {
        scanf("%d",&Inputarr[arrloop]);
    }

    OutArray = (float *)malloc(6);

    minVal = Inputarr[0];
    maxVal = Inputarr[0];

    for(int  loop =1 ; loop < arrSize; loop++)
    {
        if(Inputarr[loop] > maxVal)
        {
            maxVal = Inputarr[loop];
            maxIndex = loop;
        }

        if(Inputarr[loop] < minVal)
        {
            minVal = Inputarr[loop];
            minIndex = loop;
        }
    }

    //finding mean
    for(int meanloop = 0; meanloop < arrSize; meanloop++)
    {
      sumofArrNumbers += Inputarr[meanloop];
    }

    meanValue = sumofArrNumbers / (float)arrSize;

    OutArray[0] = arrSize;
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

int smallerThanIndex()
{
    int arrSize = 0, arrloop =0, totalCnt =0;
    int *arr = NULL;
    printf("\n\nEnter the number of elements for array for smallerThanIndex program\n");
    scanf("%d",&arrSize);

    arr = (int *)malloc(sizeof(int)* arrSize);

    printf("Enter the array numbers\n");

    for(arrloop =0 ; arrloop < arrSize ; arrloop++)
    {
        scanf("%d",&arr[arrloop]);
    }

    for(arrloop =0; arrloop < arrSize; arrloop++)
    {
        if((*(arr + arrloop)) < arrloop)
        {
            totalCnt++;
        }
    }

    return totalCnt;
}

  
  
  
