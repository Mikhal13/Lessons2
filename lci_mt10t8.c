#include "lci_mt10t8.h"

#define SIZE_OF_BIN			        8		    // 8 character cell for binary number.
#define SIZE_OF_DEC			        10		    // 10 character cell for decimal number.
#define SIZE_OF_HEX			        8		    // 8 character cell for hexadecimal number.
#define MAX_POSITIVE_VALUE	        0x80000000
#define MAX_NEGATIVE_DEC_VALUE	    999999999   // -999999999 - the minimum value that can be displayed on the 10 character cell LCI.
#define LOW_TETRAD_MSK	            0x0F        // Low tetrad extraction mask.
#define DEC_NUM_SYS_BASE            10          // The decimal number system base.

#define SEGMENT_CODE_0              0xEE
#define SEGMENT_CODE_1              0x60
#define SEGMENT_CODE_2              0x2F
#define SEGMENT_CODE_3              0x6D
#define SEGMENT_CODE_4              0xE1
#define SEGMENT_CODE_5              0xCD
#define SEGMENT_CODE_6              0xCF
#define SEGMENT_CODE_7              0x68
#define SEGMENT_CODE_8              0xEF
#define SEGMENT_CODE_9              0xED
#define SEGMENT_CODE_A              0xEB
#define SEGMENT_CODE_b              0xC7
#define SEGMENT_CODE_c              0x07
#define SEGMENT_CODE_d              0x67
#define SEGMENT_CODE_E              0x8F
#define SEGMENT_CODE_F              0x8B
#define SEGMENT_CODE_MINUS          0x01
#define SEGMENT_CODE_DEGREE         0xA9
#define SEGMENT_CODE_J              0x6E
#define SEGMENT_CODE_G              0xCE
#define SEGMENT_CODE_h              0xC3
#define SEGMENT_CODE_L              0x86
#define SEGMENT_CODE_n              0x43
#define SEGMENT_CODE_o              0x47
#define SEGMENT_CODE_P              0xAB
#define SEGMENT_CODE_r              0x03
#define SEGMENT_CODE_U              0xE6
#define SEGMENT_CODE_X              0xE3
#define SEGMENT_CODE_Y              0xE5
#define SEGMENT_CODE_EQUAL          0x05
#define SEGMENT_CODE_UNDERLINE      0x04
#define SEGMENT_CODE_EXCLAMATION    0x70
#define SEGMENT_CODE_ROOF           0x41
#define SEGMENT_CODE_SPASE          0x00

static   lci_mt10t8_bus_t    *pt_bus;

void    lci_mt10t8_bus_select(lci_mt10t8_bus_t *pt_lci_bus)
{
    pt_bus = pt_lci_bus;
    return;
}

void    lci_mt10t8_init(uint8_t *pt_lci_select)       // Send signals to LCI for unlock.
{
    *(pt_bus->pt_WR1) = 0;              // pt_WR1 = 0. Don't send signals to LCI.
    *(pt_lci_select) = 0;               // WR2 = 0. LCI enable.
    *(pt_bus->pt_D0) = 1;               // DB0 = 1.
    *(pt_bus->pt_D1) = 1;               // DB1 = 1.
    *(pt_bus->pt_D2) = 1;               // DB2 = 1.
    *(pt_bus->pt_D3) = 1;               // DB3 = 1.
    *(pt_bus->pt_A0) = 0;               // pt_A0 = 0.  DB3-DB0 = 0xF - LCI register address.
    *(pt_bus->pt_WR1) = 1;              // pt_WR1 = 1. Send register address 0xF to LCI.
    *(pt_bus->pt_WR1) = 0;              // pt_WR1 = 0. Don't send signals to LCI.
    *(pt_bus->pt_D1) = 0;               // DB1 = 0.
    *(pt_bus->pt_D2) = 0;               // DB2 = 0.
    *(pt_bus->pt_D3) = 0;               // DB3 = 0.
    *(pt_bus->pt_A0) = 1;               // pt_A0 = 1.  DB3-DB0 = 0x1 - data.
    *(pt_bus->pt_WR1) = 1;              // pt_WR1 = 1, Send data 0x1 to lci register 0xF for LCI unlock.
    *(pt_bus->pt_WR1) = 0;              // pt_WR1 = 0. Don't send signals to LCI.
    *(pt_lci_select) = 1;               // WR2 = 1. LCI disable.
    
    lci_mt10t8_clear(pt_lci_select);    // Clear LCI.
    return;
}   // End of lci_mt10t8_init.

void    lci_mt10t8_clear(uint8_t *pt_lci_select)    // Clear LCI.
{
    uint8_t    void_array[LCI_MT10T8_DIMENTION] = {0,0,0,0,0,0,0,0,0,0};
    
    lci_mt10t8_out_segment_code_string(pt_lci_select, &void_array[0]);
    return;
}   // End of lci_mt10t8_clear.

void    lci_mt10t8_out_segment_code_string(uint8_t *pt_lci_select, uint8_t *pt_segment_code_string)
{
    uint8_t     *pt_data_internal;

    *(pt_bus->pt_WR1) = 0;        // pt_WR1 = 0. Don't send signals to lci.
    *pt_lci_select = 0;         // WR2 = 0. lci enable.
    *(pt_bus->pt_D0) = 0;         // DB0 = 0.
    *(pt_bus->pt_D1) = 0;         // DB1 = 0.
    *(pt_bus->pt_D2) = 0;         // DB2 = 0.
    *(pt_bus->pt_D3) = 0;         // DB3 = 0.
    *(pt_bus->pt_A0) = 0;         // pt_A0 = 0.  DB3-DB0 = 0x0 - lci register address.
    *(pt_bus->pt_WR1) = 1;        // pt_WR1 = 1. Send register address 0x0 to lci.
    *(pt_bus->pt_WR1) = 0;        // pt_WR1 = 0. Don't send signals to lci.
    *(pt_bus->pt_A0) = 1;         // pt_A0 = 1.  DB3-DB0 = 0x1 - data.
    for (pt_data_internal = pt_segment_code_string + LCI_MT10T8_DIMENTION-1; pt_data_internal > pt_segment_code_string - 1; pt_data_internal--)
    {
        *(pt_bus->pt_D0) = (*pt_data_internal) & 0x01;            // DB0.
        *(pt_bus->pt_D1) = ((*pt_data_internal) >> 1) & 0x01;     // DB1.
        *(pt_bus->pt_D2) = ((*pt_data_internal) >> 2) & 0x01;     // DB2.
        *(pt_bus->pt_D3) = ((*pt_data_internal) >> 3) & 0x01;     // DB3.
        *(pt_bus->pt_WR1) = 1;                                    // pt_WR1 = 1. Send low tetrad data to lci register.
        *(pt_bus->pt_WR1) = 0;                                    // pt_WR1 = 0. Don't send signals to lci.
        *(pt_bus->pt_D0) = ((*pt_data_internal) >> 4) & 0x01;     // DB0.
        *(pt_bus->pt_D1) = ((*pt_data_internal) >> 5) & 0x01;     // DB1.
        *(pt_bus->pt_D2) = ((*pt_data_internal) >> 6) & 0x01;     // DB2.
        *(pt_bus->pt_D3) = ((*pt_data_internal) >> 7) & 0x01;     // DB3.
        *(pt_bus->pt_WR1) = 1;                                    // pt_WR1 = 1. Send higt tetrad data to lci register. Increment lci register address automatically.
        *(pt_bus->pt_WR1) = 0;                                    // pt_WR1 = 0. Don't send signals to lci.
    }
    *(pt_lci_select) = 1;                                         // WR2 = 1. lci disable.
    return;
}   // End of lci_mt10t8_out_segment_code_string.

void    lci_mt10t8_out_char_string(uint8_t *pt_lci_select, uint8_t *pt_char_string)
{
    uint8_t    segment_code_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_char_string_to_segment_code_string(pt_char_string, &segment_code_array[0]);
    lci_mt10t8_out_segment_code_string(pt_lci_select, &segment_code_array[0]);
    return;
}   // End of lci_mt10t8_out_char_string.

void    lci_mt10t8_out_bin(uint8_t *pt_lci_select, uint8_t *pt_data)
{
    uint8_t    segment_code_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_bin_to_segment_code_string(pt_data, &segment_code_array[0]);
    lci_mt10t8_out_segment_code_string(pt_lci_select, &segment_code_array[0]);
    return;
}   // End of lci_mt10t8_out_bin.

void    lci_mt10t8_out_unsign_dec(uint8_t *pt_lci_select, uint32_t *pt_data)
{
    uint8_t    segment_code_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_unsign_dec_to_segment_code_string(pt_data, &segment_code_array[0]);
    lci_mt10t8_out_segment_code_string(pt_lci_select, &segment_code_array[0]);
    return;
}   // End of lci_mt10t8_out_unsign_dec.

void    lci_mt10t8_out_sign_dec(uint8_t *pt_lci_select, uint32_t *pt_data)
{
    uint8_t    segment_code_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_sign_dec_to_segment_code_string(pt_data, &segment_code_array[0]);
    lci_mt10t8_out_segment_code_string(pt_lci_select, &segment_code_array[0]);
    return;
}   // End of lci_mt10t8_out_sign_dec.

void    lci_mt10t8_out_unsign_hex(uint8_t *pt_lci_select, uint32_t *pt_data)
{
    uint8_t    segment_code_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_unsign_hex_to_segment_code_string(pt_data, &segment_code_array[0]);
    lci_mt10t8_out_segment_code_string(pt_lci_select, &segment_code_array[0]);
    return;
}   // End of lci_mt10t8_out_unsign_hex.

void    lci_mt10t8_out_sign_hex(uint8_t *pt_lci_select, uint32_t *pt_data)
{
    uint8_t    segment_code_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_sign_hex_to_segment_code_string(pt_data, &segment_code_array[0]);
    lci_mt10t8_out_segment_code_string(pt_lci_select, &segment_code_array[0]);
    return;
}   // End of lci_mt10t8_out_sign_hex.

void    lci_mt10t8_convert_char_string_to_segment_code_string(uint8_t *pt_char_string, uint8_t *pt_segment_code_string)
{
    uint8_t     i;

    for (i = 0; i < LCI_MT10T8_DIMENTION; i++)
    {
        switch  (*(pt_char_string + i))
        {
            case '0' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_0;   // 0
            break;
            case '1' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_1;   // 1
            break;
            case '2' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_2;   // 2
            break;
            case '3' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_3;   // 3
            break;
            case '4' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_4;   // 4
            break;
            case '5' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_5;   // 5
            break;
            case '6' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_6;   // 6
            break;
            case '7' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_7;   // 7
            break;
            case '8' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_8;   // 8
            break;
            case '9' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_9;   // 9
            break;
            case 'A' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_A;   // A
            break;
            case 'b' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_b;   // b
            break;
            case 'c' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_c;   // c
            break;
            case 'd' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_d;   // d
            break;
            case 'E' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_E;   // E
            break;
            case 'F' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_F;   // F
            break;
            case '-' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_MINUS;   // -
            break;
            case '*' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_DEGREE;   // *
            break;
            case 'J' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_J;   // J
            break;
            case 'G' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_G;   // G
            break;
            case 'h' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_h;   // h
            break;
            case 'L' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_L;   // L
            break;
            case 'n' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_n;   // n
            break;
            case 'o' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_o;   // o
            break;
            case 'P' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_P;   // P
            break;
            case 'r' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_r;   // r
            break;
            case 'U' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_U;   // U
            break;
            case 'X' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_X;   // X
            break;
            case 'Y' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_Y;   // Y
            break;
            case '=' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_EQUAL;   // =
            break;
            case '_' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_UNDERLINE;   // _
            break;
            case '!' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_EXCLAMATION;   // !
            break;
            case '^' :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_ROOF;   // ^
            break;
            default  :
            	*(pt_segment_code_string + i) = SEGMENT_CODE_SPASE;      // Spase
            break;
        }   // End of switch.
    }   // End of for.
    return;
}   // End of lci_mt10t8_convert_char_string_to_segment_code_string.

void    lci_mt10t8_convert_bin_to_segment_code_string(uint8_t *pt_data, uint8_t *pt_segment_code_string)
{
    uint8_t    char_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_bin_to_char_string(pt_data, &char_array[0]);
    lci_mt10t8_convert_char_string_to_segment_code_string(&char_array[0], pt_segment_code_string);
    return;
}   // End of lci_mt10t8_convert_bin_to_segment_code_string.


void    lci_mt10t8_convert_unsign_dec_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string)
{
    uint8_t    char_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_unsign_dec_to_char_string(pt_data, &char_array[0]);
    lci_mt10t8_convert_char_string_to_segment_code_string(&char_array[0], pt_segment_code_string);
    return;
}   // End of lci_mt10t8_convert_unsign_dec_to_segment_code_string.

void    lci_mt10t8_convert_sign_dec_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string)
{
    uint8_t    char_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_sign_dec_to_char_string(pt_data, &char_array[0]);
    lci_mt10t8_convert_char_string_to_segment_code_string(&char_array[0], pt_segment_code_string);
    return;
}   // End of lci_mt10t8_convert_sign_dec_to_segment_code_string.

void    lci_mt10t8_convert_unsign_hex_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string)
{
    uint8_t    char_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_unsign_hex_to_char_string(pt_data, &char_array[0]);
    lci_mt10t8_convert_char_string_to_segment_code_string(&char_array[0], pt_segment_code_string);
    return;
}   // End of lci_mt10t8_convert_unsign_hex_to_segment_code_string.

void    lci_mt10t8_convert_sign_hex_to_segment_code_string(uint32_t *pt_data, uint8_t  *pt_segment_code_string)
{
    uint8_t    char_array[LCI_MT10T8_DIMENTION];
    
    lci_mt10t8_convert_sign_hex_to_char_string(pt_data, &char_array[0]);
    lci_mt10t8_convert_char_string_to_segment_code_string(&char_array[0], pt_segment_code_string);
    return;
}   // End of lci_mt10t8_convert_sign_hex_to_segment_code_string.

void    lci_mt10t8_convert_bin_to_char_string(uint8_t *pt_data, uint8_t *pt_char_string)
{
    uint8_t     i;

    for (i = 0; i < SIZE_OF_BIN; i++)
        *(pt_char_string+ i) = '0' + (((*pt_data) >> i) & 0x01);
    *(pt_char_string+ 8) = ' ';                                // Replace insignificant zeros by space.
    *(pt_char_string+ 9) = 'b';                                // Set bin sign.
    return;
}   // End of lci_mt10t8_convert_bin_to_char_string.

void    lci_mt10t8_convert_unsign_dec_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string)
{
    uint32_t    data1, data2;
    uint8_t     char_string_position;
    
    char_string_position = 0;
    data1 = *pt_data;
    do
    {
        data2 = data1;                                                                // Remember value.
        data1 = data1 / DEC_NUM_SYS_BASE;
        *(pt_char_string + char_string_position) = '0' + (uint8_t)(data2 - data1 * DEC_NUM_SYS_BASE);    // Convert decada to ASCII code.
        char_string_position++;
    }
    while (data1 > 0);
    for ( ; char_string_position < LCI_MT10T8_DIMENTION; char_string_position++)
        *(pt_char_string +  char_string_position) = ' ';                      // Replace insignificant zeros by space.
    return;
}   // End of lci_mt10t8_convert_unsign_dec_to_char_string.

void    lci_mt10t8_convert_sign_dec_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string)
{
    uint32_t    data1;
    uint8_t     char_string_position, sign;

    if (*pt_data > MAX_POSITIVE_VALUE)                              // If data is negativ, then
    {
        sign = '-';                                                     // sign = '-';
        data1 = ~(*pt_data) + 1;                                        // extract negative value.
        if (data1 > MAX_NEGATIVE_DEC_VALUE)                             // If value < -999999999, then 
            data1 = MAX_NEGATIVE_DEC_VALUE;                              // limit value by -999999999.
    }
    else                                                            // If data1 =< MAX_POSITIVE_VALUE, then
        {
            sign = ' ';                                             // sign is absent and
            data1 = *pt_data;                                       // data is positive.
        }
    lci_mt10t8_convert_unsign_dec_to_char_string(&data1, pt_char_string);    // Convert new data value.
    if (sign == '-')                                                          // If sign is negativ,
    {                                                                        // find sign position in char string and
        for (char_string_position = LCI_MT10T8_DIMENTION-1; *(pt_char_string + char_string_position) != ' '; char_string_position--)
        *(pt_char_string + char_string_position + 1) = sign;                 // put sign in char string.
    }
    return;
}   // End of lci_mt10t8_convert_sign_dec_to_char_string.

void    lci_mt10t8_convert_unsign_hex_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string)
{
    uint32_t    data1;
    uint8_t     char_string_position, tetrada;
    
    char_string_position = 0;
    data1 = *pt_data;
    do
    {
        tetrada = (uint8_t)(data1 & LOW_TETRAD_MSK);
        switch (tetrada)                                                              // Convert tetrada to ASCII code.
        {
            case 0x0F   :
                *(pt_char_string + char_string_position) = 'F';
            break;
            case 0x0E   :
                *(pt_char_string + char_string_position) = 'E';
            break;
            case 0x0D   :
                *(pt_char_string + char_string_position) = 'd';
            break;
            case 0x0C   :
                *(pt_char_string + char_string_position) = 'c';
            break;
            case 0x0B   :
                *(pt_char_string + char_string_position) = 'b';
            break;
            case 0x0A   :
                *(pt_char_string + char_string_position) = 'A';
            break;
            default     :
                *(pt_char_string + char_string_position) = '0' + tetrada;
        }   // End of switch.
        data1 >>= 4;                                                                  // Next decada.
        char_string_position++;                                                       // Next position in char string.
    }
    while (data1 > 0);
    for ( ; char_string_position < LCI_MT10T8_DIMENTION-1; char_string_position++)
        *(pt_char_string + char_string_position) = ' ';                                                  // Replace insignificant zeros by space.
    *(pt_char_string + char_string_position) = 'h';                                   // Set hex sign.
    return;
}   // End of lci_mt10t8_convert_unsign_hex_to_char_string.

void    lci_mt10t8_convert_sign_hex_to_char_string(uint32_t *pt_data, uint8_t  *pt_char_string)
{
    uint32_t    data1;
    uint8_t     char_string_position, sign;
    
    if (*pt_data > MAX_POSITIVE_VALUE)                              // If data is negativ, then
    {
        sign = '-';                                                 // sign = '-';
        data1 = ~(*pt_data) + 1;                                    // extract negative value.
    }
    else                                                            // If data1 =< MAX_POSITIVE_VALUE, then
        {
            sign = ' ';                                             // sign is absent and
            data1 = *pt_data;                                       // data is positive.
        }
    lci_mt10t8_convert_unsign_hex_to_char_string(&data1, pt_char_string);    // Convert new data value.
    if (sign == '-')                                                          // If sign is negativ,
    {                                                                        // find sign position in char string and
        for (char_string_position = LCI_MT10T8_DIMENTION - 2; *(pt_char_string + char_string_position) != ' '; char_string_position--)
            *(pt_char_string + char_string_position + 1) = sign;                 // put sign in char string.
    }
    return;
}   // End of lci_mt10t8_convert_sign_hex_to_char_string.
