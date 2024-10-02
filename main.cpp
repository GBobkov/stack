#include <stdio.h>
#include "stk.h"
#include <stdlib.h>


int main()
{
    
    STACK stk = {};


    for (int i = 1; i < 3; i++)
    {
        
        Stack_Dump(stk);
        Stack_Pop(&stk);
        
    }

    Stack_Dump(stk);
    


    return 0;
}