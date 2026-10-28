/**
 * @file ButtonHandler.cpp
 * 
 * @brief `MIDI-GP`: ButtonHandler Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "ButtonHandler.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

ButtonHandler::ButtonHandler(Button& btn,uint16_t hold_time) : btn(btn)
{
    this->hold_time = hold_time;
    this->state = State::IDLE;
}
ButtonHandler::~ButtonHandler() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void ButtonHandler::process()
{
    switch(this->state)
    {
        case State::IDLE:
        {
            if(this->btn.pressed())
            {
                this->timer.reset();
                this->state = State::PENDING;
            }
            break;
        }
        case State::PENDING:
        {
            if(this->btn.released())
            {
                this->gesture.triggerPressCallback();
                this->state = State::IDLE;
            }
            else if(this->timer.expired(this->hold_time))
            {
                this->gesture.triggerHoldCallback();
                this->state = State::IDLE;
            }
            break;
        }
    }
}
void ButtonHandler::reset()
{
    this->state = State::IDLE;
}
ButtonState ButtonHandler::getState() const
{
    return this->state;
}
ButtonHandler& ButtonHandler::onPress(ButtonCallback callback,void* context)
{
    this->gesture.onPress(callback,context);
    return *this;
}
ButtonHandler& ButtonHandler::onHold(ButtonCallback callback,void* context)
{
    this->gesture.onHold(callback,context);
    return *this;
}