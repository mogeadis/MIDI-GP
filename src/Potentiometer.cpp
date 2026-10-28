/**
 * @file Potentiometer.cpp
 * 
 * @brief `MIDI-GP`: Potentiometer Class Implementation File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Potentiometer.h"

#include <Arduino.h>

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Potentiometer::Potentiometer(uint8_t pin)
{
    this->pin = pin;
}
Potentiometer::~Potentiometer() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

uint16_t Potentiometer::read() const
{
    return analogRead(this->pin);
}