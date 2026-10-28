/**
 * @file ButtonGesture.h
 * 
 * @brief `MIDI-GP`: ButtonGesture Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

class ButtonGesture
{
    public:

    // ---------------------
    // [Public] Type Aliases
    // ---------------------
    
    using Callback = void (*)(void*);

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    ButtonGesture();
    ~ButtonGesture();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    ButtonGesture& onPress(Callback callback,void* context);
    ButtonGesture& onHold(Callback callback,void* context);
    void triggerPressCallback() const;
    void triggerHoldCallback() const;

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    Callback press_callback;
    Callback hold_callback;
    void* press_context;
    void* hold_context;
};

// ------------
// Type Aliases
// ------------

using ButtonCallback = ButtonGesture::Callback;