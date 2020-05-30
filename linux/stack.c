#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <limits.h>

// A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    void **array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (void*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, void* item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    printf("Pushed to stack\n");
}

// Function to remove an item from stack.  It decreases top by 1
void* pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
void* peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top];
}

int main(int argc, char const *argv[]) {}
  struct Stack *stack = createStack(100);
  int  var = 20;
  int *a = &var;
  push(stack, (int *)a);
  int *T = (int *)pop(stack);
  return 0;
}
