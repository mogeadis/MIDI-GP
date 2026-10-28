/**
 * @file Memory.h
 * 
 * @brief `MIDI-GP`: Memory Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

class Memory
{
    public:

    // --------------------------------
    // [Public] Static Template Methods
    // --------------------------------

    template<typename T>
    static void write(uint16_t address,const T& value);
    template<typename T>
    static void read(uint16_t address,T& value);

    private:

    // ------------------------
    // [Private] Static Methods
    // ------------------------

    static void writeByte(uint16_t address,uint8_t value);
    static uint8_t readByte(uint16_t address);

    // ------------------------------------------
    // [Private] Constructor & Destructor Methods
    // ------------------------------------------
    
    Memory() = delete;
    ~Memory() = delete;
};

// --------------------------------
// [Public] Static Template Methods
// --------------------------------

template<typename T>
void Memory::write(uint16_t address,const T& value)
{
    const uint8_t* data = reinterpret_cast<const uint8_t*>(&value);
    for(uint16_t index = 0; index < sizeof(T); index++)
    {
        Memory::writeByte(address + index,data[index]);
    }
}
template<typename T>
void Memory::read(uint16_t address,T& value)
{
    uint8_t* data = reinterpret_cast<uint8_t*>(&value);
    for(uint16_t index = 0; index < sizeof(T); index++)
    {
        data[index] = Memory::readByte(address + index);
    }
}