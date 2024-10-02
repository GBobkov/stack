#ifndef STACK_ERRORS_H
#define STACK_ERRORS_H

#include "constants.h"


void Check_Damage(STACK* stack, const char* file, const char* func, const int line);

void Do_Stack_Dump(STACK* stack, const char* file, const char* func, const int line);
void Do_Stack_Assert(STACK *stack, const char* file, const char* func,  const int line);
void print_errors(int problem);
void Fill_Poizon(STACK *stack);
unsigned Stack_Error(STACK* stack);

#endif