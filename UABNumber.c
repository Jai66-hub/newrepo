#include <stdio.h>
#include <stdbool.h>

bool UABNumber(int n);

int main()
{
    int  Value =0;
   
    printf("Please Enter any number\n") ;   
    scanf("%d", &Value);
    
    if(UABNumber(Value))
    {
        printf("\n%d is a UABNumber", Value);   
    }
    else
    {
        printf("\n%d is not UABNumber", Value);
    }
    
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
