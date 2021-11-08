#include "stack.h"

FILE* output = fopen("output.txt", "a");

int StackCtor(Stack* stk, size_t cap)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK(stk->capacity == 0, stk, CTOR_ERROR);

    #ifdef CANARY_PROTECTION
    stk->canary1 = CANARY_VALUE1;
    stk->canary2 = CANARY_VALUE2;
    #endif //CANARY_PROTECTION

    stk->data = (Elem*)calloc(cap * sizeof(Elem) + 2 * sizeof(canary_t), sizeof(stk->data[0]));
    STK_CHECK(stk->data, stk, MEMORY_ERROR);
 
    stk->capacity = cap;
    stk->size = 0;

    #ifdef CANARY_PROTECTION
    stk->canary1_data = (canary_t*)(stk->data);
    *(stk->canary1_data) = CANARY_DATA1;
    stk->canary2_data = (canary_t*)(stk->data + sizeof(canary_t) + stk->capacity * sizeof(Elem));
    *(stk->canary2_data) = CANARY_DATA2;
    #endif //CANARY_PROTECTION

    StackFillPoison(stk, 0);

    return STACK_OK;
};

int StackDtor(Stack* stk)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK(stk->data, stk, DTOR_ERROR);

    free(stk->data);
    stk->data = NULL;
    stk->size = 0;
    stk->capacity = 0;

    return STACK_OK;
};

int StackPush(Stack* stk, Elem value)
{
    STK_CHECK(stk, stk, NOT_A_STACK);

    #ifdef CANARY_PROTECTION
    STK_CHECK((stk->canary1 == CANARY_VALUE1 && stk->canary2 == CANARY_VALUE2), stk, CANARY_STK);
    STK_CHECK((*(stk->canary1_data) == CANARY_DATA1 && *(stk->canary2_data) == CANARY_DATA2), stk, CANARY_DATA);
    #endif //CANARY_PROTECTION

    if((stk->size + 1) >= stk->capacity)
        STK_CHECK(StackResize(stk, 2 * stk->capacity), stk, RESIZE_ERROR);

    Data[stk->size] = value;
    ++stk->size;

    return STACK_OK;
};

int StackPop(Stack* stk)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK(stk->size, stk, UNDERFLOW);

    #ifdef CANARY_PROTECTION
    STK_CHECK((stk->canary1 == CANARY_VALUE1 && stk->canary2 == CANARY_VALUE2), stk, CANARY_STK);
    STK_CHECK((*(stk->canary1_data) == CANARY_DATA1 && *(stk->canary2_data) == CANARY_DATA2), stk, CANARY_DATA);
    #endif //CANARY_PROTECTION

    Data[stk->size] = POISON_VALUE;
    --stk->size;
//  тоже сделать ресайз даун
    return STACK_OK;
};

int StackResize(Stack* stk, const size_t new_cap)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK(new_cap >= stk->size, stk, RESIZE_ERROR);

    #ifdef CANARY_PROTECTION
    STK_CHECK((stk->canary1 == CANARY_VALUE1 && stk->canary2 == CANARY_VALUE2), stk, CANARY_STK);
    STK_CHECK((*(stk->canary1_data) == CANARY_DATA1 && *(stk->canary2_data) == CANARY_DATA2), stk, CANARY_DATA);
    #endif //CANARY_PROTECTION

    Elem* new_data = (Elem*)realloc(stk->data, new_cap * sizeof(Elem) + 2 * sizeof(canary_t));

    STK_CHECK(new_data, stk, MEMORY_ERROR);

    stk->data = new_data;
    stk->capacity = new_cap;
    StackFillPoison(stk, stk->size);

    #ifdef CANARY_PROTECTION
    stk->canary2_data = (canary_t*)(stk->data + stk->capacity * sizeof(Elem) + 2 * sizeof(canary_t));
	*(stk->canary2_data) = CANARY_DATA2;
    #endif //CANARY_PROTECTION

    return STACK_OK;
};

//elem - num of elem from which to fill
void StackFillPoison(Stack* stk, size_t elem)
{
	assert(stk);

	for (size_t i = elem; i < stk->capacity; ++i)
	{
		Data[i] = POISON_VALUE;
        printf("hey\n");
	}
}


void ErrorsProcessing(int error)
{
    switch(error)
    {
        case NOT_A_STACK:
            fprintf(output, "Stack pointer is NULL\n");
            break;

        case MEMORY_ERROR:
            fprintf(output, "Not enough memory or another memory error\n");
            break;
    
        case OVERFLOW:
            fprintf(output, "Stack is overflow: size > capacity\n");
            break;
    
        case UNDERFLOW:
            fprintf(output, "Stack is underflow: size <= 0\n");
            break;
    
        case POP_ERROR:
            fprintf(output, "Something went wrong in Pop func\n");
            break;
        
        case PUSH_ERROR:
            fprintf(output, "Something went wrong in Push func\n");
            break;
    
        case RESIZE_ERROR:
            fprintf(output, "Something went wrong in resize func\n");
            break;

        case DTOR_ERROR:
            fprintf(output, "Dtor was called twice or another dtor error\n");
            break;
    
        case CTOR_ERROR:
            fprintf(output, "Ctor was called twice or another ctor error\n");
            break;

        case CANARY_STK:
            fprintf(output, "One of stack canaries has been changed\n");
            break;

        case CANARY_DATA:
            fprintf(output, "One of stack canaries has been changed\n");
            break;
        
        /*case HASH_DATA:
            comment =
            break;

        case HASH_STK:
            comment =
            break; */

        default:

            fprintf(output, "All is OK\n");
    }
}


void StackDump(Stack *stk, int error, FILE* output) {

    //FILE* output = fopen("output.txt", "wb");
    fprintf(output, "Error code: %d\n", error);
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

    //fclose(output);
}


int StackCheck(bool condition, Stack *stk, int error, const char *file, const int line, const char *function)
{
    if (!condition)
    {
        assert(output);
        fprintf(output, "Error %d: file %s line %d\n", error, file, line);
        fprintf(output, "function '%s'\n", function);
        ErrorsProcessing(error);
        StackDump(stk, error, output);
    }

    return error;
}