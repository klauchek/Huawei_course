#ifndef _STACK_H_
#define _STACK_H_

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef double Elem; //пока что
typedef unsigned long long canary_t; 
//typedef unsigned long long hash_t;

const Elem POISON_VALUE = 666;


const canary_t CANARY_VALUE1 = 0xBABABEDA;
const canary_t CANARY_VALUE2 = 0xBADADEDA;


struct Stack
{
    canary_t canary1;
    canary_t *canary1_data;

    Elem* data;
    size_t size;
    size_t capacity;

    canary_t canary2;
    canary_t *canary2_data;
};

void StackCtor(Stack* stk, size_t capacity);
void StackDtor(Stack* stk);
void StackPush(Stack* stk, Elem value);
Elem StackPop(Stack* stk);
void StackResize(Stack* stk, const size_t new_cap);
void StackDump(Stack* stk);



#endif