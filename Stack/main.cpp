#include "stack.h"

int main()
{
    Stack stk = {};
    
    StackCtor(&stk, 1);
    
   // StackPop(&stk);
    

    printf("Created empty stack for 10 elems\n");
    for (int i = 0; i < stk.size; ++i)
    {
        printf("%lf\n", ((Elem*)(stk.data + sizeof(canary_t)))[i]);
    }

    StackPush(&stk, 10);
    printf("Pushed 10\n");
    for (int i = 0; i < stk.size; ++i)
    {
        printf("%lf\n", ((Elem*)(stk.data + sizeof(canary_t)))[i]);
    }

    StackPush(&stk, 20);
    printf("Pushed 20\n");
    for (int i = 0; i < stk.size; ++i)
    {
        printf("%lf\n", ((Elem*)(stk.data + sizeof(canary_t)))[i]);
    }

    StackPush(&stk, 30);
    printf("Pushed 30\n");
    for (int i = 0; i < stk.size; ++i)
    {
        printf("%lf\n", ((Elem*)(stk.data + sizeof(canary_t)))[i]);
    }

    StackPush(&stk, 40);
    printf("Pushed 40\n");
    for (int i = 0; i < stk.size; ++i)
    {
        printf("%lf\n", ((Elem*)(stk.data + sizeof(canary_t)))[i]);
    }

    StackPop(&stk);
    printf("Poped 40\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);
    for (int i = 0; i < stk.size; ++i)
    {
        printf("%lf\n", ((Elem*)(stk.data + sizeof(canary_t)))[i]);
    }

    StackResize(&stk, 20);
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);



    StackDtor(&stk);

    fclose(output);

    return 0;
}