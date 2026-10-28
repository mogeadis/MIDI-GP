/**
 * @file Switch.cpp
 * 
 * @brief `MIDI-GP`: Switch Class Implementation File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Switch.h"

#include <Arduino.h>

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Switch::Switch(uint8_t pin,uint16_t debounce_time) : debouncer(debounce_time)
{
    this->pin = pin;
}
Switch::~Switch() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void Switch::init()
{
    pinMode(this->pin,INPUT_PULLUP);
    this->debouncer.init(digitalRead(this->pin));
}
void Switch::update()
{
    this->debouncer.update(digitalRead(this->pin));
}
bool Switch::changed() const
{
    return this->debouncer.changed();
}
bool Switch::state() const
{
    return this->debouncer.state();
}