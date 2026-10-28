/**
 * @file ExpressionPedal.h
 * 
 * @brief `MIDI-GP`: ExpressionPedal Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Potentiometer.h"

class ExpressionPedal
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    ExpressionPedal() = delete;
    ExpressionPedal(Potentiometer& pot,uint8_t cc_min,uint8_t cc_max,uint16_t raw_min,uint16_t raw_max,uint16_t deadzone,uint16_t threshold);
    ~ExpressionPedal();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void init();
    bool update();
    uint8_t value() const;
    void assignLowerBound(uint16_t raw_value);
    void assignUpperBound(uint16_t raw_value);

    private:

    // ------------------------
    // [Private] Member Methods
    // ------------------------

    bool movementDetected(uint16_t raw_value) const;

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    Potentiometer& pot;
    uint8_t cc_min;
    uint8_t cc_max;
    uint16_t deadzone;
    uint16_t threshold;
    uint16_t lower_bound;
    uint16_t upper_bound;
    uint16_t raw_value;
    uint8_t cc_value;
};