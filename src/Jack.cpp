/**
 * @file Jack.cpp
 * 
 * @brief `MIDI-GP`: Jack Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Jack.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Jack::Jack(uint8_t pin,uint16_t debounce_time) : Switch(pin,debounce_time) {}
Jack::~Jack() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

bool Jack::connected() const
{
    return this->state();
}