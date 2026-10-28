/**
 * @file Logger.cpp
 * 
 * @brief `MIDI-GP`: Logger Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Logger.h"

// -----------------------
// [Public] Static Methods
// -----------------------

void Logger::init(uint32_t LOGGER_BAUD_RATE)
{
    Serial.begin(LOGGER_BAUD_RATE);
    #if DEBUG
        while(!Serial) {};
    #endif
}