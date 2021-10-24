#include "stack.h"

//возвращать коды ошибок!!

 FILE* output = fopen(FILENAME, "w");

int StackCtor(Stack* stk, size_t cap)
{
    if (stk->capacity > 0 || !stk)
        return CTOR_ERROR;

    #ifdef CANARY_PROTECTION
    stk->canary1 = CANARY_VALUE1;
    stk->canary2 = CANARY_VALUE2;
    #endif //CANARY_PROTECTION

    stk->data = (Elem*)calloc(cap * sizeof(Elem) + 2 * sizeof(canary_t), sizeof(stk->data[0]));
    if(!stk->data)
        return MEMORY_ERROR;

    stk->capacity = cap;
    stk->size = 0;

    StackFillPoison(stk, 0);

    #ifdef CANARY_PROTECTION
    stk->canary1_data = (canary_t*)(stk->data);
    *(stk->canary1_data) = CANARY_DATA1;
    stk->canary2_data = (canary_t*)(stk->data + sizeof(canary_t) + stk->capacity * sizeof(Elem));
    *(stk->canary2_data) = CANARY_DATA2;
    #endif //CANARY_PROTECTION

    assert(!StackOK(stk));

    return STACK_OK;
};

int StackDtor(Stack* stk)
{
    assert(!StackOK(stk));

    free(stk->data);
    stk->data = NULL;
    stk->size = -1;
    stk->capacity = -1;

    return STACK_OK;
};

int StackPush(Stack* stk, Elem value)
{
    assert(!StackOK(stk));

    if((stk->size + 1) >= stk->capacity)
        if(!StackResize(stk, 2 * stk->capacity))
            return PUSH_ERROR;

    Data[stk->size] = value;
    ++stk->size;

    assert(!StackOK(stk));
    return STACK_OK;
};

int StackPop(Stack* stk)
{
    assert(!StackOK(stk));

    if (stk->size == 0)
        return UNDERFLOW;

    Data[stk->size] = POISON_VALUE;
    --stk->size;

    assert(!StackOK(stk));
    return STACK_OK;
};

int StackResize(Stack* stk, const size_t new_cap)
{
    assert(!StackOK(stk));

    if(new_cap < stk->size)
        return RESIZE_ERROR;

    Elem* new_data = (Elem*)realloc(stk->data, new_cap * sizeof(Elem) + 2 * sizeof(canary_t));

    if (!new_data)
        return MEMORY_ERROR;

    stk->data = new_data;
    stk->capacity = new_cap;
    StackFillPoison(stk, stk->size);

    #ifdef CANARY_PROTECTION
    stk->canary2_data = (canary_t*)(stk->data + stk->capacity * sizeof(Elem) + 2 * sizeof(canary_t));
	*(stk->canary2_data) = CANARY_DATA2;
    #endif //CANARY_PROTECTION

    assert(!StackOK(stk));
    return STACK_OK;
};

//elem - num of elem from which to fill
void StackFillPoison(Stack* stk, int elem)
{
	assert(stk);

	for (int i = elem; i < stk->capacity; ++i)
	{
		Data[i] = POISON_VALUE;
	}
}

int StackOK(const Stack* stk)
{
    //вернуть 0, есои все хорошо
    //вернуть код ошибки, если нет
    //во всех функция - assert(!StackOK)
    if (stk == NULL)
        return NOT_A_STACK;
    
    if(stk->data == NULL)
        return DTOR_ERROR;
    
    if (stk->size > stk->capacity)
        return OVERFLOW;
    
    if (stk->capacity <= 0)
        return UNDERFLOW;


    #ifdef CANARY_PROTECTION
    
    if (stk->canary1 != CANARY_VALUE1 || stk->canary2 != CANARY_VALUE2)
        return CANARY_STK;
    if (*(stk->canary1_data) != CANARY_DATA1 || *(stk->canary2_data) != CANARY_DATA2)
        return CANARY_DATA;

    #endif //CANARY_PROTECTION 

    
    #ifdef HASH_PROTECTION

    ///////////////////////////

    #endif //HASH_PROTECTION 


    return STACK_OK;
}

void StackDump(Stack* stk)
{

}