#include "emu.h"

uint32_t ITM_SendCharInt (uint32_t ch){
	
	#ifdef EMU_DELAY
	uint32_t cnt;
	#endif // EMU_DELAY
	
	//ITM_SendChar('A'); // head
	
	if ((ITM->TCR & ITM_TCR_ITMENA_Msk)                  &&      /* ITM enabled */
      (ITM->TER & (1UL << 0)        )                    )     /* ITM Port #0 enabled */
	{
		while (ITM->PORT[0].u32 == 0);
		ITM->PORT[0].u32 = ch;
	}
	
	//ITM_SendChar('B'); // tail
	
	#ifdef EMU_DELAY
	for (cnt = 0; cnt <= EMU_DELAY; cnt++)
		;
	#endif // EMU_DELAY
	
	return (ch);
}

