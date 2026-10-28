/**
 * @file ExpressionPedal.cpp
 * 
 * @brief `MIDI-GP`: ExpressionPedal Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "ExpressionPedal.h"

#include <Arduino.h>
#include "Logger.h"
// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

ExpressionPedal::ExpressionPedal(Potentiometer& pot,uint8_t cc_min,uint8_t cc_max,uint16_t raw_min,uint16_t raw_max,uint16_t deadzone,uint16_t threshold) : pot(pot)
{
    this->cc_min = cc_min; 
    this->cc_max = cc_max; 
    this->deadzone = deadzone;
    this->threshold = threshold; 
    this->assignLowerBound(raw_min);
    this->assignUpperBound(raw_max);
    this->raw_value = 0;
    this->cc_value = 0;
}
ExpressionPedal::~ExpressionPedal() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void ExpressionPedal::init()
{
    this->raw_value = this->pot.read();
    uint16_t clamped_value = constrain(this->raw_value,this->lower_bound,this->upper_bound);
    this->cc_value = map(clamped_value,this->lower_bound,this->upper_bound,this->cc_min,this->cc_max);
}
bool ExpressionPedal::update()
{
    uint16_t new_value = this->pot.read();

    if(!this->movementDetected(new_value))
    {
        return false;
    }

    this->raw_value = new_value;

    uint16_t clamped_value = constrain(this->raw_value,this->lower_bound,this->upper_bound);
    uint8_t new_cc_value = map(clamped_value,this->lower_bound,this->upper_bound,this->cc_min,this->cc_max);
    
    if(new_cc_value == this->cc_value)
    {
        return false;
    }

    this->cc_value = new_cc_value;

    return true;
}
uint8_t ExpressionPedal::value() const
{
    return this->cc_value;
}
void ExpressionPedal::assignLowerBound(uint16_t raw_value)
{
    this->lower_bound = raw_value + this->deadzone;
}
void ExpressionPedal::assignUpperBound(uint16_t raw_value)
{
    this->upper_bound = raw_value - this->deadzone;
}

// ------------------------
// [Private] Member Methods
// ------------------------

bool ExpressionPedal::movementDetected(uint16_t raw_value) const
{
    uint16_t diff;
    if(raw_value >= this->raw_value)
    {
        diff = raw_value - this->raw_value;
    }
    else
    {
        diff = this->raw_value - raw_value;
    }
    return (diff > this->threshold);
}