/**
 * @file MidiController.cpp
 * 
 * @brief `MIDI-GP`: MidiController Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#include "MidiController.h"

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE()

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

MidiController::MidiController(uint8_t channel)
{
    this->channel = channel;
    this->cc_callback = nullptr;
    this->pc_callback = nullptr;
    this->cc_context = nullptr;
    this->pc_context = nullptr;
}
MidiController::~MidiController() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void MidiController::init() const
{
    MIDI.begin(this->channel);
    MIDI.turnThruOff();
}
void MidiController::process() const
{
    if(!MIDI.read())
    {
        return;
    }

    midi::MidiType type = MIDI.getType();
    uint8_t data_1 = MIDI.getData1();
    uint8_t data_2 = MIDI.getData2();

    if(type == midi::MidiType::ControlChange)
    {
        this->triggerControlChangeCallback(data_1,data_2);
    }
    else if(type == midi::MidiType::ProgramChange)
    {
        this->triggerProgramChangeCallback(data_1);
    }
}
uint8_t MidiController::getChannel() const
{
    return this->channel;
}
void MidiController::sendControlChange(uint8_t cc_number,uint8_t cc_value) const
{
    MIDI.sendControlChange(cc_number,cc_value,this->channel);
}
void MidiController::sendProgramChange(uint8_t pc_number) const
{
    MIDI.sendProgramChange(pc_number,this->channel);
}
MidiController& MidiController::onControlChange(ControlChangeCallback callback,void* context)
{
    this->cc_callback = callback;
    this->cc_context = context;
    return *this;
}
MidiController& MidiController::onProgramChange(ProgramChangeCallback callback,void* context)
{
    this->pc_callback = callback;
    this->pc_context = context;
    return *this;
}

// ------------------------
// [Private] Member Methods
// ------------------------

void MidiController::triggerControlChangeCallback(uint8_t cc_number,uint8_t cc_value) const
{
    if(this->cc_callback != nullptr)
    {
        this->cc_callback(this->cc_context,cc_number,cc_value);
    }
}
void MidiController::triggerProgramChangeCallback(uint8_t pc_number) const
{
    if(this->pc_callback != nullptr)
    {
        this->pc_callback(this->pc_context,pc_number);
    }
}