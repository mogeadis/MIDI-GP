/**
 * @file Calibrator.h
 * 
 * @brief `MIDI-GP`: Calibrator Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Potentiometer.h"

class Calibrator
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Calibrator() = delete;
    Calibrator(Potentiometer& pot);
    ~Calibrator();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void begin();
    bool update();
    uint16_t rawValue() const;
    uint16_t minValue() const;
    uint16_t maxValue() const;

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    Potentiometer& pot;
    uint16_t raw_value;
    uint16_t min_value;
    uint16_t max_value;
};