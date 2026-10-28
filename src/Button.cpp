/**
 * @file Button.cpp
 * 
 * @brief `MIDI-GP`: Button Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Button.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Button::Button(uint8_t pin,uint16_t debounce_time) : Switch(pin,debounce_time) {}
Button::~Button() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

bool Button::down() const
{
    return !this->state();
}
bool Button::up() const
{
    return this->state();
}
bool Button::pressed() const
{
    return (this->changed() && this->down());
}
bool Button::released() const
{
    return (this->changed() && this->up());
}