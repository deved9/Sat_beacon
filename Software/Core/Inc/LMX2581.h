/*
 * LMX2581.h
 *
 *  Created on: 3. 3. 2026
 *      Author: Jenosek
 */

#ifndef INC_LMX2581_H_
#define INC_LMX2581_H_

#define N_REG 13
#define PASS_BY_DMA FALSE

#include "LMX2581_config.h"
#include <stdint.h>
#include "stm32c0xx_ll_spi.h"
#include "stm32c0xx_ll_utils.h"
#include "stm32c0xx_ll_gpio.h"

typedef struct {
	uint32_t Setup[N_REG + 1];
	GPIO_TypeDef* CE_port;
	uint32_t CE_pin;
	GPIO_TypeDef* LE_port;
  uint32_t LE_pin;
} PLL_t;

PLL_t PLL_init(GPIO_TypeDef* CE_port, uint32_t CE_pin, GPIO_TypeDef* LE_port, uint32_t LE_pin, uint32_t PLL_N, uint32_t PLL_NUM, uint32_t PLL_DEN, uint32_t out_div_en, uint32_t out_pwr);

void PLL_write_reg(PLL_t* pll, SPI_TypeDef* spi);
uint32_t PLL_read_reg(PLL_t* pll, SPI_TypeDef* SPI, uint8_t reg_num);


#endif /* INC_LMX2581_H_ */
