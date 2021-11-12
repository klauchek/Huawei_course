#include "stack.h"

int main()
{
    Stack stk = {};
    
    StackCtor(&stk, 2);
    printf("Created stk with cap = 2\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);


    StackPush(&stk, 10);
    printf("Pushed 10\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);


    StackPop(&stk);
    printf("Poped 10\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);

    StackPush(&stk, 20);
    printf("Pushed 20\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);

    StackPush(&stk, 30);
    printf("Pushed 30\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);
    
    StackPush(&stk, 40);
    printf("Pushed 40\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);

    StackPop(&stk);
    printf("Poped 40\n");
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);
 

    StackResize(&stk, 20);
    printf("cur cap = %ld, cur size = %ld\n", stk.capacity, stk.size);


    StackDtor(&stk);
    printf("Dtor called\n");

    fclose(output);

    return 0;
}