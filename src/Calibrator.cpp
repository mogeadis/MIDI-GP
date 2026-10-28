/**
 * @file Calibrator.cpp
 * 
 * @brief `MIDI-GP`: Calibrator Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Calibrator.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Calibrator::Calibrator(Potentiometer& pot) : pot(pot)
{
    this->raw_value = 0;
    this->min_value = 0;
    this->max_value = 0;
}
Calibrator::~Calibrator() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void Calibrator::begin()
{
    this->raw_value = this->pot.read();
    this->min_value = this->raw_value;
    this->max_value = this->raw_value;
}
bool Calibrator::update()
{
    uint16_t new_value = this->pot.read();

    if(new_value == this->raw_value)
    {
        return false;
    }

    if(new_value < this->min_value)
    {
        this->min_value = new_value;
    }
    if(new_value > this->max_value)
    {
        this->max_value = new_value;
    }

    this->raw_value = new_value;
    
    return true;
}
uint16_t Calibrator::rawValue() const
{
    return this->raw_value;
}
uint16_t Calibrator::minValue() const
{
    return this->min_value;
}
uint16_t Calibrator::maxValue() const
{
    return this->max_value;
}