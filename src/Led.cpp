/**
 * @file Led.cpp
 * 
 * @brief `MIDI-GP`: Led Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "Led.h"

#include <Arduino.h>

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Led::Led(uint8_t pin)
{
    this->pin = pin;
    this->state = State::OFF;
}
Led::~Led() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void Led::init()
{
    pinMode(this->pin,OUTPUT);
    this->off();
}
void Led::on()
{
    digitalWrite(this->pin,HIGH);
    this->state = State::ON;
}
void Led::off()
{
    digitalWrite(this->pin,LOW);
    this->state = State::OFF;
}
void Led::toggle()
{
    switch(this->state)
    {
        case State::ON:
        {
            this->off();
            break;
        }
        case State::OFF:
        {
            this->on();
            break;
        }
    }
}