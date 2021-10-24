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

#define Data ((Elem*)(stk->data + sizeof(canary_t)))

const char FILENAME[] = "output.txt";

typedef double Elem; //пока что

#ifdef CANARY_PROTECTION
typedef unsigned long long canary_t;
const canary_t CANARY_VALUE1 = 0xBABABEDA;
const canary_t CANARY_VALUE2 = 0xBADADEDA;
const canary_t CANARY_DATA1 = 0xDEDABADA;
const canary_t CANARY_DATA2 = 0xDEADBEBA;
#endif //CANARY_PROTECTION

const Elem POISON_VALUE = 666;

enum Errors
{
    STACK_OK     =  0, //All was ok
    NOT_A_STACK  =  1, //If struct wasn't stack
    MEMORY_ERROR =  2, //Not enough memory or another memerror
    OVERFLOW     =  3, //Size > capacity or needed size error
    UNDERFLOW    =  4, //Size <= 0
    POP_ERROR    =  5, //Something went wrong in Pop func
    PUSH_ERROR   =  6, //Something went wrong in Push func
    RESIZE_ERROR =  7, //Something went wrong in Resize func
    DTOR_ERROR   =  8, //If dtor was called twice or another dtor error
    CTOR_ERROR   =  9, //If ctor was called twice or another ctor error
    CANARY_STK   = 10, //If one of stack canaries have been changed
    CANARY_DATA  = 11, //If one of data canaries have been changed
    HASH_DATA    = 12, //If data hash has been changed without reason
    HASH_STK     = 13  //If stack hash has been changed without reason
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
void StackDump(Stack* stk);
int StackOK(const Stack* stk); //обработка всевозможных ошибок
void StackFillPoison(Stack* stk, int elem);

void ErrorsProcessing(Stack* stk, int cur_line, int error);

//error verification - стопка сообщений
//dump - их вывод в файл


#endif