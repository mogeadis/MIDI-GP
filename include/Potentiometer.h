/**
 * @file Potentiometer.h
 * 
 * @brief `MIDI-GP`: Potentiometer Class Header File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

class Potentiometer
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Potentiometer() = delete;
    Potentiometer(uint8_t pin);
    ~Potentiometer();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    uint16_t read() const;

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    uint8_t pin;
};