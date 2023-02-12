/*
Examples:

#include "stdio.h"
#include "mt10t8.h"

    const uint8_t       char_array1[MT10T8_DIMENTION] = "0123456789";                                           					// Char string data.
    const uint8_t       char_array2[MT10T8_DIMENTION] = "AbcdEFJGhL";                                           					// Char string data.
    const uint8_t       char_array3[2 * MT10T8_DIMENTION] = "u-*_!^..A..\0";                                    					// Char string data.
    uint8_t             char_array4[2 * MT10T8_DIMENTION];                                         									// Char string data.

    const mt10t8_bus_t	mt10t8_bus = {PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD4_Pos * 4, \
    								  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD0_Pos * 4, \
									  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD1_Pos * 4, \
									  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD2_Pos * 4, \
									  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD3_Pos * 4, \
									  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD5_Pos * 4}; // Inicialization pt_A0, pt_D0, pt_D1, pt_D2, pt_D3, pt_WR1.

    const mt10t8_t		mt10t8_1 = {&mt10t8_bus, PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD6_Pos * 4};	// LCI description structure (pt_bus, pt_WR2).

    mt10t8_init(&mt10t8_1);                                                                                         // Initialization LCI. Result: unlock and clear LCI.
	Delay(1000);
    mt10t8_out_char_string(&mt10t8_1, &char_array1[0]);                                                             // Result: 0123456789
    Delay(1000);
    mt10t8_out_char_string(&mt10t8_1, &char_array2[0]);                                                             // Result: AbcdEFJGhL
    Delay(1000);
    mt10t8_out_char_string(&mt10t8_1, &char_array3[0]);                                                             // Result: u-*_!^..A..
    Delay(1000);
	sprintf(&char_array4[0], "%d", 0);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);                                                             // Result: 0
    Delay(1000);
	sprintf(&char_array4[0], "%d", -1);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);                                                             // Result: -1
    Delay(1000);
	sprintf(&char_array4[0], "%u", -1);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);                                                             // Result: 4294967295
    Delay(1000);
	sprintf(&char_array4[0], "%d", -1000000001);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);                                                             // Result(!): -100000000
    Delay(1000);
	sprintf(&char_array4[0], "%o", 15);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);                                                             // Result: 17
    Delay(1000);
	sprintf(&char_array4[0], "%x", 0xFFFFFFFF);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);                                                             // Result: FFFFFFFF
*/

#include <stdint.h>
#define MT10T8_DIMENTION    10          // MT10T8 character cell quantity.

typedef struct
{
	volatile    uint8_t     *pt_A0;     // Bit-band adress A0 pin signal.
	volatile    uint8_t     *pt_D0;     // Bit-band adress D0 pin signal.
	volatile    uint8_t     *pt_D1;     // Bit-band adress D1 pin signal.
	volatile    uint8_t     *pt_D2;     // Bit-band adress D2 pin signal.
	volatile    uint8_t     *pt_D3;     // Bit-band adress D3 pin signal.
	volatile    uint8_t     *pt_WR1;    // Bit-band adress WR1 pin signal.
} mt10t8_bus_t;                         // LCI bus pins structure type.

typedef struct
{
	            mt10t8_bus_t    *mt10t8_bus;
	volatile    uint8_t         *pt_WR2;    // Bit-band adress WR2 pin signal.
} mt10t8_t;                                 // LCI structure type.

void    mt10t8_init(mt10t8_t *pt_lci);
void    mt10t8_out_char_string(mt10t8_t *pt_lci, uint8_t *pt_char_string);
