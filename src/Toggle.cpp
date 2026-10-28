/**
 * @file Toggle.cpp
 * 
 * @brief `MIDI-GP`: Toggle Class Implementation File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Toggle.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Toggle::Toggle(uint8_t on_value,uint8_t off_value,bool set_on)
{
    this->on_value = on_value;
    this->off_value = off_value;
    this->state = set_on ? State::ON : State::OFF;
}
Toggle::~Toggle() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

uint8_t Toggle::trigger()
{
    uint8_t value;
    switch(this->state)
    {
        case State::ON:
        {
            this->state = State::OFF;
            value = this->off_value;
            break;
        }
        case State::OFF:
        {
            this->state = State::ON;
            value = this->on_value;
            break;
        }
    }
    return value;
}