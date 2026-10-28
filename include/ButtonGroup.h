/**
 * @file ButtonGroup.h
 * 
 * @brief `MIDI-GP`: ButtonGroup Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Button.h"
#include "ButtonGesture.h"
#include "ButtonHandler.h"
#include "Timer.h"

class ButtonGroup
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    ButtonGroup() = delete;
    ButtonGroup(Button& btn_1,Button& btn_2,uint16_t group_time,uint16_t hold_time);
    ~ButtonGroup();

    // -----------------------
    // [Public] Member Methods
    // -----------------------
    
    void process();
    void reset();
    ButtonHandler& firstButtonHandler();
    ButtonHandler& secondButtonHandler();
    ButtonGroup& onPress(ButtonCallback callback,void* context);
    ButtonGroup& onHold(ButtonCallback callback,void* context);
    
    private:

    // ------------------------
    // [Private] Member Methods
    // ------------------------

    void processGroup();

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    Button& btn_1;
    Button& btn_2;
    uint16_t group_time;
    uint16_t hold_time;
    ButtonHandler btn_1_handler;
    ButtonHandler btn_2_handler;
    ButtonGesture group_gesture;
    ButtonState group_state;
    Timer group_timer;
};