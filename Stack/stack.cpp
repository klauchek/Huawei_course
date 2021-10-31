#include "stack.h"


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

    StackCheck(stk);

    return STACK_OK;
};

int StackDtor(Stack* stk)
{
    StackCheck(stk);

    free(stk->data);
    stk->data = NULL;
    stk->size = -1;
    stk->capacity = -1;

    return STACK_OK;
};

int StackPush(Stack* stk, Elem value)
{
    StackCheck(stk);

    if((stk->size + 1) >= stk->capacity)
        if(!StackResize(stk, 2 * stk->capacity))
            return PUSH_ERROR;

    Data[stk->size] = value;
    ++stk->size;

    StackCheck(stk);
    return STACK_OK;
};

int StackPop(Stack* stk)
{
    StackCheck(stk);

    if (stk->size == 0)
        return UNDERFLOW;

    Data[stk->size] = POISON_VALUE;
    --stk->size;

    StackCheck(stk);
    return STACK_OK;
};

int StackResize(Stack* stk, const size_t new_cap)
{
    StackCheck(stk);

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

    StackCheck(stk);
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

char* ErrorsProcessing(int error)
{
    char* comment = (char*)calloc(50, sizeof(char));

    switch(error)
    {
        case NOT_A_STACK:
            comment = "Stack pointer is NULL";
            break;

        case MEMORY_ERROR:
            comment = "Not enough memory or another memory error";
            break;
    
        case OVERFLOW:
            comment = "Stack is overflow: size > capacity";
            break;
    
        case UNDERFLOW:
            comment = "Stack is underflow: size <= 0";
            break;
    
        case POP_ERROR:
            comment = "Something went wrong in Pop func";
            break;
        
        case PUSH_ERROR:
            comment = "Something went wrong in Push func";
            break;
    
        case RESIZE_ERROR:
            comment = "Something went wrong in resize func";
            break;

        case DTOR_ERROR:
            comment = "Dtor was called twice or another dtor error";
            break;
    
        case CTOR_ERROR:
            comment = "Ctor was called twice or another ctor error";
            break;

        case CANARY_STK:
            comment = "One of stack canaries has been changed";
            break;

        case CANARY_DATA:
            comment = "One of stack canaries has been changed";
            break;
        
        /*case HASH_DATA:
            comment =
            break;

        case HASH_STK:
            comment =
            break; */

        default:

            comment = "All is OK";
    }

    char* output = comment;
    free(comment);

    return output;
}


void StackDump(Stack *stk, int error) {

    FILE* output = fopen("output.txt", "w");
    fprintf(output, "Error code: %d", error);
    fprintf (output, "Stack pointer = [%p]\n", stk);

    fprintf (output, "Capacity: %lu \n", stk->capacity);
    fprintf (output, "Size : %lu \n", stk->size);

    //fprintf (output, "* HashSum      = [%llu]\n", (stk->HashSum));
    //fprintf (output, "* True HashSum = [%llu]\n", stk(thou));

    //fprintf (output, "Data = [%p]\n", (stk->data));

    #ifdef CANARY_PROTECTION
    fprintf (output, "Left Canary  = [%lx]\n", stk->canary1);
    fprintf (output, "Right Canary = [%lx]\n", stk->canary2);

    fprintf (output, "Left Canary data = [%lx]\n", stk->canary1_data);
    fprintf (output, "Right Canary data = [%lx]\n", stk->canary2_data);
    #endif //CANARY_PROTECTION

    fprintf (output, "Stack Elements: \n");
    for (size_t i = 0; i < stk->size; i++) {

        fprintf (output, "%lf\n", Data[i]);

    }

    fprintf (output, "============================\n");

    fclose(output);
}


void StackCheck(Stack *stk)
{
    FILE* output = fopen("output.txt", "w");
    int error = StackOK(stk);
    if (error)
    {
        assert(output);
        char* comment = ErrorsProcessing(error);
        fprintf(output, "Error %d: file %s line %d ", error, __FILE__, __LINE__);
        fprintf(output, "function '%s'\n", __FUNCTION__);
        fprintf(output, "Error description: %s\n\n", comment);
        fclose(output);
        StackDump(stk, error);
    }
    fclose(output);
}