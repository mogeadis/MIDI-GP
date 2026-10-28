/**
 * @file Timer.h
 * 
 * @brief `MIDI-GP`: Timer Class Header File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

class Timer
{
    public:
    
    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Timer();
    ~Timer();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void reset();
    uint32_t elapsed() const;
    bool expired(uint32_t duration) const;

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    uint32_t start_time;
};