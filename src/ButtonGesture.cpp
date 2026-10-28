/**
 * @file ButtonGesture.cpp
 * 
 * @brief `MIDI-GP`: ButtonGesture Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "ButtonGesture.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

ButtonGesture::ButtonGesture()
{
    this->press_callback = nullptr;
    this->hold_callback = nullptr;
    this->press_context = nullptr;
    this->hold_context = nullptr;
}
ButtonGesture::~ButtonGesture() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

ButtonGesture& ButtonGesture::onPress(Callback callback,void* context)
{
    this->press_callback = callback;
    this->press_context = context;
    return *this;
}
ButtonGesture& ButtonGesture::onHold(Callback callback,void* context)
{
    this->hold_callback = callback;
    this->hold_context = context;
    return *this;
}
void ButtonGesture::triggerPressCallback() const
{
    if(this->press_callback != nullptr)
    {
        this->press_callback(this->press_context);
    }
}
void ButtonGesture::triggerHoldCallback() const
{
    if(this->hold_callback != nullptr)
    {
        this->hold_callback(this->hold_context);
    }
}