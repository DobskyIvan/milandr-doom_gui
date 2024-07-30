#ifndef __EMU_h__
#define __EMU_h__

#include "MDR32Fx.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t ITM_SendCharInt (uint32_t ch);

//#define EMULATION_EN // set var in project settings
	
#define EMU_DELAY 3500
	
#ifdef __cplusplus
} // extern "C" block end
#endif
	
#endif // __EMU_h__
