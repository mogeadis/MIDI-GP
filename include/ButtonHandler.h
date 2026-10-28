/**
 * @file ButtonHandler.h
 * 
 * @brief `MIDI-GP`: ButtonHandler Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Button.h"
#include "ButtonGesture.h"
#include "Timer.h"

class ButtonHandler
{
    public:

    // ---------------------
    // [Public] Enumerations
    // ---------------------

    enum class State : uint8_t
    {
        IDLE,
        PENDING,
    };

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    ButtonHandler() = delete;
    ButtonHandler(Button& btn,uint16_t hold_time);
    ~ButtonHandler();

    // -----------------------
    // [Public] Member Methods
    // -----------------------
    
    void process();
    void reset();
    State getState() const;
    ButtonHandler& onPress(ButtonCallback callback,void* context);
    ButtonHandler& onHold(ButtonCallback callback,void* context);

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    Button& btn;
    uint16_t hold_time;
    ButtonGesture gesture;
    State state;
    Timer timer;
};

// ------------
// Type Aliases
// ------------

using ButtonState = ButtonHandler::State;