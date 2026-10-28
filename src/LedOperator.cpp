/**
 * @file LedOperator.cpp
 * 
 * @brief `MIDI-GP`: LedOperator Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "LedOperator.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

LedOperator::LedOperator(Led& led,uint16_t flash_time,uint16_t blink_time) : led(led)
{
    this->flash_time = flash_time;
    this->blink_time = blink_time;
    this->state = State::OFF;
}
LedOperator::~LedOperator() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void LedOperator::process()
{
    switch(this->state)
    {
        case State::OFF:
        {
            break;
        }
        case State::FLASHING:
        {
            if(this->timer.expired(this->flash_time))
            {
                this->led.off();
                this->state = State::OFF;
            }
            break;
        }
        case State::BLINKING:
        {
            if(this->timer.expired(this->blink_time))
            {
                this->led.toggle();
                this->timer.reset();
            }
            break;
        }
    }
}
void LedOperator::flash()
{
    this->led.on();
    this->timer.reset();
    this->state = State::FLASHING;
}
void LedOperator::startBlinking()
{
    this->led.on();
    this->timer.reset();
    this->state = State::BLINKING;
}
void LedOperator::stopBlinking()
{
    this->led.off();
    this->state = State::OFF;
}