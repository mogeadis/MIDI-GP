/**
 * @file LedOperator.h
 * 
 * @brief `MIDI-GP`: LedOperator Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Led.h"
#include "Timer.h"

class LedOperator
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    LedOperator() = delete;
    LedOperator(Led& led,uint16_t flash_time,uint16_t blink_time);
    ~LedOperator();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void process();
    void flash();
    void startBlinking();
    void stopBlinking();
    
    private:

    // ----------------------
    // [Private] Enumerations
    // ----------------------

    enum class State : uint8_t
    {
        OFF,
        FLASHING,
        BLINKING,
    };

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    Led& led;
    uint16_t flash_time;
    uint16_t blink_time;
    State state;
    Timer timer;
};