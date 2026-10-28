/**
 * @file Timer.cpp
 * 
 * @brief `MIDI-GP`: Timer Class Implementation File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Timer.h"

#include <Arduino.h>

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Timer::Timer()
{
    this->start_time = 0;
}
Timer::~Timer() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void Timer::reset()
{
    this->start_time = millis();
}
uint32_t Timer::elapsed() const
{
    return millis() - this->start_time;
}
bool Timer::expired(uint32_t duration) const
{
    return (this->elapsed() >= duration);
}