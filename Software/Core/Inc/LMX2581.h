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

typedef struct {
	uint32_t* Setup;
	GPIO_TypeDef* NSS_port;
	uint8_t NSS_pin;
} PLL_t;

PLL_t PLL_init(GPIO_TypeDef* NSS_port, uint8_t NSS_pin, uint32_t PLL_DEN, uint32_t PLL_NUM, uint32_t PLL_R, uint32_t PLL_N);

void PLL_write_reg(PLL_t* pll, SPI_TypeDef *spi);


#endif /* INC_LMX2581_H_ */
