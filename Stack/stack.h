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
typedef int Elem; //пока что

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
    RESIZE_ERROR =  6, 
    DTOR_ERROR   =  7,
    CTOR_ERROR   =  8, 
    CANARY_STK   =  9,
    CANARY_DATA  = 10,
    HASH         = 11,
};

//!Stack structure
struct Stack
{
    #ifdef CANARY_PROTECTION
    canary_t canary1;
    canary_t *canary1_data;
    #endif //CANARY_PROTECTION

    Elem* data;
    size_t size;
    size_t capacity;

    #ifdef HASH_PROTECTION
    unsigned long long HashSum;
    #endif //HASH_PROTECTION

    #ifdef CANARY_PROTECTION
    canary_t canary2;
    canary_t *canary2_data;
    #endif //CANARY_PROTECTION
};

//---------------------------------------------------------------------
//! Stack constructor with specified capacity
//! @param [out]  stk  stack pointer 
//! @param [in]  cap  start capacity of the stack
//! 
//! @return Error code
//---------------------------------------------------------------------
int StackCtor(Stack* stk, size_t cap);

//---------------------------------------------------------------------
//! Stack destructor, frees memory
//! @param [out] stk  stack pointer 
//!
//! @return Error code
//---------------------------------------------------------------------
int StackDtor(Stack* stk);

//---------------------------------------------------------------------
//! Function for pushing an element into the stack
//! @param [out] stk   stack pointer 
//! @param [in]  value element to push
//! 
//! @return Error code
//---------------------------------------------------------------------
int StackPush(Stack* stk, Elem value);

//---------------------------------------------------------------------
//! Function for deleting an element from the end of the stack
//! @param [out] stk   stack pointer 
//! 
//! @return Error code
//---------------------------------------------------------------------
int StackPop(Stack* stk);

//---------------------------------------------------------------------
//! Function for resizing the stack - changes its capacity through memory reallocation
//! @param [out] stk     stack pointer 
//! @param [in]  new_cap new capacity of the stack
//!
//! @return Error code
//---------------------------------------------------------------------
int StackResize(Stack* stk, const size_t new_cap);

//---------------------------------------------------------------------
//! Dump function - prints all information about current stack condition
//! @param [out] stk     stack pointer 
//! @param [out] output  file to write to
//! @param [in]  error   error code
//---------------------------------------------------------------------
void StackDump(Stack* stk, int error, FILE* output);

//---------------------------------------------------------------------
//! Function for fillig the whole stack with one value
//! @param [out] stk  stack pointer 
//! @param [in]  elem element to fill stack
//---------------------------------------------------------------------
void StackFillPoison(Stack* stk, size_t elem);

//---------------------------------------------------------------------
//! Function for processing errors
//! @param [out] stk  stack pointer 
//---------------------------------------------------------------------
void ErrorsProcessing(Stack* stk);

//---------------------------------------------------------------------
//! Function for checking current stack condition
//! @param [out] stk       stack pointer
//! @param [in]  condition condition to check
//! @param [in]  error     error code
//! @param [in]  file      file where the error has occured
//! @param [in]  line      line where the error has occured
//! @param [in]  function  function where the error has occured
//!
//! @return Error code
//---------------------------------------------------------------------
int StackCheck(bool condition, Stack *stk, int error, const char *file, const int line, const char *function);

//---------------------------------------------------------------------
//! Function for calculating stack hash using ROR function
//! @param [out] stk     stack pointer
//!
//! @return Stack hash
//---------------------------------------------------------------------
unsigned long long Hash (Stack* stk);
unsigned long long ROR (unsigned long long elem);

//Function for testing 
void TestProcessing();

#endif