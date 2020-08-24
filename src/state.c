#include "stator.h"

stack_t *stateStack;
size_t state_size;


void StateInit(size_t size, uint8_t max) {
    state_size = size;
    stateStack = StackCreate(max);
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
}

void StatePop() {
    StackPop(stateStack);
}

State *StatePeek() {
    return StackPeek(stateStack);
}

