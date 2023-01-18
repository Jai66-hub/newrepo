#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float *arrayDetails()
{  
    int  Inputarr[]= {-8, -23 , 18 , 103 , 0 , 1 , -4  , 631, 3 , -41 , 5 };
    float *OutArray = NULL;  
    int arrSize = 0, minVal =0 , maxVal =0 , minIndex =0, maxIndex =0;
    int sumofArrNumbers = 0 ;
    float meanValue = 0;
    
    arrSize = ((sizeof(Inputarr)/sizeof(Inputarr[0])));
    
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

int main()
{
    float *OutputArrray = NULL;
    
    OutputArrray = arrayDetails();
    
    for(int i=0; i < 6; i++)  
    {  
      printf("%f ", OutputArrray[i]);  
    }

    return 0;
}
