#include <stdio.h>
#include <stdlib.h>

/* Type of data, replace int as needed */
#define type int

/* An item in the stack */
typedef struct Item {
	type data;
	struct Item *prev;
} Item;

/* The stack */
typedef struct Stack {
	Item *top;
	size_t size;
	size_t max;
} Stack;

/* Initialize a stack */
Stack*
stackInit(size_t max)
{
	/* Allocate memory for the stack */
	Stack *newStack = (Stack*)malloc(sizeof(Stack));
	
	/* Initialize the stack for pushing */
	newStack->top = NULL;
	newStack->size = 0;
	newStack->max = max;
	
	return newStack;
}

/* Create an item with the values passed */
Item*
makeItem(type data, Item *prev)
{
	/* Allocate memory for the item */
	Item *newItem = (Item*)malloc(sizeof(Item));
	
	/* Set the values of the item */
	newItem->data = data;
	newItem->prev = prev;
	
	return newItem;
}

/* Push an item to the top of the stack */
int
push(type data, Stack *stack)
{
	if (!stack || stack->size >= stack->max) {
		/* Error, stackoverflow or stack is null */
		return 1;
	} else {
		/* Make item and change the stack accordingly */
		Item *newItem = makeItem(data, stack->top);
		stack->top = newItem;
		++stack->size;
		return 0;
	}
}

/* Remove top item from stack */
int
pop(Stack *stack)
{
	if (!stack || 0 >= stack->size) {
		/* Error, stack is empty or null*/
		return 1;
	} else {
		/* Change top to the one below and free the old top from memory */
		Item *oldTop = stack->top;
		stack->top = stack->top->prev;
		--stack->size;
		free(oldTop);
		return 0;
	}
}

/* Return the data of the top item */
type
peek(Stack* stack)
{
	if (!stack || stack->size == 0) {
		/* There is no data, returns default value of type */
	} else {
		return stack->top->data;
	}
}

/* Free the stacks items from memory */
int
clearStack(Stack *stack)
{
	if (!stack || stack->size <= 0)
		return 1;
	
	while (stack->size > 0) {
		pop(stack);
	}
	return 0;
}

int
printStack(Stack* stack)
{
	printf("Size: %d\n", stack->size);
	printf("Max:  %d\n", stack->max);
	printf("type: %d\n\n", peek(stack));
	return 1;
}

int
main(void)
{
	/* A test of the data Stucture */
	Stack *myStack = stackInit(10);
	printf("pop return code: %d\n", pop(myStack));
	printStack(myStack);


	push(23, myStack);
	printStack(myStack);

	pop(myStack);
	printStack(myStack);

	for (int i = 1; push(i, myStack) != 1; i++) {}
	printf("push return code: %d\n", push(23, myStack));
	printStack(myStack);

	clearStack(myStack);
	printStack(myStack);

	myStack = NULL;

	printf("push return code: %d\n", push(23, myStack));
	printf("pop return code: %d\n", pop(myStack));

	free(myStack);

	return 1;
}