/**
 * @file MidiController.h
 * 
 * @brief `MIDI-GP`: MidiController Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

class MidiController
{
    public:

    // ---------------------
    // [Public] Type Aliases
    // ---------------------
    
    using ControlChangeCallback = void (*)(void*,uint8_t,uint8_t);
    using ProgramChangeCallback = void (*)(void*,uint8_t);

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    MidiController() = delete;
    MidiController(uint8_t channel);
    ~MidiController();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void init() const;
    void process() const;
    uint8_t getChannel() const;
    void sendControlChange(uint8_t cc_number,uint8_t cc_value) const;
    void sendProgramChange(uint8_t pc_number) const;
    MidiController& onControlChange(ControlChangeCallback callback,void* context);
    MidiController& onProgramChange(ProgramChangeCallback callback,void* context);

    private:

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    uint8_t channel;
    ControlChangeCallback cc_callback;
    ProgramChangeCallback pc_callback;
    void* cc_context;
    void* pc_context;

    // ------------------------
    // [Private] Member Methods
    // ------------------------

    void triggerControlChangeCallback(uint8_t cc_number,uint8_t cc_value) const;
    void triggerProgramChangeCallback(uint8_t pc_number) const;
};

// ------------
// Type Aliases
// ------------

using MidiControlChangeCallback = MidiController::ControlChangeCallback;
using MidiProgramChangeCallback = MidiController::ProgramChangeCallback;