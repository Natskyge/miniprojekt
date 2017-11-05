#include <stdio.h>
#include <stdlib.h>

/* Definition of the data, can be changed as needed */
typedef struct Data {
	int data;
} Data;

/* An item in the stack */
typedef struct Item {
	Data data;
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
makeItem(Data data, Item *prev)
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
push(Data data, Stack *stack)
{
	if (stack->size >= stack->max) {
		/* Error, stackoverflow */
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
	if (0 == stack->size) {
		/* Stack is empty */
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
Data
peek(Stack* stack)
{
	return stack->top->data;
}

/* Free the stacks items from memory */
int
clearStack(Stack *stack)
{
	while (stack->size > 0) {
		pop(stack);
	}
	return 0;
}

int
main(void)
{
	/* A test of the data Stucture */
	Stack *myStack = stackInit(10);      /* Returns: */
	printf("Size: %d\n", myStack->size); /* 0        */
	printf("Max:  %d\n", myStack->max);  /* 10       */
	push((Data){ .data = 23 }, myStack);
	printf("Size: %d\n", myStack->size); /* 1        */
	printf("Max:  %d\n", myStack->max);  /* 10       */
	printf("Data: %d\n", peek(myStack)); /* 23       */
	pop(myStack);
	printf("Size: %d\n", myStack->size); /* 0        */
	printf("Max:  %d\n", myStack->max);  /* 10       */
	for (int i = 1; push((Data){ .data = i }, myStack) != 1; i++) {}
	printf("Size: %d\n", myStack->size); /* 10       */
	printf("Max:  %d\n", myStack->max);  /* 10       */
	printf("Data: %d\n", peek(myStack)); /* 10       */
	clearStack(myStack);
	printf("Size: %d\n", myStack->size); /* 0        */
	printf("Max:  %d\n", myStack->max);  /* 10       */
	return 0;
}