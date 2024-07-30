#include "input.h"

volatile Input input = {false};  // global input state

void update_input(void) {
  if (PORTC_BB[UP] == INPUT_STATE) input.up = true;
  if (PORTC_BB[DOWN] == INPUT_STATE) input.down = true;
  if (PORTC_BB[LEFT] == INPUT_STATE) input.left = true;
  if (PORTC_BB[RIGHT] == INPUT_STATE) input.right = true;
  if (PORTC_BB[SELECT] == INPUT_STATE) input.fire = true;
}

#ifndef EMULATION_EN
bool input_up(void) { return PORTC_BB[UP] == INPUT_STATE; }

bool input_down(void) { return PORTC_BB[DOWN] == INPUT_STATE; }

bool input_left(void) { return PORTC_BB[LEFT] == INPUT_STATE; }

bool input_right(void) { return PORTC_BB[RIGHT] == INPUT_STATE; }

bool input_fire(void) { return PORTC_BB[SELECT] == INPUT_STATE; }
#else 
bool input_up(void) { return (MDR_PORTF->GFEN & 2); }

bool input_down(void) { return (MDR_PORTF->GFEN & 4); }

bool input_left(void) { return (MDR_PORTF->GFEN & 8); }

bool input_right(void) { return (MDR_PORTF->GFEN & 16); }

bool input_fire(void) { return (MDR_PORTF->GFEN & 1); }
#endif // EMULATION_EN
