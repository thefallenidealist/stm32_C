#ifndef NRF_H
#define NRF_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> 	// atoi
#include <stdbool.h>

#ifdef STM32F10X_MD
	#include "stm32f10x_rcc.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_spi.h"
#endif
#ifdef STM32F4XX
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_spi.h"
#endif
#include "spi.h"

#define SPI1_PORT	GPIOA
//#define SPI1_RCC	RCC_APB2Periph_GPIOA	// F1
#define SPI1_RCC	RCC_AHB1Periph_GPIOA	// F4
#define SPI1_SCK	GPIO_Pin_5
#define SPI1_MISO	GPIO_Pin_6
#define SPI1_MOSI	GPIO_Pin_7

#define SPI2_PORT	GPIOB
#define SPI2_SCK	GPIO_Pin_13
#define SPI2_MISO	GPIO_Pin_14
#define SPI2_MOSI	GPIO_Pin_15

// GPIO
#ifdef STM32F4XX
	#define RCCA	RCC_AHB1Periph_GPIOA
	#define RCCB	RCC_AHB1Periph_GPIOA
	#define RCCC	RCC_AHB1Periph_GPIOA
	#define RCCD	RCC_AHB1Periph_GPIOA

/*
// nema potrebe
	#define PIN0	GPIO_Pin_0
	#define PIN1	GPIO_Pin_1
	#define PIN2	GPIO_Pin_2
	#define PIN3	GPIO_Pin_3
	#define PIN4	GPIO_Pin_4
	#define PIN5	GPIO_Pin_5
	#define PIN6	GPIO_Pin_6
	#define PIN7	GPIO_Pin_7
	#define PIN8	GPIO_Pin_8
	#define PIN9	GPIO_Pin_9
	#define PIN10	GPIO_Pin_10
	#define PIN11	GPIO_Pin_11
	#define PIN12	GPIO_Pin_12
	#define PIN13	GPIO_Pin_13
	#define PIN14	GPIO_Pin_14
	#define PIN15	GPIO_Pin_15
	*/
#endif

/*
typedef enum
{
	IN = 0,
	OUT = 1
} direction_t;
*/

/*
typedef struct
{
	uint8_t spi_number;
	char	cs_port;
	char	ce_port;
	char	irq_port;
	uint8_t cs_pin;
	uint8_t ce_pin;
	uint8_t irq_pin;
} nRF_pins_t;
*/

// kokos ili jaje
//typedef	int (*pFunc)(nRF_t *self);

typedef	struct nRF_t nRF_t;		// prototip structa nRF_t
//typedef	int (*pfunc)(nRF_t *self);	// pointer na funkciju
//typedef void (*pfunc_print)(nRF_t *self);

typedef struct 
{
	//uint32_t	port;
	GPIO_TypeDef 	*port;
	uint16_t	pin;
} gpio_pin;

//typedef struct
// nema typedefa jer ga ima gore, kasnije u kodu se moze pozivat bez "struct" (typedef applied)
struct nRF_t
{
	//nRF_pins_t	pins;	// nasljedjivanje, wheee
	char	*spi;
	char	*cs;
	char	*ce;
	char	*irq;
	char	*name;
	//pfunc	init;
	//pfunc	print;
	//pfunc_print print;
	
//} nRF_t;
};

//typedef enum
enum
{
	//EXIT_SUCCESS,	// ima vec u stdlib
	EXIT_FAILED = -99,
	EXIT_WRONG_SPI,
	EXIT_WRONG_SPI_NUMBER,
	EXIT_WRONG_GPIO_PORT,
	EXIT_WRONG_GPIO_PIN,
	EXIT_WRONG_GPIO_DIRECTION
//} NRF_EXIT_CODES;
};

//void spi_init(uint8_t spi_number);
//int parse_spi(const char *arg);
//int parse_gpio(const char *name, const char *arg, direction_t direction);
//void nRF_constructor(nRF_t *self);
//int nRF_main();

// javne, izvana dostupne funkcije
//int nRF_init(nRF_t *self);
nRF_t *nRF_new(const char *name);
//nRF_t *nRF_new(const char *name);
//void nRF_print(nRF_t *self);
void nRF_main();

#endif
