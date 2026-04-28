/*
 * LMX2581.c
 *
 *  Created on: 7. 4. 2026
 *      Author: Jenosek
 */
#include "LMX2581.h"


void PLL_write_reg(PLL_t* pll, SPI_TypeDef* SPI) {
  uint8_t* byte_value;
  uint8_t byte_value_deref;

	// Check SPI status
  if (!LL_SPI_IsEnabled(SPI)) {
    LL_SPI_Enable(SPI);
  }

  // Pull CE and LE high
  pll->CE_port->BSRR = pll->CE_pin;
  pll->LE_port->BSRR = pll->LE_pin;

  // Loop through all register values
  for (uint8_t i = 0; i < (N_REG+1); i++) {

  	// Pull LE down to enable register write
  	pll->LE_port->BRR = pll->LE_pin;

  	// Store pointer least significant 8 bits of selected register
  	uint32_t test_word = pll->Setup[i];
  	byte_value = (uint8_t*) &(pll->Setup[i]);

    // Split register values into 8b data, 32/8 = 4
  	for (uint8_t j = 4; j > 0; j--) {

  		// Avoid overflow of TX buffer
  		while(LL_SPI_IsActiveFlag_BSY(SPI) == LL_SPI_TX_FIFO_FULL) {}

  		// Send 8b value
      //byte_value = ((pll->Setup[i]) & (0xFF << ((j-1)*2))) >> ((j-1)*2);
      byte_value_deref = *(byte_value+(j-1));
      LL_SPI_TransmitData8(SPI, byte_value_deref);
  	}
  	// Wait until all data are transmitted from buffer
  	while (LL_SPI_IsActiveFlag_BSY(SPI)) {}

  	// Store data into PLL's register by pulling LE high
  	pll->LE_port->BSRR = pll->LE_pin;
  	LL_mDelay(1);

  	// After init. reset, wait 20 ms
  	if (!i) {
  	  LL_mDelay(20);
  	}
  }

  // End transmission by pulling CE low
  pll->CE_port->BRR = pll->CE_pin;

}



PLL_t PLL_init(GPIO_TypeDef* CE_port, uint32_t CE_pin, GPIO_TypeDef* LE_port, uint32_t LE_pin, uint32_t PLL_N, uint32_t PLL_NUM, uint32_t PLL_DEN, uint32_t out_div_en, uint32_t out_pwr) {

  PLL_t pll;


	// Prevent illegal register values on edit
	PLL_DEN &= 0x3FFFFF;                                // first 22 bits
	uint32_t PLL_NUM_MSB = ((PLL_NUM & 0x3FF000) >> 12);
	uint32_t PLL_NUM_LSB = (PLL_NUM & 0xFFF);
	//PLL_R &= 0xFF;
	PLL_N &= 0xFFF;
	PLL_N = (PLL_N > 6) ? PLL_N : 7;
	out_div_en &= 1;
	out_pwr = (out_pwr < 48) ? out_pwr : 47;

	// Activate frac mode (1st order) if needed
	uint32_t frac_order = (PLL_NUM) ? 1 : 0;

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
	  R5 | (out_div_en << 13),
	  R4,
	  R3 | (out_pwr << 12),
	  R2 | (PLL_DEN << 4),
	  R1 | (PLL_NUM_MSB << 15) | (frac_order << 12), //| (PLL_R << 4),
	  R0 | (PLL_N << 16) | (PLL_NUM_LSB << 4)
	  //If continuous freq. changes are required, follow LMX2581's datasheet
	};


	pll.Setup = setup_data;
	pll.CE_port = CE_port;
	pll.CE_pin = CE_pin;
	pll.LE_port = LE_port;
  pll.LE_pin = LE_pin;

	return pll;
}

uint32_t PLL_read_reg(PLL_t* pll, SPI_TypeDef* SPI, uint8_t reg_num) {
	uint8_t byte_value = 0;
	uint32_t data = 0;

	uint32_t readout_command = 0;
  uint8_t* p_readout_command;
	// Avoid illegal register numbers
	reg_num &= 0xF;

	// Prepare readout command
	readout_command = (0b100000 | reg_num);
	readout_command <<= 5;
	readout_command |= 0b110;
  p_readout_command =(uint8_t*) &readout_command;

  // Ensure SPI active state
	if (!LL_SPI_IsEnabled(SPI)) {
	  LL_SPI_Enable(SPI);
  }

	// Flush RX register
	while(LL_SPI_IsActiveFlag_RXNE(SPI)) {
		data = LL_SPI_ReceiveData8(SPI);
	}

	// Transmit Readout request
	// Pull CE high and LE low
	pll->CE_port->BSRR = pll->CE_pin;
	pll->LE_port->BRR = pll->LE_pin;

	// Split register values into 8b data, 32/8 = 4
	for (uint8_t i = 4; i > 0; i--) {

    // Wait until the FIFO is not full
	  while(LL_SPI_GetTxFIFOLevel(SPI) == LL_SPI_TX_FIFO_FULL) {}

	    // Send 8b value
	    byte_value = *(p_readout_command + (i-1));
	    LL_SPI_TransmitData8(SPI, byte_value);
	}
	// Wait until all data are transmitted from buffer
	while (LL_SPI_IsActiveFlag_BSY(SPI)) {}

	// Pull LE high to store data into register
	pll->LE_port->BSRR = pll->LE_pin;
	//LL_mDelay(1);
	//pll->LE_port->BRR = pll->LE_pin;

  data = 0;
	byte_value = 0;
	LL_SPI_SetRxFIFOThreshold(SPI, LL_SPI_RX_FIFO_TH_QUARTER);
	//Wait until transmission is complete (TX buffer is empty)
	//while (!LL_SPI_IsActiveFlag_TXE(SPI)) {}

	// Read response while transmitting dummy data (R6 again) to supply CLK
	// Save 8 bit values to 32 bit variable
	for (uint8_t i = 4; i > 0; i--) {
		// Transmit dummy data to supply CLK for readback
		while(LL_SPI_GetTxFIFOLevel(SPI) == LL_SPI_TX_FIFO_FULL) {}

		// Send 8b value
		byte_value = *(p_readout_command + (i-1));
		LL_SPI_TransmitData8(SPI, byte_value);

		// Wait for data to arrive to RX buffer (not empty)
	  while (!LL_SPI_IsActiveFlag_RXNE(SPI)) {}
    //while(LL_SPI_GetRxFIFOLevel(SPI) == LL_SPI_RX_FIFO_EMPTY) {}

	  // Read buffer
	  byte_value = LL_SPI_ReceiveData8(SPI);
	  data = ((data << 8) | byte_value);
	}
  LL_mDelay(1);
	// Wait until all data are transmitted from buffer
	while (LL_SPI_IsActiveFlag_BSY(SPI)) {}
	//pll->LE_port->BSRR = pll->LE_pin;
	pll->CE_port->BRR = pll->CE_pin;

	return data;
}



