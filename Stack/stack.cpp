#include "stack.h"

 

void StackCtor(Stack* stk, size_t capacity)
{
    assert(stk);

    stk->canary1 = CANARY_VALUE1;
    stk->canary1_data = (canary_t*)(stk->data);


    stk->data = (Elem*)calloc(capacity * sizeof(Elem) + 2*sizeof(canary_t), sizeof(char));
    stk->capacity = capacity;
    stk->size = 0;

    
    stk->canary2 = CANARY_VALUE2;
    stk->canary2_data = (canary_t*)(stk->data + sizeof(canary_t) + stk->capacity * sizeof(Elem));
};

void StackDtor(Stack* stk)
{
    assert(stk);
    free(stk->data);
    stk->data = NULL;
    stk->size = -1;
};

void StackPush(Stack* stk, Elem value)
{
    assert(stk);

    if(stk->size == stk->capacity)
        StackResize(stk, 2 * stk->capacity);
        //errors?

    ((Elem*)(stk->data + sizeof(canary_t)))[stk->size] = value;
    ++stk->size;
};

Elem StackPop(Stack* stk)
{
    assert(stk);

    Elem last = ((Elem*)(stk->data + sizeof(canary_t)))[stk->size];
    ((Elem*)(stk->data + sizeof(canary_t)))[stk->size] = POISON_VALUE;
    --stk->size;

    return last;
};

void StackResize(Stack* stk, const size_t new_cap)
{
    assert(stk);

    if(new_cap < stk->size)
    {
        //error
    }


    Elem* new_data = (Elem*)realloc(stk->data, new_cap * sizeof(Elem) + 2 * sizeof(canary_t));

    assert(new_data);

    stk->data = new_data;
    stk->capacity = new_cap;

    stk->canary2_data = (canary_t*)(stk->data + stk->capacity * sizeof(Elem) + 2 * sizeof(canary_t));
	*(stk->canary2_data) = CANARY_VALUE2;
};