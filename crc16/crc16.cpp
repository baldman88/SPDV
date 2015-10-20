#include "crc16.hpp"


uint16_t Calculate(uint8_t *data, uint8_t size)
{
    uint16_t crc16 = 0xFFFF; /* Initial value */
    for (uint8_t i = 0; i < size; i++)
    {
        crc16 ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            crc16 = (crc16 & 0x0001) ? ((crc16 >> 1) ^ 0xA001) : (crc16 >> 1);
        }
    }
    return crc16;
}
