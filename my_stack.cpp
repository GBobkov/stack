#include "my_stack.h"
#include "colors.h"
#include "stack_check.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


const size_t ELEMENTARY_CAPACITY = 4;
const int MEMORY_INCREASE_COEFFICIENT=2;
const int MEMORY_DECREASE_COEFFICIENT=2;
static const int PUSH_ELEMENT_MODE= 1;
static const int POP_ELEMENT_MODE =2;



unsigned Stack_Realloc_Increase(STACK* stack);
unsigned Stack_Realloc_Desrease(STACK* stack);





void Do_Stack_Init(STACK *stack, size_t capacity, const char* name, const char* file, const char* func, const int line) 
{  
    if (!stack)
    {
        printf(ANSI_RED "%s:%d(%s) Can't construct stack:%s=NULL" ANSI_RESET_COLOR, name, file, line, func);
        abort();
    }

    
    stack->size = 0;
    stack->capacity=capacity;
    stack->left_canary=SECRET_KEY;
    stack->right_canary=SECRET_KEY;
    stack->data = (ELEMENT_TYPE *)calloc(capacity + 2, sizeof(ELEMENT_TYPE));
    ON_DEBUG(Stack_Error(stack);\
            if (stack->errors != NULL_DATA_PTR && stack->errors != NO_ERROR)\
                {\
                    printf(ANSI_RED "%s:%d(%s) problems with construct. Errors=%d" ANSI_RESET_COLOR, file, line, func, stack->errors);\
                    print_errors(stack->errors);\
                    abort();\
                })


    stack->data[0] = SECRET_KEY;
    stack->data[stack->capacity + 1] = SECRET_KEY;
    stack->data += 1;

    
    Fill_Poizon(stack);
    
    
    ON_DEBUG(
            stack->name=name;\
            stack->file=file;\
            stack->line=line;\
            stack->func=func;)
}


void Do_Stack_Destroy(STACK* stack, const char* name, const char* file, const char* func, const int line)
{
    if(!stack)
    { 
        printf("Can't destroy \"%s\"(=NULL) at %s:%d(%s)", name, file, line, func);
        return;
    }

    stack->capacity = 0;
    stack->size = 0;
    free(stack->data - 1);
    stack->data = NULL;
}



unsigned Stack_Push(STACK* stack, ELEMENT_TYPE new_element)
{
    ON_DEBUG(Stack_Assert(stack);)

    Stack_Realloc_Increase(stack);
    stack->data[stack->size - 1] = new_element;
    
    ON_DEBUG(Stack_Assert(stack);)

    
    return Stack_Error(stack);
}


ELEMENT_TYPE Stack_Pop(STACK* stack)
{
    stack->size -= 1;
    ON_DEBUG(Stack_Assert(stack);)

    ELEMENT_TYPE value_return = stack->data[stack->size];

    Stack_Realloc_Desrease(stack);

    ON_DEBUG(Stack_Assert(stack);)

    
    return value_return;

}


unsigned Stack_Realloc_Increase(STACK* stack) 
{
    ON_DEBUG(Stack_Assert(stack);)

    stack->size += 1;
    if (stack->size > stack->capacity)
        {
            if (stack->capacity)
                stack->capacity *= MEMORY_INCREASE_COEFFICIENT;
            else
                stack->capacity = ELEMENTARY_CAPACITY;
                
            if (stack->data)
                stack->data -= 1;
            stack->data = (ELEMENT_TYPE *) realloc((void *) stack->data, (stack->capacity + 2) * sizeof(ELEMENT_TYPE));

            stack->data[0] = SECRET_KEY;
            stack->data[stack->capacity + 1] = SECRET_KEY;
            stack->data += 1;
        }


    Fill_Poizon(stack);

    ON_DEBUG(Stack_Assert(stack);)


    
    return Stack_Error(stack);

}




unsigned Stack_Realloc_Desrease(STACK* stack)
{
    ON_DEBUG(Stack_Assert(stack);)

    if (stack->size * MEMORY_INCREASE_COEFFICIENT * MEMORY_INCREASE_COEFFICIENT <= stack->capacity)
    {
        stack->capacity /= MEMORY_DECREASE_COEFFICIENT;       
        stack->data = (ELEMENT_TYPE *) realloc((void *) (stack->data - 1), (stack->capacity + 2) * sizeof(ELEMENT_TYPE));

        stack->data[0] = SECRET_KEY;
        stack->data[stack->capacity + 1] = SECRET_KEY;
        stack->data += 1;
    }

    ON_DEBUG(Fill_Poizon(stack);)
    ON_DEBUG(Stack_Assert(stack);)


    
    return Stack_Error(stack);
}