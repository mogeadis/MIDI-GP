/**
 * @file Jack.h
 * 
 * @brief `MIDI-GP`: Jack Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Switch.h"

class Jack : public Switch
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Jack() = delete;
    Jack(uint8_t pin,uint16_t debounce_time);
    ~Jack();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    bool connected() const;
};