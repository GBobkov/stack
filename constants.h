#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stddef.h>  
#include "defines.h"

typedef int ELEMENT_TYPE;

const ELEMENT_TYPE POIZON_VALUE = -22072006;
const ELEMENT_TYPE SECRET_KEY = 1111;

struct STACK 
{
    ELEMENT_TYPE left_canary = SECRET_KEY;

    size_t struct_hashsum;
    size_t data_hashsum;

    long int size;
    long int capacity;
    ELEMENT_TYPE *data;
    
    ON_DEBUG(unsigned errors;\
        const char* name;\
        const char* file;\
        const char* func;\
        int line;)
        
    ELEMENT_TYPE right_canary = SECRET_KEY;
};

struct  HOW_IT_WORK
{
    char f;
    double num;
    char s;
};



enum ERROR_FLAG{
    NO_ERROR=0, 
    NEGATIVE_SIZE=1,
    NEGATIVE_CAPACITY=2, 
    SIZE_BIGGER_THAN_CAPACITY=4,
    NULL_STACK_PTR=8,
    NULL_DATA_PTR=16,
    LST_CNR_DEAD=32,
    RST_CNR_DEAD=64
};


#endif