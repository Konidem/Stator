#include "stator.h"

void *GetFunctionFromStateAndOffset(State *state, size_t offset);

stack_t *stateStack;
size_t state_size;
void (*push_func)(void);
void (*pop_func)(void);
size_t state_push_func_offset;
size_t state_pop_func_offset;


void StateInit(size_t size, uint8_t max) {
	state_size = size;
	stateStack = StackCreate(max);
	push_func = NULL;
	pop_func = NULL;
}

State *StateCreate() {
	State *state = malloc(state_size);
	memset(state, 0, state_size);
	return state;
}

State *StateCreateFrom(State *source) {
	State *state = StateCreate();
	if (state) {
		memcpy(state, source, state_size);
	}

	return state;
}

void StateDestroy(State *state) {
	free(state);
}

void StatePush(State *state) {
	StackPush(stateStack, state);

	if (state_push_func_offset != NULL) {
		void *state = (void*)StatePeek();
		void (*func)(void) = GetFunctionFromStateAndOffset(state, state_push_func_offset);
		func();
	}

	if (push_func != NULL) {
		push_func();
	}
}

void StatePop() {
	if (state_pop_func_offset != NULL) {
		void *state = (void*)StatePeek();
		void (*func)(void) = GetFunctionFromStateAndOffset(state, state_pop_func_offset);
		func();
	}

	StackPop(stateStack);

	if (pop_func != NULL) {
		pop_func();
	}
}

State *StatePeek() {
	return StackPeek(stateStack);
}

void StateSetPushedFunc(size_t offset) {
	state_push_func_offset = offset;
}

void StateSetPopedFunc(size_t offset) {
	state_pop_func_offset = offset;
}

void StateSetAnyPushFunc(void(*func)(void)) {
	push_func = func;
}

void StateSetAnyPopFunc(void(*func)(void)) {
	pop_func = func;
}

void *GetFunctionFromStateAndOffset(State *state, size_t offset) {
	/* This monstrosity gets address of function in unknown structure */
	/* 1. Cast variables to size_t so we won't get thing like 50 + 8 = 60 (thanks C BTW, took me almost .5h to realise) */
	/* 2. Add offset so now we're pointing to address where function pointer shall be */
	/* 3. Cast again to void** so we can dereference correctly */
	/* 4. Dereference pointer to get function pointer at this address */
	/* 5. Return pointer to function at given offset in given struct */
	/* 6. Grab a coffee */
	return *(void**)((size_t)state + (size_t)offset);
}
