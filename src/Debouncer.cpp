/**
 * @file Debouncer.cpp
 * 
 * @brief `MIDI-GP`: Debouncer Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Debouncer.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Debouncer::Debouncer(uint16_t debounce_time)
{
    this->debounce_time = debounce_time;
    this->raw_state = false;
    this->stable_state = false;
    this->state_changed = false;
}
Debouncer::~Debouncer() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void Debouncer::init(bool raw_state)
{
    this->raw_state = raw_state;
    this->stable_state = raw_state;
}
void Debouncer::update(bool raw_state)
{
    this->state_changed = false;

    if(raw_state != this->raw_state)
    {
        this->raw_state = raw_state;
        this->timer.reset();
        return;
    }

    if(this->raw_state != this->stable_state && this->timer.expired(this->debounce_time))
    {
        this->stable_state = this->raw_state;
        this->state_changed = true;
    }
}
bool Debouncer::state() const
{
    return this->stable_state;
}
bool Debouncer::changed() const
{
    return this->state_changed;
}