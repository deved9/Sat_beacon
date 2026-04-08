/*
 * LMX2581.c
 *
 *  Created on: 7. 4. 2026
 *      Author: Jenosek
 */
#include "LMX2581.h"



PLL_t PLL_init(GPIO_TypeDef* NSS_port, uint8_t NSS_pin, uint32_t PLL_DEN, uint32_t PLL_NUM, uint32_t PLL_R, uint32_t PLL_N) {

    PLL_t pll;
	// Prevent illegal register values on edit
	PLL_DEN &= 0x3FFFFF;                                // first 22 bits
	uint32_t PLL_NUM_MSB = ((PLL_NUM & 0x3FF000) >> 12);
	uint32_t PLL_NUM_LSB = (PLL_NUM & 0xFFF);
	PLL_R &= 0xFF;
	PLL_N &= 0xFFF;

	// Create 32 bit array for PLL's initial setup
	//// Use common setup, differences change by bit operations
	uint32_t setup_data[N_REG + 1] = {
	  R5 | (1 << 4), // Causes initial SW reset
	  R15,
	  R13,
	  R10,
	  R9,
	  R8,
	  R7,
	  R6,
	  R5,
	  R4,
	  R3,
	  R2 | (PLL_DEN << 4),
	  R1 | (PLL_NUM_MSB << 15) | (PLL_R << 4),
	  R0 | (PLL_N << 16) | (PLL_NUM_LSB << 4)
	  //If continuous freq. changes are required, follow LMX2581's datasheet
	};

	pll.Setup = setup_data;
	pll.NSS_port = NSS_port;
	pll.NSS_pin = NSS_pin;
	return pll;
}

void PLL_write_reg(PLL_t* pll, SPI_TypeDef* SPI) {
  if (!LL_SPI_IsEnabled(SPI)) {
    LL_SPI_Enable(SPI);
  }

  // Enable NSS
  pll->NSS_port->BSRR = (1 << pll->NSS_pin);


  uint8_t* byte_value;
  // Loop through all register values
  for (uint8_t i = 0; i < (N_REG + 1); i++) {
  	// Store pointer to LSB of selected register
  	byte_value = (uint8_t*) &(pll->Setup[i]);

  	// Wait until TX buffer clears out
    while (!LL_SPI_IsActiveFlag_TXE(SPI)) {}

    // Split register values into 8b data, 32/8 = 4
  	for (uint8_t j = 4; j > 0; j--) {

  		// Wait until the FIFO is not full
  		while(LL_SPI_GetTxFIFOLevel(SPI) == LL_SPI_TX_FIFO_FULL) {}

  		// Send 8b value
      //byte_value = ((pll->Setup[i]) & (0xFF << ((j-1)*2))) >> ((j-1)*2);

      LL_SPI_TransmitData8(SPI, *(byte_value+(i-1)));
  	}

  	// After init. reset, wait 20 ms
  	if (!i) {
  	  LL_mDelay(20);
  	}

  }
  //Wait until transmission is complete
  while (!LL_SPI_IsActiveFlag_TXE(SPI)) {}


  // Disable NSS
  pll->NSS_port->BRR = (1 << pll->NSS_pin);
}




