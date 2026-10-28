/**
 * @file Logger.h
 * 
 * @brief `MIDI-GP`: Logger Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "Configuration.h"

class Logger
{
    public:

    // -----------------------
    // [Public] Static Methods
    // -----------------------

    static void init(uint32_t LOGGER_BAUD_RATE);

    // --------------------------------
    // [Public] Static Template Methods
    // --------------------------------

    template<typename T>
    static void print(const T& value);
    template<typename T>
    static void println(const T& value);

    private:

    // ------------------------------------------
    // [Private] Constructor & Destructor Methods
    // ------------------------------------------
    
    Logger() = delete;
    ~Logger() = delete;
};

// --------------------------------
// [Public] Static Template Methods
// --------------------------------

template<typename T>
void Logger::print(const T& value)
{
    Serial.print(value);
}
template<typename T>
void Logger::println(const T& value)
{
    Serial.println(value);
}

// -----------------
// Macro Definitions
// -----------------

#if DEBUG
    #define DBG_INIT(x)     Logger::init(x)
    #define DBG_PRINT(x)    Logger::print(x)
    #define DBG_PRINTLN(x)  Logger::println(x)
#else
    #define DBG_INIT(x)     ((void)0)
    #define DBG_PRINT(x)    ((void)0)
    #define DBG_PRINTLN(x)  ((void)0)
#endif