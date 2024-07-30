#ifndef SETUP_H
#define SETUP_H

#include "display/display.h"
#include "game/input.h"

extern "C" {
#include "core_cm3.h"
// imports for IntelliSense only (can be removed)
// normally this file is auto-linked by the Keil uVision IDE
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32Fx.h"
#include "system_MDR32F9Qx.h"
}

PORT_InitTypeDef PORT_InitStructure;

#if defined EMULATION_EN && defined CPUSPEED
extern "C" {
/*Инициаализация внешнего кварца*/
void CPU_init (void){
  MDR_RST_CLK->HS_CONTROL = 0x01; /* вкл. HSE осцилятора */
  while (MDR_RST_CLK->CLOCK_STATUS & (1 << 2) == 0x00); /* ждем пока HSE выйдет в рабочий режим */

  //MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (4 << 8));//Коэф 5
  MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (9 << 8));//Коэф 10
  while((MDR_RST_CLK->CLOCK_STATUS & 0x02) != 0x02); //ждем когда PLL выйдет в раб. режим

  MDR_RST_CLK->CPU_CLOCK = (2 /*источник для CPU_C1*/
  | (1 << 2) /*источник для CPU_C2*/
  | (0 << 4) /*предделитель для CPU_C3*/
  | (1 << 8));/*источник для HCLK*/
}
}
#endif // // EMULATION_EN

void init_leds(void) {
	#ifndef EMULATION_EN
  // Enables the RTCHSE clock on PORTC and PORTD
  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD, ENABLE);

  // Configure PORTD pins 10..14 for output to switch LEDs on/off
  PORT_InitStructure.PORT_Pin =
      (PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14);

  PORT_InitStructure.PORT_OE = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

  PORT_Init(MDR_PORTD, &PORT_InitStructure);
	#endif // EMULATION_EN
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE); // for "buttons"
	#if defined EMULATION_EN && defined BLINK
	PORT_InitStructure.PORT_Pin = PORT_Pin_1; // PF1(led)
	
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
	
	PORT_Init(MDR_PORTF, &PORT_InitStructure);
	#endif // // EMULATION_EN && BLINK
}

void init_keys(void) {
	#ifndef EMULATION_EN
  // TODO: initialize button ports (if needed)
  // Configure PORTC pins 10..14 for input to handle joystick events
  PORT_InitStructure.PORT_Pin =
      (PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14);
  PORT_InitStructure.PORT_OE = PORT_OE_IN;
  PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
  PORT_InitStructure.PORT_GFEN = PORT_GFEN_ON;
  PORT_Init(MDR_PORTC, &PORT_InitStructure);
	#else
	PORT_InitStructure.PORT_Pin = PORT_Pin_1;
	#endif // EMULATION_EN
}

// --- TODO: configure timers
void Init_Timer1() {
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_TIMER1;
  MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM1_CLK_EN;
  MDR_TIMER1->CNT = 0;
  MDR_TIMER1->PSG = (8000000 / 1000) - 1;
  MDR_TIMER1->ARR = 10000;
  MDR_TIMER1->IE = TIMER_IE_CNT_ARR_EVENT_IE;
  NVIC_EnableIRQ(Timer1_IRQn);
  MDR_TIMER1->CNTRL = TIMER_CNTRL_CNT_EN;
}

/*
void Init_Timer2() {
  MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_TIMER2;
  MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM2_CLK_EN;
  MDR_TIMER2->CNT = 0;
  MDR_TIMER2->PSG = 32000 -1;
  MDR_TIMER2->ARR = 30;
  MDR_TIMER2->IE = TIMER_IE_CNT_ARR_EVENT_IE;
  NVIC_EnableIRQ(Timer2_IRQn);
  MDR_TIMER2->CNTRL = TIMER_CNTRL_CNT_EN;
}
*/

#ifndef EMULATION_EN
// extern "C" {
// void Timer1_IRQHandler() {
//   MDR_TIMER1->STATUS = 0;
//   update_input();
// }
// }
#endif // EMULATION_EN
#if defined EMULATION_EN && defined BLINK
 extern "C" {
 void Timer1_IRQHandler() {
	if((MDR_TIMER1->STATUS)&(1<<1)){ // ARR_EVENT_IE
		MDR_TIMER1->STATUS &= ~(1<<1); // reset status flag (ARR_EVENT_IE)
		MDR_PORTF->RXTX ^= (1 << 1); // PF1(led) toggle
	}
 }
 }
#endif // EMULATION_EN && BLINK

void setup(void) {
  __disable_irq();
	#if defined EMULATION_EN && CPUSPEED
	CPU_init();
	#endif // EMULATION_EN
  init_leds();
  init_keys();
  setupDisplay();

  SysTick_Config(SystemCoreClock / 1000);
  
	#if defined EMULATION_EN && defined BLINK
	Init_Timer1();
	#else
	// Init_Timer1();
	#endif // EMULATION_EN && BLINK

  __enable_irq();
}

#endif  // SETUP_H
