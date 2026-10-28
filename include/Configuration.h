/**
 * @file Configuration.h
 * 
 * @brief `MIDI-GP`: Configuration Namespace File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date October 2026
 */
#pragma once

#include <stdint.h>

namespace cfg
{
    // --------------------
    // Button Configuration
    // --------------------

    constexpr uint8_t BUTTON_1_PIN = 10;
    constexpr uint8_t BUTTON_2_PIN = 9;
    constexpr uint8_t BUTTON_3_PIN = 16;
    constexpr uint8_t BUTTON_4_PIN = 14;
    constexpr uint8_t BUTTON_5_PIN = 7;
    constexpr uint16_t BUTTON_DEBOUNCE_TIME = 20;
    constexpr uint16_t BUTTON_GROUP_TIME = 150;
    constexpr uint16_t BUTTON_HOLD_TIME = 500;

    // ------------------------------
    // Expression Pedal Configuration
    // ------------------------------

    constexpr uint8_t PEDAL_CC_MIN = 0;
    constexpr uint8_t PEDAL_CC_MAX = 127;
    constexpr uint16_t PEDAL_RAW_MIN = 0;
    constexpr uint16_t PEDAL_RAW_MAX = 1023;
    constexpr uint16_t PEDAL_DEADZONE = 5;
    constexpr uint16_t PEDAL_THRESHOLD = 5;

    // ------------------
    // Jack Configuration
    // ------------------

    constexpr uint8_t JACK_TRS_PIN = 15;
    constexpr uint8_t JACK_TS_PIN = 8;
    constexpr uint8_t JACK_EXP_PIN = 6;
    constexpr uint16_t JACK_DEBOUNCE_TIME = 300;

    // -----------------
    // LED Configuration
    // -----------------

    constexpr uint8_t LED_PIN = 2;
    constexpr uint16_t LED_FLASH_TIME = 100;
    constexpr uint16_t LED_BLINK_TIME = 250;

    // --------------------
    // Logger Configuration
    // --------------------

    constexpr uint32_t LOGGER_BAUD_RATE = 9600;

    // --------------------
    // Memory Configuration
    // --------------------

    constexpr uint8_t MEMORY_CALIBRATION_ID = 0xCA;
    constexpr uint16_t MEMORY_CALIBRATION_ADDRESS = 0;

    // -----------------------------
    // MIDI Controller Configuration
    // -----------------------------

    constexpr uint8_t MIDI_CHANNEL = 1;
    constexpr uint8_t MIDI_VALUE_ON = 100;
    constexpr uint8_t MIDI_VALUE_OFF = 0;
    constexpr uint8_t MIDI_CC_BUTTON_1_PRESS = 61;
    constexpr uint8_t MIDI_CC_BUTTON_2_PRESS = 93;
    constexpr uint8_t MIDI_CC_BUTTON_3_PRESS = 75;
    constexpr uint8_t MIDI_CC_BUTTON_4_PRESS = 28;
    constexpr uint8_t MIDI_CC_BUTTON_5_PRESS = 50;
    constexpr uint8_t MIDI_CC_BUTTONS_12_PRESS = 60;
    constexpr uint8_t MIDI_CC_BUTTONS_34_PRESS = 65;
    constexpr uint8_t MIDI_CC_BUTTON_1_HOLD = 67;
    constexpr uint8_t MIDI_CC_BUTTON_2_HOLD = 96;
    constexpr uint8_t MIDI_CC_BUTTON_3_HOLD = 20;
    constexpr uint8_t MIDI_CC_BUTTON_4_HOLD = 13;
    constexpr uint8_t MIDI_CC_BUTTON_5_HOLD = 59;
    constexpr uint8_t MIDI_CC_BUTTONS_34_HOLD = 68;
    constexpr uint8_t MIDI_CC_EXPRESSION = 12;
    
    // ---------------------------
    // Potentiometer Configuration
    // ---------------------------
    
    constexpr uint8_t POTENTIOMETER_PIN = 21;

    // --------------------
    // Toggle Configuration
    // --------------------

    constexpr uint8_t TOGGLE_BUTTON_1_PRESS_ON = false;
    constexpr uint8_t TOGGLE_BUTTON_2_PRESS_ON = false;
    constexpr uint8_t TOGGLE_BUTTON_3_PRESS_ON = false;
    constexpr uint8_t TOGGLE_BUTTON_4_PRESS_ON = false;
    constexpr uint8_t TOGGLE_BUTTON_5_PRESS_ON = false;
    constexpr uint8_t TOGGLE_BUTTONS_12_PRESS_ON = false;
    constexpr uint8_t TOGGLE_BUTTONS_34_PRESS_ON = false;
    constexpr uint8_t TOGGLE_BUTTON_1_HOLD_ON = true;
    constexpr uint8_t TOGGLE_BUTTON_2_HOLD_ON = true;
    constexpr uint8_t TOGGLE_BUTTON_3_HOLD_ON = false;
    constexpr uint8_t TOGGLE_BUTTON_4_HOLD_ON = false;
    constexpr uint8_t TOGGLE_BUTTON_5_HOLD_ON = false;
    constexpr uint8_t TOGGLE_BUTTONS_34_HOLD_ON = false;
}

// -----------------
// Macro Definitions
// -----------------

#define DEBUG 0