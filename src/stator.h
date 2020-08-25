#ifndef _STATOR_H
#define _STATOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdlib.h>

#ifndef offsetof
#define offsetof(t, m) ((size_t)&(((t *)0)->m))
#endif

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
State *StateCreateFrom(State*);
/* Frees state */
void StateDestroy(State*);
/* Pushes state on top */
void StatePush(State*);
/* Pops current state from top */
void StatePop(void);
/* Peeks into active state */
State *StatePeek(void);
/* Sets offset in state_s of function that is called when given state is pushed, AFTER it's pushed but BEFORE callback for ANY */
void StateSetPushedFunc(size_t);
/* Sets offset in state_s of function that is called when given state is poped, BEFORE it's poped */
void StateSetPopedFunc(size_t);
/* Sets function called AFTER ANY state is pushed and AFTER state specific push callback is called */
void StateSetAnyPushFunc(void(*)(void));
/* Sets function called AFTER ANY state is poped */
void StateSetAnyPopFunc(void(*)(void));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STATOR_H */