/*
 * LMX2581_config.h
 *
 *  Created on: 3. 3. 2026
 *      Author: Jenosek
 */

#ifndef INC_LMX2581_CONFIG_H_
#define INC_LMX2581_CONFIG_H_

// Description: Register values needed for setup of LMX2581 PLL. In case of more than one PLLs on PCB, this can serve as common setup and minor changes can be
//// edited afterwards.

// NOTE: values of register area can be edited unless marked as "x" or "A" (address).
// For correct functionality, leave PLL_DEN, PLL_NUM and PLL_N as zeros.

// Bits are sorted from MSB to LSB (address), load into the register by MSB first

  // R0
  //// ID 			       1b
  #define R0_ID 0

  //// FRAC_DITHER     2b
  ////// 0 - weak, 1 - medium, 2 - strong, 3 - disabled
  #define R0_DITHER 0x3

  //// NO_FCAL         1b
  ////// Frequency calibration upon R0 write, 0 - calibrate, 1 - do not calibrate
  #define R0_NO_FCAL 0

  //// PLL_N          12b
  ////// has to be >6
  //---<edited by setup function>---//
  #define R0_PLL_N 0

  //// PLL_NUM(lower) 12b
  //---<edited by setup function>---//
  #define R0_PLL_NUM 0

  //// A               4b
  #define R0_ADDRESS 0

  #define R0 ((uint32_t)(R0_ID << 31) | (R0_DITHER << 29) | (R0_NO_FCAL << 28) | (R0_PLL_N << 16) | (R0_PLL_NUM << 4) | R0_ADDRESS)



  // R1
  //// CPG 			       5b
  ////// Charge pump current 110 uA multiplier, determined by sim
  #define R1_CPG 27 //approx 3mA

  //// VCO_SEL         2b
  ////// Select VCO from bank, determined by sim
  #define R1_VCO_SEL 1 //VCO 2

  //// PLL_NUM(x)     10b  (High 10 bit)
  //---<edited by setup function>---//
  #define R1_PLL_NUM 0

  //// FRAC_ORDER      3b
  ////// If frequency step is too coarse, activate fractional engine

  #define R1_FRAC_ORDER 0 //Integer mode

  //// PLL_R(x) -  8b
  #define R1_PLL_R 10
  //// A               4b
  #define R1_ADDRESS 1

  #define R1 ((uint32_t)((R1_CPG << 27) | (R1_VCO_SEL << 25) | (R1_PLL_NUM << 15) | (R1_FRAC_ORDER << 12) | (R1_PLL_R << 4) | R1_ADDRESS))



  // R2
  //// x               2b

  //// OSC_2		   1b
  ////// Enable Input clock frequency doubler
  #define R2_OSC_2X 0

  //// x			   1b

  //// CPP             1b
  ////// Charge Pump Polarity, 0 - Positive, 1 - Negative (default), NOTE: internal VCO has negative tuning gain
  #define R2_CPP 1

  //// x               1b
  #define R2_X 1

  //// PLL_DEN(x)     22b
  //---<edited by setup function>---//
  #define R2_PLL_DEN 0

  //// A               4b
  #define R2_ADDRESS 0b10

  #define R2 ((uint32_t)(R2_OSC_2X << 29) | (R2_CPP << 27) | (R2_X << 26) | (R2_PLL_DEN << 4) | R2_ADDRESS)



  // R3
  //// x               9b
  #define R3_X (uint32_t) 0b001000000

  //// VCO_DIV		     5b
  ////// Output divider, states 0-18 represents dividers from 2 to 38. Possible to bypass by OUTx_MUX
  #define R3_VCO_DIV (uint32_t) 0 //Divide by 2 or bypass by setting OUTx_MUX

  //// OUTB_PWR  	     6b
  ////// Output power, 0-47 (min-max, values dependent on design)
  //---<edited by setup function>---//
  #define R3_OUTB_PWR (uint32_t) 0
  //// OUTA_PWR        6b
  #define R3_OUTA_PWR (uint32_t) 0

  //// OUTB_PD         1b
  ////// Output state, 0 - normal operation, 1 - powered down
  #define R3_OUTB_PD (uint32_t) 0
  //// OUTA_PD         1b
  #define R3_OUTA_PD (uint32_t) 1

  //// A               4b
  #define R3_ADDRESS 0b11

  #define R3 ((R3_X << 23) | (R3_VCO_DIV << 18) | (R3_OUTB_PWR << 12) | (R3_OUTA_PWR << 6) | (R3_OUTB_PD << 5) | (R3_OUTA_PD << 4) | R3_ADDRESS)



  // R4
  //// PFD_DLY         3b
  ////// Phase Detector Delay, for integer mode use default 0
  ////// Consider longer delays when 3rd order modulator with dithering is active
  #define R4_PFD_DLY 0

  //// FL_FRCE		     1b
  ////// Force Fast Lock Conditions,
  #define R4_FL_FRCE 0 //disabled

  //// FL_TOC   	    12b
  ////// Fastlock Timeout Counter
  #define R4_FL_TOC 0 //disabled

  //// FL_CPG          5b
  ////// Fastlock Charge Pump Gain, 0 - tristate, 1:31
  #define R4_FL_CPG 0 //not used, left in tri-state                                                     <possible error?>

  //// x               1b

  //// CPG_BLEED       6b
  ////// To lower integer boundary spur
  ////// Basic setting: 0
  ////// Advanced:
  //////// Frac_order |      CPG     | CPG_BLEED
  ////////    <2      |       x      |    0
  ////////     x      |      <4      |    0
  ////////    >1      | 4 <= CPG <12 |    2
  ////////    >1      |   12 <= CPG  |    4                                                             <possible error?>
  #define R4_CPG_BLEED 0

  //// A               4b
  #define R4_ADDRESS 0b100
  #define R4 ((uint32_t)(R4_PFD_DLY << 29) | (R4_FL_FRCE << 28) | (R4_FL_TOC << 16) | (R4_FL_CPG << 11) | (R4_CPG_BLEED << 4) | R4_ADDRESS)



  // R5
  //// x               7b
  //// OUT_LDEN		     1b
  ////// Disable mux output until PLL locked
  #define R5_OUT_LDEN 1

  //// OSC_FREQ   	   3b
  ////// OSCin Frequency for VCO Calibration,
  #define R5_OSC_FREQ 0 //as CLK = 10 MHz

  //// BUFEN_DIS       1b
  ////// Disables BUFEN pin
  #define R5_BUFEN_DIS 0 // Keep HW control of RF output via BUFEN

  //// x               3b

  //// VCO_SEL_MODE    2b
  ////// 0 - auto, 1 - VCO_SEL, 2 - forced VCO_SEL
  #define R5_VCO_SEL_MODE 1

  //// OUTB_MUX        2b
  ////// Select output: 0 - f_VCO, 1 - output divider, f_Fin
  //---<edited by setup function>---//
  #define R5_OUTB_MUX 0
  //// OUTA_MUX        2b
  #define R5_OUTA_MUX 0

  //// 0_DLY           1b
  ////// 0 delay mode, has positive effect phase of signal when VCO divider is used
  //////Warning: advanced, as setup requires additional procedures
  #define R5_0_DLY 0

  //// MODE            2b
  ////// Operating mode
  #define R5_MODE 0 // Full chip mode

  //// PWDN_MODE       3b
  #define R5_PWDN_MODE 0 // All powered up

  //// RESET           1b
  #define R5_RESET 0 // Regs and SM operational, reset automatically toggles this back to zero

  //// A               4b
  #define R5_ADDRESS 0b101

  //#define R5
  #define R5 ((uint32_t)(R5_OUT_LDEN << 24) | (R5_OSC_FREQ << 21) | (R5_BUFEN_DIS << 20) | (R5_VCO_SEL_MODE << 15) | (R5_OUTB_MUX << 13) | (R5_OUTA_MUX << 11) | (R5_0_DLY << 10) | (R5_MODE << 8) | (R5_PWDN_MODE << 5) | (R5_RESET << 4) | R5_ADDRESS)



  // R6
  //// x               1b

  //// RD_DIAGNOSTICS 20b
  ////// Readback Diagnostics, consult datasheet for more information
  //#define R6_RD_DIAGNOSTICS 0

  //// x   	           2b
  #define R6_X 0b10

  //// RDADDR          4b
  ////// Write number of register to be read
  #define R6_RDADDR 0

  //// uWIRE_LOCK      1b
  #define R6_uWIRE_LOCK 0 // Normal operation

  //// A               4b
  #define R6_ADDRESS 0b110

  #define R6 ((uint32_t)(R6_X << 9) | (R6_RDADDR << 5) | (R6_uWIRE_LOCK << 4) | R6_ADDRESS)



  // R7
  //// x               1b

  ////// Modes  of pins (FLout - fastlock output, MUXOUT and LD)
  //// FL_PINMODE      3b
  #define R7_FL_PINMODE 0 // Tristate
  //// MUXOUT_PINMODE  3b
  #define R7_MUXOUT_PINMODE 1 //Push-Pull
  //// LD_PINMODE      3b
  #define R7_LD_PINMODE 1 //Push-Pull

  ////// Inverted logic
  //// FL_INV          1b
  #define R7_FL_INV 0 //Normal Operation
  //// MUX_INV         1b
  #define R7_MUX_INV 0
  //// LD_INV          1b
  #define R7_LD_INV 0

  ////// State for Status Pins
  //// FL_SELECT	     5b
  #define R7_FL_SELECT 0 //GND
  //// MUXOUT_SELECT   5b
  #define R7_MUXOUT_SELECT 4 //Readback
  //// LD_SELECT       5b
  #define R7_LD_SELECT 3 // Lock detect (phase and tuning voltage measurement)

  //// A               4b
  #define R7_ADDRESS 0b111

  #define R7 ((uint32_t)(R7_FL_SELECT << 26) | (R7_FL_PINMODE << 23) | (R7_FL_INV << 22) | (R7_MUXOUT_SELECT << 17) | (R7_MUX_INV << 16) | (R7_MUXOUT_PINMODE << 13) | (R7_LD_SELECT << 8) | (R7_LD_INV << 7) | (R7_LD_PINMODE << 4) | R7_ADDRESS)



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
  #define R13_DLD_ERR_CNT 4 // for phase det. freq. F_PD < 80 MHz, otherwise experiment

  //// DLD_PASS_CNT	  10b
  #define R13_DLD_PASS_CNT 32 // for F_PD < 80 MHz, otherwise experiment

  //// DLD_TOL   	     3b
  #define R13_DLD_TOL 5 // F_PD <= 30 MHz

  //// x              11b
  #define R13_X 0b10000010000

  //// A               4b
  #define R13_ADDRESS 0b1101

  #define R13 ((uint32_t)(R13_DLD_ERR_CNT << 28) | (R13_DLD_PASS_CNT << 18) | (R13_DLD_TOL << 15) | (R13_X << 4) | R13_ADDRESS)



  // R15
  //// x              19b
  #define R15_X 1000011111111

  //// VCO_CAP_MAN	   1b
  ////// Manual VCO Band Select
  #define R15_VCO_CAP_MAN 0 // R15_VCO_CAPCODE set as initial starting point of calibration

  //// VCO_CAPCODE 	   8b
  #define R15_VCO_CAPCODE 100 // 2135 + (2720 - 2135)/(256/100) = 2363.5 MHz as initial cal. freq.

  //// A               4b
  #define R15_ADDRESS 0b1111

  #define R15 ((uint32_t)(R15_X << 13) | (R15_VCO_CAP_MAN << 12) | (R15_VCO_CAPCODE << 4) | R15_ADDRESS)

#endif /* INC_LMX2581_CONFIG_H_ */
