// created 150220
#ifndef FLASH_H
#define FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "debug.h"
#include "delay.h"
#include "gpio.h"
#include "spi.h"

typedef struct
{
	uint8_t spi_port;
	uint16_t spi_prescaler;
	char	*cs;
} flash_hw_t;

void flash_main();

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// FLASH_H
