/**
 * This example shows how to use events
 * fired when state is changed by expanding
 * Basic example concept
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
	void (*state_pushed)(void); /* State poped callback */
	void (*state_poped)(void); /* State poped callback */
};

/* Global states */
State *state1, *state2;

void ButtonPressed() {
	/* Enter "State2" */
	StatePush(state2);
}

void IRQHandler() {
	auto state = StatePeek();
	state->btn_pressed();
}

void toggleLED() {
	static int enabled = true;
	enabled = !enabled;
	digitalWrite(LED_PIN, enabled);
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
	state1->btn_pressed = &ButtonPressed;

	state2 = StateCreate();
	/* When state2 is pushed it'll immediately pop itself */
	state2->state_pushed = StatePop();
	/* When state2 is poped it'll toggle LED */
	state2->state_poped = &toggleLED;

	/* Sets offset of callbacks in your state struct */
	/* Always use offsetof macro! Never hard code offset! */
	StateSetPushedFunc(offsetof(state_s, state_pushed));
	StateSetPopedFunc(offsetof(state_s, state_poped));
	
	/* Uncommenting this line will enable event that */
	/* is called whenever ANY state is pushed */
	/*StateSetAnyPushFunc(&toggleLED);*/
	/* there's also one called when any state is poped */
	/*StateSetAnyPopFunc(&toggleLED);*/

	/* Set state 1 as active */
	StatePush(state1);

	pinMode(LED_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BTN_PIN), IRQHandler, FALLING);
}

void loop() {}
