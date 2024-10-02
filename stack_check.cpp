#include "stack_check.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "my_stack.h"


int Check_HashSum(STACK *stack);
int Check_Canary(STACK* stack);

void Fill_Poizon(STACK *stack)
{
    for (int i = stack->size; i < stack->capacity; i++)
        stack->data[i] = POIZON_VALUE;
    
}


unsigned Stack_Error(STACK* stack)
{

    unsigned errors = 0;
    if (!stack) return NULL_STACK_PTR;
    if (stack->size < 0) errors |= NEGATIVE_SIZE;
    if (stack->capacity < 0) errors |= NEGATIVE_CAPACITY;
    if (stack->size > stack->capacity) errors |= SIZE_BIGGER_THAN_CAPACITY;
    if (!stack->data) errors |= NULL_DATA_PTR;

    ON_DEBUG(stack->errors = errors;)
    return errors;


}


void Do_Stack_Assert(STACK *stack, const char* file, const char* func, const int line)
{
    
    if (!stack)
    {
        printf("NULL_STACK_PTR in %s:%d(%s)", file, line, func);
        abort();
    }
    if (Stack_Error(stack))
    {   
        Do_Stack_Dump(stack, file, func, line);
        abort();
    }
    
}






void Do_Stack_Dump(STACK* stack, const char* file, const char* func, const int line)
{
    
    if (!stack)
    {
        printf("Assertion fault:NULL_STACK_PTR in %s:%d(%s)", file, line, func);
        abort();
    }

    printf(OPEN_LINE);
    ON_DEBUG(printf(ANSI_PURPLE "STACK [%p]\n", stack);\
    printf("\tname=\"%s\" initializated at %s:%d(%s)\n", stack->name, stack->file, stack->line, stack->func);\
    printf("\tcalled from %s:%d(%s)" ANSI_RESET_COLOR, file, line, func);\
    printf(ANSI_RED "errors=%d" ANSI_RESET_COLOR, stack->errors);\
    print_errors(stack->errors);)
    
    printf(ANSI_GREEN "capacity=%u\nsize=%u\nleft_canary=%d\nright_canary=%d" ANSI_RESET_COLOR, stack->capacity, stack->size, stack->left_canary, stack->right_canary);
    printf(ANSI_YELLOW "data[%p]:\n", stack->data);
    if (!stack->data)
    {
        printf(ANSI_RED "Can't print data containing: NULL_DATA_PTR" ANSI_RESET_COLOR);
        printf(END_LINE);
        return;
    }
    for (int i = -1; i <= (int)stack->capacity; i++)
    {
        if (0 <= i && i < stack->size)
            printf("*[%d]=%d", i, stack->data[i]);
        else
            printf(" [%d]=%d",i, stack->data[i]);

        if (stack->data[i] == POIZON_VALUE)
            printf("(POIZON)");

        printf("\n");
    }
    if (!stack->capacity) printf(ANSI_RED "Stack is empty." ANSI_RESET_COLOR);
    printf(END_LINE);

}


void print_errors(int problem)
{
    printf(ANSI_RED);
    if (problem == 0)
    {
        printf("NO_ERRORS" ANSI_RESET_COLOR);
        return;
    }
    printf("ERRORS:");
    if ((problem & NEGATIVE_SIZE) == NEGATIVE_SIZE) printf("\n\tNEGATIVE_SIZE");
    if ((problem & NEGATIVE_CAPACITY) == NEGATIVE_CAPACITY) printf("\n\tNEGATIVE_CAPACITY");
    if ((problem & SIZE_BIGGER_THAN_CAPACITY) == SIZE_BIGGER_THAN_CAPACITY) printf("\n\tSIZE_BIGGER_THAN_CAPACITY");
    if ((problem & NULL_STACK_PTR) == NULL_STACK_PTR) printf("\n\tNULL_STACK_PTR");
    if ((problem & NULL_DATA_PTR) == NULL_DATA_PTR) printf("\n\tNULL_DATA_PTR");
    printf(ANSI_RESET_COLOR);

}


int Check_Canary(STACK* stack)
{
    int flag = 0;
    printf(ANSI_RED);
    if (stack->left_canary != SECRET_KEY)
    {
        flag = 1;
        printf("LEFT_STRUCT CANARY IS DEAD.");
    }
        

    if (stack->right_canary != SECRET_KEY)
        {
            flag = 1;
            printf("LEFT_STRUCT CANARY IS DEAD.");
        }

    if (stack->data[-1] != SECRET_KEY)
        {
            flag = 1;
            printf("LEFT_DATA CANARY IS DEAD.");
        }

    if (stack->data[stack->capacity] != SECRET_KEY)
        {
            flag = 1;
            printf("RIGHT_DATA CANARY IS DEAD.");
        }
   
    return flag;
}



void Check_Damage(STACK* stack, const char* file, const char* func, const int line)
{
    int flag = Check_Canary(stack);
    flag *= Check_HashSum(stack);
}

int Check_HashSum(STACK *stack)
{
    return 0;
}