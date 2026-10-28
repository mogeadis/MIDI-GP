/**
 * @file Toggle.h
 * 
 * @brief `MIDI-GP`: Toggle Class Header File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include "stdint.h"

class Toggle
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Toggle() = delete;
    Toggle(uint8_t on_value,uint8_t off_value,bool set_on = false);
    ~Toggle();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    uint8_t trigger();

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

    uint8_t on_value;
    uint8_t off_value;
    State state;
};