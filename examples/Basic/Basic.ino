/**
 * This example shows how to create states 
 * and change state on button press.
 * 
 * LED is used to indicate that active
 * state is in fact changed.
 * 
 * Interrupt is used to simplify code but
 * it's not required by any means.
 * 
 * Global states are also not required!
 * You can create state in runtime
 * anywhere and push it.
 */

#include <stator.h>

#define LED_PIN 13
#define BTN_PIN 3

/**
 * Your state model.
 * Define here every variable and callback that you might
 * change depenging on current state like responses to
 * different button presses or incomming serial stream
 */
struct state_s {
	void (*btn_pressed)(void); /* Button pressed callback */
};

/* Global states */
State *state1, *state2;

void State1ButtonPressed() {
	digitalWrite(LED_PIN, HIGH);

	/* Enter "State2" */
	StatePush(state2);
}

void State2ButtonPressed() {
	digitalWrite(LED_PIN, LOW);

	/* Go back to previous state */
	StatePop();
}

void IRQHandler() {
	auto state = StatePeek();
	state->btn_pressed();
}

void setup() {
	/* Init state machine, set maximal depth of states to 2 */
	/* This is fake limitation made only to speed up execution */
	/* If you cannot decide on how many states deep will your */
	/* program be, add following line before including stator.h */
	/* #define SR_USE_LINKED_LIST */
	/* This will remove this limitation but slow things down */
	/* a little bit. It's up to you */
	StateInit(sizeof(state_s), 2);

	/* Create states */
	state1 = StateCreate();
	state1->btn_pressed = &State1ButtonPressed;

	state2 = StateCreate();
	state2->btn_pressed = &State2ButtonPressed;

	/* Set state 1 as active */
	StatePush(state1);

	pinMode(LED_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BTN_PIN), IRQHandler, FALLING);
}

void loop() {}
