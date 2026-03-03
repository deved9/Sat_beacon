/*
 * LMX2581_config.h
 *
 *  Created on: 3. 3. 2026
 *      Author: Jenosek
 */

#ifndef INC_LMX2581_CONFIG_H_
#define INC_LMX2581_CONFIG_H_

/* Registers
 **************************************/

// NOTE: values of register area can be edited unless marked as "x" or "A" (address)
// Bits are sorted from MSB to LSB (address), load into the register by MSB first

  // R0
  //// ID 			   1b
  //// FRAC_DITHER     2b
  //// NO_FCAL         1b
  //// PLL_N          12b
  //// PLL_NUM        12b
  //// A               4b

  #define R0 0b00000000000000000000000000000000


  // R1
  //// CPG 			   5b
  //// VCO_SEL         2b
  //// PLL_NUM        10b  (High 10 bit)
  //// FRAC_ORDER      3b
  //// PLL_R           8b
  //// A               4b

  #define R1 0b00000000000000000000000000000001


  // R2
  //// x               2b
  //// OSC_2		   1b
  //// x			   1b
  //// CPP             1b
  //// x               1b
  //// PLL_DEN        22b
  //// A               4b

  #define R2 0b00000100000000000000000000000010


  // R3
  //// x               9b
  //// VCO_DIV		   5b
  //// OUTB_PWR  	   6b
  //// OUTA_PWR        6b
  //// OUTB_PD         1b
  //// OUTA_PD         1b
  //// A               4b

  #define R3 0b00100000000000000000000000000011

  // R4
  //// PFD_DLY         3b
  //// FL_FRCE		   1b
  //// FL_TOC   	  12b
  //// FL_CPG          5b
  //// x               1b
  //// CPG_BLEED       6b
  //// A               4b

  #define R4 0b00000000000000000000000000000100

  // R5
  //// x               7b
  //// OUT_LDEN		   1b
  //// OSC_FREQ   	   3b
  //// BUFEN_DIS       1b
  //// x               3b
  //// VCO_SEL_MODE    2b
  //// OUTB_MUX        2b
  //// OUTA_MUX        2b
  //// 0_DLY           1b
  //// MODE            2b
  //// PWDN_MODE       3b
  //// RESET           1b
  //// A               4b

  #define R5 0b00000000000000000000000000101

  // R6
  //// x               1b
  //// RD_DIAGNOSTICS 20b
  //// x   	           2b
  //// RDADDR          4b
  //// uWIRE_LOCK      1b
  //// A               4b

  #define R6 0b0000000000000000000010000000110

  // R7
  //// x               1b
  //// FL_SELECT	   5b
  //// OSC_FREQ   	   3b
  //// FL_INV          1b
  //// MUXOUT_SELECT   5b
  //// MUX_INV         1b
  //// MUXOUT_PINMODE  3b
  //// LD_SELECT       5b
  //// LD_INV          1b
  //// LD_PINMODE      3b
  //// A               4b

  #define R7 0b00000000000000000000000000000111

  // R8
  //// x              28b
  //// A               4b

  #define R8 0b00100000011111011101101111111000

  // R9
  //// x              28b
  //// A               4b

  #define R9 0b00000011110001111100000000111001

  // R10
  //// x              28b
  //// A               4b

  #define R10 0b00100001000000000101000011001010

  // R13
  //// DLD_ERR_CNT     4b
  //// DLD_PASS_CNT	  10b
  //// DLD_TOL   	   3b
  //// x              11b
  //// A               4b

  #define R13 0b00000000000000000100000100001101

  // R15
  //// x              19b
  //// VCO_CAP_MAN	   1b
  //// VCO_CAPCODE 	   8b
  //// A               4b

  #define R15 0b00000010000111111110000000001111

#endif /* INC_LMX2581_CONFIG_H_ */
