#include <stdio.h>
#include <stdbool.h>

int reverseNum(int n3);

int main()
{
    int  Value =0;
    int  reverseNumber = 0;
   
    printf("Please Enter Positive number\n") ;   
    scanf("%d", &Value);
    
    reverseNumber = reverseNum(Value);
    
    if(reverseNumber)
    {
        printf("Reversed Number is :%d\n",reverseNumber);
    }

    return 0;
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
