# Stator

Library for managing state of your application, mainly purposed for use with arduino or microcontrollers.

## Purpose

This library is used to prevent handlers like this
``` C
void buttonPressed() {
  switch(state) {
  case state1:
    doA();
  case state2:
  case state3:
    doB();
  case state4:
    doC();
  }
}
```

and instead change them for
``` C
void buttonPressed() {
  State *state = StatePeek();
  state->buttonPressed();
}
```

which calls assigned function.

This is most useful in programs that use same buttons for different things depending on current state.

## Usage

### Defining state
``` C
struct state_s {
  /* Variables that change from state to state */
  uint32_t counter;
  /* Callbacks */
  void (*pinChanged)(void);
  void (*analogTreshold)(void);
}
```

### Initializing state machine
``` C
int main() {
  ...
  /* Initializes state machine with maximum depth of 5 (including entry state) */
  StateInit(sizeof(state_s), 5);
  ...
}
```

### Creating states
``` C
int main() {
  ...
  /* Create empty state */
  State *mainstate = StateCreate();
  /* Set button callback */
  mainstate->pinChanged = &btnHandler;
  
  /* Clone state */
  State *newstate = StateCreateFrom(mainstate);
  newstate->analogTreshold = &analogHandler;
  /* newstate now has defined both pinChanged and analogTreshold handlers */
  /* this feature is useful when you have common callbacks for many different states or create one in runtime from template */
  ...
}
```

### Destorying states
``` C
int main() {
  ...
  /* Create empty state */
  State *state = StateCreate();
  ...
  /* Destroy state */
  StateDestroy(state)
  ...
}
```

### Changing current state
``` C
int main() {
  ...
  /* Activates state */
  StatePush(s1); /* Active state is "s1" */
  StatePush(s2); /* Active state is "s2" */
  /* Returns to previous active state */
  StatePop();  /* Active state is "s1" */
  ...
}
```

### Accessing current active state
``` C
void handler() {
  /* Get currently active state */
  State *state = StatePeek();
  state->pinChanged();
}
```
