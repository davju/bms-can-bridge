#include "crc.h"

uint16_t CRC16(const uint8_t *data, uint16_t length)
{
    uint8_t tmp;
    uint16_t crcWord = 0xFFFF;
    while (length--)
    {
        tmp = *data++ ^ crcWord;
        crcWord >>= 8;
        crcWord ^= crcTable[tmp];
    }
    return crcWord;
}