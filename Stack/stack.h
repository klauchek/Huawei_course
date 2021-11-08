#ifndef _STACK_H_
#define _STACK_H_

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

#define DEBUG

#ifdef DEBUG
#define CANARY_PROTECTION
#define HASH_PROTECTION
#endif //DEBUG


#define STK_CHECK(condition, stk, error)                                            \
{                                                                                   \
    if (!condition)                                                                 \
    {                                                                               \
        StackCheck(false, stk, error, __FILE__, __LINE__, __FUNCTION__);            \
        return error;                                                               \
    }                                                                               \
}



#define Data ((Elem*)(stk->data + sizeof(canary_t)))

extern FILE* output;
typedef double Elem; //пока что

#ifdef CANARY_PROTECTION
typedef unsigned long canary_t;
const canary_t CANARY_VALUE1 = 0xBABABEDA;
const canary_t CANARY_VALUE2 = 0xBADADEDA;
const canary_t CANARY_DATA1 = 0xDEDABADA;
const canary_t CANARY_DATA2 = 0xDEADBEBA;
#endif //CANARY_PROTECTION

const Elem POISON_VALUE = 666;

enum Errors
{
    STACK_OK     =  0,
    NOT_A_STACK  =  1,
    MEMORY_ERROR =  2,
    OVERFLOW     =  3,
    UNDERFLOW    =  4,
    POP_ERROR    =  5, 
    PUSH_ERROR   =  6, 
    RESIZE_ERROR =  7, 
    DTOR_ERROR   =  8,
    CTOR_ERROR   =  9, 
    CANARY_STK   = 10,
    CANARY_DATA  = 11,
    HASH_DATA    = 12,
    HASH_STK     = 13
};

struct Stack
{
    #ifdef CANARY_PROTECTION
    canary_t canary1;
    canary_t *canary1_data;
    #endif

    Elem* data;
    size_t size;
    size_t capacity;
//hash

    #ifdef CANARY_PROTECTION
    canary_t canary2;
    canary_t *canary2_data;
    #endif
};

int StackCtor(Stack* stk, size_t cap);
int StackDtor(Stack* stk);
int StackPush(Stack* stk, Elem value);
int StackPop(Stack* stk);
int StackResize(Stack* stk, const size_t new_cap);
void StackDump(Stack* stk, int error, FILE* output);
//int StackOK(const Stack* stk); //обработка всевозможных ошибок
void StackFillPoison(Stack* stk, size_t elem);
void ErrorsProcessing(Stack* stk);
int StackCheck(bool condition, Stack *stk, int error, const char *file, const int line, const char *function);

#endif