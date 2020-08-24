#ifndef _STATOR_H
#define _STATOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdlib.h>

/* ==== STACK ==== */

/* Universal stack, contains pointer to array of data */
typedef struct {
    uint8_t capacity;
    uint8_t size;
    void *data[];
} stack_t;

stack_t *StackCreate(uint8_t);
void StackDestroy(stack_t*);
uint8_t StackGetCapacity(stack_t*);
uint8_t StackGetSize(stack_t*);
void StackPush(stack_t*, void *);
void *StackPop(stack_t*);
void *StackPeek(stack_t*);

/* ==== STATE ==== */

struct state_s;
typedef struct state_s State;

/* Initialize global state stack */
void StateInit(size_t, uint8_t);
/* Allocates new state and returns it. Returns NULL on fail */
State *StateCreate(void);
/* Clones given state as new state and returns it. Returns NULL on fail */
State *StateCreateFrom(State *source);
/* Frees state */
void StateDestroy(State *state);
/* Pushes state on top */
void StatePush(State *state);
/* Pops current state from top */
void StatePop(void);
/* Peeks into active state */
State *StatePeek(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STATOR_H */