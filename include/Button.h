/**
 * @file Button.h
 * 
 * @brief `MIDI-GP`: Button Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Switch.h"

class Button : public Switch
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Button() = delete;
    Button(uint8_t pin,uint16_t debounce_time);
    ~Button();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    bool down() const;
    bool up() const;
    bool pressed() const;
    bool released() const;
};