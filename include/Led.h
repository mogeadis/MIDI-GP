/**
 * @file Led.h
 * 
 * @brief `MIDI-GP`: Led Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

class Led
{
    public:
    
    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Led() = delete;
    Led(uint8_t pin);
    ~Led();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void init();
    void on();
    void off();
    void toggle();

    private:

    // ----------------------
    // [Private] Enumerations
    // ----------------------

    enum class State : uint8_t
    {
        ON,
        OFF
    };

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    uint8_t pin;
    State state;
};