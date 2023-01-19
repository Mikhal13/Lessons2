/*
Examples:
    lci_mt10t8_init_t   lci_bus;                                                          // LCI bus description structure.

    uint8_t             *lci1;                                                            // Pointer to lci1 select pin.
    uint32_t            data = 0;                                                         // Data.
    uint8_t             char_array1[MT10T8_DIMENTION] = "0123456789";                     // Char string data.
    uint8_t             char_array2[MT10T8_DIMENTION] = "AbcdEFJGhL";                     // Char string data.
    uint8_t             char_array1[MT10T8_DIMENTION] = "-*_!^     ";                     // Char string data.

    uint8_t             segment_code_array[MT10T8_DIMENTION];                             // Segment code string data.

    lci_pins.A0 =  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD4_Pos * 4;                       // Initialization lci bus description structure.
    lci_pins.D0 =  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD0_Pos * 4;
    lci_pins.D1 =  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD1_Pos * 4;
    lci_pins.D2 =  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD2_Pos * 4;
    lci_pins.D3 =  PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD3_Pos * 4;
    lci_pins.WR1 = PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD5_Pos * 4;
    lci1 =         PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD6_Pos * 4;

    lci_mt10t8_bus_select(&lci_bus);                                                          // Initialization LCI bus.
    lci_mt10t8_init(lci1);                                                                    // Initialization LCI.                              Result: unlock and clear LCI.
    lci_mt10t8_clear(lci1);                                                                   // Initialization LCI.                              Result: clear LCI.

    lci_mt10t8_out_char_string(lci1; &char_array);                                             // Output lci_string to LCI.                        Result: '9876543210' on LCI.
    HAL_Delay(5);
    lci_mt10t8_out_char_string(lci1; &char_array2);                                            // Output lci_string to LCI.                        Result: 'LhGJFEcdbA' on LCI. LhGJFEcdbA
    HAL_Delay(15);
    lci_mt10t8_out_char_string(lci1; &char_array3);                                            // Output lci_string to LCI.                        Result: '     ^!_*-' on LCI.
    HAL_Delay(10);

    lci_mt10t8_out_bin(lci1; &((uint8_t)data));                                               // Output low byte lci_data to LCI.                 Result: 'b 00000000' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_unsign_dec(lci1; &data);                                                   // Output lci_data to LCI in unsign decimal format. Result: '         0' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_sign_dec(lci1; &data);                                                     // Output lci_data to LCI in sign decimal format.   Result: '         0' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_unsign_hex(lci1; &data);                                                   // Output lci_data to LCI in unsign hex format.     Result: 'h        0' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_sign_hex(lci1; &data);                                                     // Output lci_data to LCI in sign hex format.       Result: 'h        0' on LCI.
    HAL_Delay(2);

    data = 0xFFFFFFFF;
    lci_mt10t8_out_bin(lci1; &((uint8_t)data));                                               // Output low byte lci_data to LCI.                 Result: 'b 11111111' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_unsign_dec(lci1; &data);                                                   // Output lci_data to LCI in unsign decimal format. Result: '4294836225' on LCI.
    HAL_Delay(5);
    lci_mt10t8_out_sign_dec(lci1; &data);                                                     // Output lci_data to LCI in sign decimal format.   Result: '        -1' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_unsign_hex(lci1; &data);                                                   // Output lci_data to LCI in unsign hex format.     Result: 'h FFFFFFFF' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_sign_hex(lci1; &data);                                                     // Output lci_data to LCI in sign hex format.       Result: 'h       -1' on LCI.
    HAL_Delay(2);

    data = 0x80000000;
    lci_mt10t8_out_unsign_dec(lci1; &data);                                                   // Output lci_data to LCI in unsign decimal format. Result: '2147483648' on LCI.
    HAL_Delay(5);
    lci_mt10t8_out_sign_dec(lci1; &data);                                                     // Output lci_data to LCI in sign decimal format.   Result: '2147483648' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_unsign_hex(lci1; &data);                                                   // Output lci_data to LCI in unsign hex format.     Result: 'h 80000000' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_sign_hex(lci1; &data);                                                     // Output lci_data to LCI in sign hex format.       Result: 'h 80000000' on LCI.
    HAL_Delay(2);

    data = 0x80000001;
    lci_mt10t8_out_unsign_dec(lci1; &data);                                                   // Output lci_data to LCI in unsign decimal format. Result: '2147483649' on LCI.
    HAL_Delay(5);
    lci_mt10t8_out_sign_dec(lci1; &data);                                                     // Output lci_data to LCI in sign decimal format.   Result: '-999999999' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_unsign_hex(lci1; &data);                                                   // Output lci_data to LCI in unsign hex format.     Result: 'h 80000001' on LCI.
    HAL_Delay(2);
    lci_mt10t8_out_sign_hex(lci1; &data);                                                     // Output lci_data to LCI in sign hex format.       Result: 'h-7FFFFFFF'  on LCI.
    HAL_Delay(2);

    data = 1234567890;
    lci_mt10t8_convert_dec_to_char_string(&data; &char_array);                                // Convert data from hex to char string.            Result: char_array = 'h 800000FF'.
    lci_mt10t8_convert_char_string_to_segment_code_string(&char_array; &segment_code_array);  // Convert string from char to segment_code.        Result: segment_code_array = segment code of 'h 800000FF' char string.
    lci_mt10t8_out_segment_code_string(lci1; &segment_code__array);                           // Output segment_code_string to LCI.               Result: '1234567890' on LCI.
    HAL_Delay(2);
*/

#include <stdint.h>
#define LCI_MT10T8_DIMENTION    10      // MT10T8 character cell quantity.

typedef struct
{
	volatile    uint8_t     *pt_A0;    // Bit-band adress A0 pin signal.
	volatile    uint8_t     *pt_D0;    // Bit-band adress D0 pin signal.
	volatile    uint8_t     *pt_D1;    // Bit-band adress D1 pin signal.
	volatile    uint8_t     *pt_D2;    // Bit-band adress D2 pin signal.
	volatile    uint8_t     *pt_D3;    // Bit-band adress D3 pin signal.
	volatile    uint8_t     *pt_WR1;   // Bit-band adress WR1 pin signal.
} lci_mt10t8_bus_t;                    // LCI bus pins structure type.

void    lci_mt10t8_convert_bin_to_char_string(uint8_t *pt_data, uint8_t *pt_char_string);
void    lci_mt10t8_convert_unsign_dec_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string);
void    lci_mt10t8_convert_sign_dec_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string);
void    lci_mt10t8_convert_unsign_hex_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string);
void    lci_mt10t8_convert_sign_hex_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string);

void    lci_mt10t8_convert_char_string_to_segment_code_string(uint8_t *pt_char_string, uint8_t *pt_segment_code_string);
void    lci_mt10t8_convert_bin_to_segment_code_string(uint8_t *pt_data, uint8_t *pt_segment_code_string);
void    lci_mt10t8_convert_unsign_dec_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string);
void    lci_mt10t8_convert_sign_dec_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string);
void    lci_mt10t8_convert_unsign_hex_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string);
void    lci_mt10t8_convert_sign_hex_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string);

void    lci_mt10t8_bus_select(lci_mt10t8_bus_t *pt_lci_bus);
void    lci_mt10t8_init(uint8_t *pt_lci_select);
void    lci_mt10t8_clear(uint8_t *pt_lci_select);
void    lci_mt10t8_out_segment_code_string(uint8_t *pt_lci_select, uint8_t *pt_segment_code_string);
void    lci_mt10t8_out_char_string(uint8_t *pt_lci_select, uint8_t *pt_char_string);
void    lci_mt10t8_out_bin(uint8_t *pt_lci_select, uint8_t *pt_data);
void    lci_mt10t8_out_unsign_dec(uint8_t *pt_lci_select, uint32_t *pt_data);
void    lci_mt10t8_out_sign_dec(uint8_t *pt_lci_select, uint32_t *pt_data);
void    lci_mt10t8_out_unsign_hex(uint8_t *pt_lci_select, uint32_t *pt_data);
void    lci_mt10t8_out_sign_hex(uint8_t *pt_lci_select, uint32_t *pt_data);
