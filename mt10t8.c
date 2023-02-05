#include "mt10t8.h"

static  inline  void    mt10t8_enable(mt10t8_t *pt_lci)
{
    *(pt_lci->pt_WR2) = 0;  // WR2 = 0. LCI enable.
}   // End of mt10t8_enable.

static  inline  void    mt10t8_disable(mt10t8_t *pt_lci)
{
    *(pt_lci->pt_WR2) = 1;  // WR2 = 1. LCI disable.
}   // End of mt10t8_disable.

static  void    mt10t8_send_nibble(mt10t8_t *pt_lci, uint8_t data)
{
    *(pt_lci->mt10t8_bus->pt_D0) = (data & 1);
    *(pt_lci->mt10t8_bus->pt_D1) = ((data >> 1) & 1);
    *(pt_lci->mt10t8_bus->pt_D2) = ((data >> 2) & 1);
    *(pt_lci->mt10t8_bus->pt_D3) = ((data >> 3) & 1);
    *(pt_lci->mt10t8_bus->pt_WR1) = 1;
    *(pt_lci->mt10t8_bus->pt_WR1) = 0;  // pt_WR1 = 0. Don't send signals to LCI.
}   // End of mt10t8_send_nibble.

static  inline  void    mt10t8_send_address(mt10t8_t *pt_lci, uint8_t address)
{
        *(pt_lci->mt10t8_bus->pt_A0) = 0;
        mt10t8_send_nibble(pt_lci, address);
        *(pt_lci->mt10t8_bus->pt_A0) = 1;
}   // End of mt10t8_send_address.

static  inline  void    mt10t8_send_byte(mt10t8_t *pt_lci, uint8_t data)
{
        mt10t8_send_nibble(pt_lci, data);
        mt10t8_send_nibble(pt_lci, (data >> 4));
}   // End of mt10t8_send_data.

static  uint8_t     mt10t8_char_to_code(uint8_t data)
{
    switch  (data)
    {
        case '0' : return 0xEE;
        case '1' : return 0x60;
        case '2' : return 0x2F;
        case '3' : return 0x6D;
        case '4' : return 0xE1;
        case '5' : return 0xCD;
        case '6' : return 0xCF;
        case '7' : return 0x68;
        case '8' : return 0xEF;
        case '9' : return 0xED;
        case 'A' : return 0xEB;
        case 'a' : return 0xEB;
        case 'B' : return 0xC7;
        case 'b' : return 0xC7;
        case 'C' : return 0x07;
        case 'c' : return 0x07;
        case 'D' : return 0x67;
        case 'd' : return 0x67;
        case 'E' : return 0x8F;
        case 'e' : return 0x8F;
        case 'F' : return 0x8B;
        case 'f' : return 0x8B;
        case '-' : return 0x01;
        case '*' : return 0xA9;
        case 'J' : return 0x6E;
        case 'j' : return 0x6E;
        case 'G' : return 0xCE;
        case 'g' : return 0xCE;
        case 'H' : return 0xC3;
        case 'h' : return 0xC3;
        case 'L' : return 0x86;
        case 'l' : return 0x86;
        case 'N' : return 0x43;
        case 'n' : return 0x43;
        case 'O' : return 0x47;
        case 'o' : return 0x47;
        case 'P' : return 0xAB;
        case 'p' : return 0xAB;
        case 'R' : return 0x03;
        case 'r' : return 0x03;
        case 'U' : return 0xE6;
        case 'u' : return 0x46;
        case 'X' : return 0xE3;
        case 'x' : return 0xE3;
        case 'Y' : return 0xE5;
        case 'y' : return 0xE5;
        case '=' : return 0x05;
        case '_' : return 0x04;
        case '!' : return 0x70;
        case '^' : return 0x41;
        case '.' : return 0x10;
    }   // End of switch.
    return 0;
}   // End of mt10t8_char_to_code.

static  void    mt10t8_string_char_to_code(uint8_t *pt_char_string, uint8_t *pt_code_string)
{
    uint8_t code_cell = 0;
    uint8_t char_cell = 0;
    uint8_t first_point_flag = 1;

    while ((code_cell < MT10T8_DIMENTION) && (*(pt_char_string + char_cell)))   // While not end of code buffer and not end of string.
    {
    	if (*(pt_char_string + char_cell) == '.')                               // If symbol is point,
        {
			if (!first_point_flag)                                              // If first point,
            {
                code_cell--;
                *(pt_code_string + code_cell) |= 0x10;                          // Addition point in last symbol;
                first_point_flag = 1;
            }
            else
                *(pt_code_string + code_cell) = mt10t8_char_to_code(*(pt_char_string + char_cell)); // Set point as separate symbol.
        }
        else
        {
            *(pt_code_string + code_cell) = mt10t8_char_to_code(*(pt_char_string + char_cell));
            first_point_flag = 0;
        }
        code_cell++;
        char_cell++;
    }   // End of while.
}   // End of mt10t8_out_char_string.

static  void    mt10t8_out_code_string(mt10t8_t *pt_lci, uint8_t *pt_code_string)
{
    uint8_t i;
    
    mt10t8_enable(pt_lci);
    mt10t8_send_address(pt_lci, 0);
    for (i = 0; i < MT10T8_DIMENTION; i++)
        mt10t8_send_byte(pt_lci, *(pt_code_string + i));
    mt10t8_disable(pt_lci);
}   // End of mt10t8_out_code_string.

void    mt10t8_init(mt10t8_t *pt_lci)
{
		*(pt_lci->mt10t8_bus->pt_WR1) = 0;  // pt_WR1 = 0. Don't send signals to LCI.
        mt10t8_enable(pt_lci);
        mt10t8_send_address(pt_lci, 0x0F);  // Send register address 0xF to LCI.
        mt10t8_send_nibble(pt_lci, 0x01);   // Send nibble 0b1111 to lci register 0xF for LCI unlock.
        mt10t8_disable(pt_lci);
        mt10t8_out_char_string(pt_lci, "          ");
}   // End of mt10t8_init.

void    mt10t8_out_char_string(mt10t8_t *pt_lci, uint8_t *pt_char_string)
{
    uint8_t buffer[MT10T8_DIMENTION] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    mt10t8_enable(pt_lci);
    mt10t8_string_char_to_code(pt_char_string, &buffer[0]);
    mt10t8_out_code_string(pt_lci, &buffer[0]);
    mt10t8_disable(pt_lci);
}   // End of mt10t8_out_char_string.
