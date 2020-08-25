#include "stator.h"

#define MEMBER_SIZE(t, m) sizeof(((t *)0)->m)

stack_t *StackCreate(uint8_t capacity) {
	/* Allocate memory for meta + required members */
	stack_t *stack = malloc(sizeof(stack_t) + capacity * MEMBER_SIZE(stack_t, data[0]));

	if (!stack) {
		/* TODO: Error */
	}
	
	stack->capacity = capacity;
	stack->size = 0;

	return stack;
}

void StackDestroy(stack_t* stack) {
	free(stack->data);
	free(stack);
}

uint8_t StackGetCapacity(stack_t* stack) {
	return stack->capacity;
}

uint8_t StackGetSize(stack_t* stack) {
	return stack->size;
}

void StackPush(stack_t* stack, void *value) {
	if (stack->size == stack->capacity) {
		// Fail or log
		return;
	}

	stack->data[stack->size++] = value;
}

void *StackPop(stack_t* stack) {
	return stack->data[--stack->size];
}


void *StackPeek(stack_t *stack) {
	if (stack->size == 0) {
		return NULL;
	}

	return stack->data[stack->size-1];
}