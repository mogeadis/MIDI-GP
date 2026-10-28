/**
 * @file ButtonGroup.cpp
 * 
 * @brief `MIDI-GP`: ButtonGroup Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "ButtonGroup.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

ButtonGroup::ButtonGroup(Button& btn_1,Button& btn_2,uint16_t group_time,uint16_t hold_time) :
    btn_1(btn_1),
    btn_2(btn_2),
    btn_1_handler(btn_1,hold_time),
    btn_2_handler(btn_2,hold_time)
{
    this->group_time = group_time;
    this->hold_time = hold_time;
    this->group_state = ButtonState::IDLE;
}
ButtonGroup::~ButtonGroup() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void ButtonGroup::process()
{
    if(this->group_state == ButtonState::PENDING)
    {
        this->processGroup();
        return;
    }

    bool btn_1_pressed = this->btn_1.pressed();
    bool btn_2_pressed = this->btn_2.pressed();
    ButtonState btn_1_state = this->btn_1_handler.getState();
    ButtonState btn_2_state = this->btn_2_handler.getState();

    bool btn_1_pressed_before_btn_2 = (btn_1_pressed && btn_2_state == ButtonState::IDLE);
    bool btn_2_pressed_before_btn_1 = (btn_2_pressed && btn_1_state == ButtonState::IDLE);
    if(btn_1_pressed_before_btn_2 || btn_2_pressed_before_btn_1)
    {
        this->group_timer.reset();
    }

    bool btn_1_pressed_after_btn_2 = (btn_1_pressed && btn_2_state == ButtonState::PENDING);
    bool btn_2_pressed_after_btn_1 = (btn_2_pressed && btn_1_state == ButtonState::PENDING);
    bool buttons_pressed_consecutively = ((btn_1_pressed_after_btn_2 || btn_2_pressed_after_btn_1) && !this->group_timer.expired(this->group_time));
    bool buttons_pressed_concurrently = (btn_1_pressed && btn_2_pressed);
    if(buttons_pressed_consecutively || buttons_pressed_concurrently)
    {
        this->group_state = ButtonState::PENDING;
        return;
    }

    this->btn_1_handler.process();
    this->btn_2_handler.process();
}
void ButtonGroup::reset()
{
    this->btn_1_handler.reset();
    this->btn_2_handler.reset();
    this->group_state = ButtonState::IDLE;
}
ButtonHandler& ButtonGroup::firstButtonHandler()
{
    return this->btn_1_handler;
}
ButtonHandler& ButtonGroup::secondButtonHandler()
{
    return this->btn_2_handler;
}
ButtonGroup& ButtonGroup::onPress(ButtonCallback callback,void* context)
{
    this->group_gesture.onPress(callback,context);
    return *this;
}
ButtonGroup& ButtonGroup::onHold(ButtonCallback callback,void* context)
{
    this->group_gesture.onHold(callback,context);
    return *this;
}

// ------------------------
// [Private] Member Methods
// ------------------------

void ButtonGroup::processGroup()
{
    if(this->btn_1.released() || this->btn_2.released())
    {
        this->group_gesture.triggerPressCallback();
        this->reset();
    }
    else if(this->group_timer.expired(this->hold_time))
    {
        this->group_gesture.triggerHoldCallback();
        this->reset();
    }
}