/**
 * @file Memory.cpp
 * 
 * @brief `MIDI-GP`: Memory Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Memory.h"

#include <EEPROM.h>

// ------------------------
// [Private] Static Methods
// ------------------------

void Memory::writeByte(uint16_t address,uint8_t value)
{
    EEPROM.update(address,value);
}
uint8_t Memory::readByte(uint16_t address)
{
    return EEPROM.read(address);
}