#include "stack.h"

FILE* output = fopen("output.txt", "a");

int StackCtor(Stack* stk, size_t cap)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK((stk->capacity == 0), stk, CTOR_ERROR);

    #ifdef CANARY_PROTECTION
    stk->canary1 = CANARY_VALUE1;
    stk->canary2 = CANARY_VALUE2;
    #endif //CANARY_PROTECTION

    stk->data = (Elem*)calloc(cap * sizeof(Elem) + 2 * sizeof(canary_t), sizeof(stk->data[0]));
    STK_CHECK(stk->data, stk, MEMORY_ERROR);
 
    stk->capacity = cap;
    stk->size = 0;

    StackFillPoison(stk, 0);

    #ifdef CANARY_PROTECTION
    stk->canary1_data = (canary_t*)(stk->data);
    *(stk->canary1_data) = CANARY_DATA1;
    stk->canary2_data = (canary_t*)(stk->data + sizeof(canary_t) + cap * sizeof(Elem));
    *(stk->canary2_data) = CANARY_DATA2;
    #endif //CANARY_PROTECTION

    #ifdef HASH_PROTECTION
    stk->HashSum = Hash(stk);
    #endif //HASH_PROTECTION

    return STACK_OK;
};

int StackDtor(Stack* stk)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK(stk->data, stk, DTOR_ERROR);

    free(stk->data);

    stk->size = 0;
    stk->capacity = 0;

    return STACK_OK;
};

int StackPush(Stack* stk, Elem value)
{
    STK_CHECK(stk, stk, NOT_A_STACK);

    #ifdef CANARY_PROTECTION
    STK_CHECK((stk->canary1 == CANARY_VALUE1 && stk->canary2 == CANARY_VALUE2), stk, CANARY_STK);
    STK_CHECK((*(stk->canary1_data) == CANARY_DATA1 && (*(stk->canary2_data)) == CANARY_DATA2), stk, CANARY_DATA);
    #endif //CANARY_PROTECTION

    #ifdef HASH_PROTECTION
    STK_CHECK((stk->HashSum == Hash(stk)), stk, HASH)
    #endif //HASH_PROTECTION

    STK_CHECK((stk->size <= stk->capacity), stk, OVERFLOW);

    if(stk->size == stk->capacity)
    {
        if(StackResize(stk, stk->capacity * 2))
            STK_CHECK(false, stk, RESIZE_ERROR);
    }

    Data[stk->size++] = value;

    #ifdef HASH_PROTECTION
    stk->HashSum = Hash(stk);
    #endif //HASH_PROTECTION

    return STACK_OK;
};

int StackPop(Stack* stk)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK(stk->size, stk, UNDERFLOW);

    #ifdef CANARY_PROTECTION
    STK_CHECK((stk->canary1 == CANARY_VALUE1 && stk->canary2 == CANARY_VALUE2), stk, CANARY_STK);
    STK_CHECK((*(stk->canary1_data) == CANARY_DATA1 && (*(stk->canary2_data)) == CANARY_DATA2), stk, CANARY_DATA);
    #endif //CANARY_PROTECTION

    #ifdef HASH_PROTECTION
    STK_CHECK((stk->HashSum == Hash(stk)), stk, HASH)
    #endif //HASH_PROTECTION


    Data[stk->size - 1] = POISON_VALUE;
    --stk->size;

    #ifdef HASH_PROTECTION
    stk->HashSum = Hash(stk);
    #endif //HASH_PROTECTION

    return STACK_OK;
};

int StackResize(Stack* stk, const size_t new_cap)
{
    STK_CHECK(stk, stk, NOT_A_STACK);
    STK_CHECK((new_cap >= stk->size), stk, RESIZE_ERROR);

    #ifdef CANARY_PROTECTION
    STK_CHECK((stk->canary1 == CANARY_VALUE1 && stk->canary2 == CANARY_VALUE2), stk, CANARY_STK);
    STK_CHECK((*(stk->canary1_data) == CANARY_DATA1 && (*(stk->canary2_data)) == CANARY_DATA2), stk, CANARY_DATA);
    #endif //CANARY_PROTECTION

    #ifdef HASH_PROTECTION
    STK_CHECK((stk->HashSum == Hash(stk)), stk, HASH)
    #endif //HASH_PROTECTION


    Elem* new_data = (Elem*)realloc(stk->data, new_cap * sizeof(Elem) + 2 * sizeof(canary_t));

    STK_CHECK(new_data, stk, MEMORY_ERROR);

    stk->data = new_data;
    stk->capacity = new_cap;
    StackFillPoison(stk, stk->size);

    #ifdef CANARY_PROTECTION
    stk->canary2_data = (canary_t*)(stk->data + stk->capacity * sizeof(Elem) + 2 * sizeof(canary_t));
	*(stk->canary2_data) = CANARY_DATA2;
    #endif //CANARY_PROTECTION

    #ifdef HASH_PROTECTION
    stk->HashSum = Hash(stk);
    #endif //HASH_PROTECTION

    return STACK_OK;
};

//elem - num of elem from which to fill
void StackFillPoison(Stack* stk, size_t elem)
{
	assert(stk);

	for (size_t i = elem; i < stk->capacity; ++i)
	{
		Data[i] = POISON_VALUE;
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
        
        case HASH:
            (output, "Hash has been changed without reason\n");
            break;

        default:

            fprintf(output, "All is OK\n");
    }
}


void StackDump(Stack *stk, int error, FILE* output)
{

    fprintf(output, "\nError code: %d\n", error);
    fprintf (output, "Stack pointer = [%p]\n", stk);

    fprintf (output, "Capacity: %lu \n", stk->capacity);
    fprintf (output, "Size : %lu \n", stk->size);

    #ifdef HASH_PROTECTION
    fprintf (output, "HashSum = [%llu]\n", (stk->HashSum));
    fprintf (output, "True HashSum = [%llu]\n", Hash(stk));
    #endif //HASH_PROTECTION
    
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

unsigned long long Hash (Stack* stk)
{
    char* stack_buffer = (char *) stk;

    unsigned long long old_hash = stk->HashSum;
    stk->HashSum = 0;

    unsigned long long new_hash = 0;

    for (int i = 0; i < sizeof (*stk); i++)
    {
        new_hash = ROR (new_hash) + stack_buffer[i];
    }

    char * data_buffer = (char *) stk->data - sizeof(canary_t);
    for (size_t i = 0; i < stk->capacity * sizeof (Elem) + 2 * sizeof (canary_t); i++)
    {
        new_hash = ROR (new_hash) + data_buffer[i];
    }

    stk->HashSum = old_hash;

    return new_hash;
}

unsigned long long ROR (unsigned long long elem)
{
  return (elem >> 1 | elem << 63);
}


void TestProcessing()
{
    Stack stk = {};
    int func_code = 0;
    size_t stk_cap = 0;
    size_t num_of_elems = 0;
    Elem stk_elem = 0;
    size_t new_stk_cap = 0;

    printf ("Enter the number of the function you want to test (correct work): \n\n");
    printf (" Constructor - 1\n Destructor - 2\n Push - 3\n Pop - 4\n Resize - 5\n");

    scanf("%d", &func_code);

    switch (func_code)
    {
    case 1:
        printf ("Enter stack capacity: \n");
        scanf("%zu", &stk_cap);

        StackCtor(&stk, stk_cap);
        printf("Created stack with cap = %zu\n", stk_cap);
        StackDtor(&stk);
        break;

    case 2:
        StackCtor(&stk, 0);
        
        StackDtor(&stk);
        printf("Dtor called\n");
        break;

    case 3:
        printf ("Enter stack capacity: \n");
        scanf("%zu", &stk_cap);

        StackCtor(&stk, stk_cap);
        printf("Created stack with cap = %zu\n", stk_cap);

        printf("Enter how many numbers to push: \n");
        scanf("%zu", &num_of_elems);
        printf("Enter numbers to push: \n");

        for(int i = 0; i < num_of_elems; ++i)
        {
            scanf("%d", &stk_elem);
            StackPush(&stk, stk_elem);
        }

        StackDtor(&stk);
        break;

    case 4:
        StackCtor(&stk, 2);
        StackPush(&stk, 10);
        StackPop(&stk);
        printf("Pushed and then poped 10\n");
        StackDtor(&stk);
        break;

    case 5:
        StackCtor(&stk, 0);
        printf("Created stack with cap = %zu", stk.capacity);
        printf("Enter new cap:");
        
        scanf("%zu", &new_stk_cap);
        StackResize(&stk, new_stk_cap);
        printf("New capacity is: %zu\n", stk.capacity);
        StackDtor(&stk);
        break;
    
    default:
        break;
    }

    printf ("\n====================================================================\n");
    printf ("Enter the number of the function you want to break (incorrect work): \n\n");
    printf (" Constructor - 1\n Destructor - 2\n Pop - 3\n Resize - 4\n");

    scanf("%d", &func_code);

    switch (func_code)
    {
    case 1:
        StackCtor(&stk, 2);
        printf("Created stk with cap = 2\n");

        StackCtor(&stk, 1);
        printf("Created stk with cap = 2\n");
        break;

    case 2:

        StackCtor(&stk, 0);
        StackDtor(&stk);
        printf("Dtor called. Trying to call for the second time\n");
        StackDtor(&stk);
        break;

    case 3:
        StackCtor(&stk, 0);
        printf("Created stk with cap = 0 and calling StackPop\n");
        StackPop(&stk);
        break;

    case 4:
        StackCtor(&stk, 1);
        StackPush(&stk, 10);
        printf("Created stk with cap = 1 and 1 element and calling StackPop\n");
        StackResize(&stk, 0);
        break;

    default:
        break;
    }
}