/**
 * @file Switch.h
 * 
 * @brief `MIDI-GP`: Switch Class Header File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Debouncer.h"

class Switch
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Switch() = delete;
    Switch(uint8_t pin,uint16_t debounce_time);
    ~Switch();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void init();
    void update();
    bool changed() const;
    bool state() const;

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    uint8_t pin;
    Debouncer debouncer;
};