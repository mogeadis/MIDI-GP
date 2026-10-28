/**
 * @file Debouncer.h
 * 
 * @brief `MIDI-GP`: Debouncer Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Timer.h"

class Debouncer
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Debouncer() = delete;
    Debouncer(uint16_t debounce_time);
    ~Debouncer();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void init(bool raw_state);
    void update(bool raw_state);
    bool state() const;
    bool changed() const;

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    Timer timer;
    uint16_t debounce_time;
    bool raw_state;
    bool stable_state;
    bool state_changed;
};