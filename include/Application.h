/**
 * @file Application.h
 * 
 * @brief `MIDI-GP`: Application Class Header File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date October 2026
 */
#pragma once

#include <stdint.h>

#include "Button.h"
#include "ButtonGroup.h"
#include "ButtonHandler.h"
#include "Calibrator.h"
#include "ExpressionPedal.h"
#include "Jack.h"
#include "Led.h"
#include "LedOperator.h"
#include "MidiController.h"
#include "Potentiometer.h"
#include "Toggle.h"

class Application
{
    public:

    // -----------------------------------------
    // [Public] Constructor & Destructor Methods
    // -----------------------------------------

    Application();
    ~Application();

    // -----------------------
    // [Public] Member Methods
    // -----------------------

    void begin();
    void process();

    private:

    // ----------------------
    // [Private] Enumerations
    // ----------------------

    enum class PedalMode : uint8_t
    {
        OPERATION,
        CALIBRATION
    };

    // -----------------
    // [Private] Structs
    // -----------------

    struct CalibrationData
    {
        uint8_t id;
        uint16_t min_value;
        uint16_t max_value;
    };

    // ------------------------
    // [Private] Static Methods
    // ------------------------

    static Application* castContext(void* context);
    static void buttonPressCallback1(void* context);
    static void buttonPressCallback2(void* context);
    static void buttonPressCallback3(void* context);
    static void buttonPressCallback4(void* context);
    static void buttonPressCallback5(void* context);
    static void buttonPressCallback12(void* context);
    static void buttonPressCallback34(void* context);
    static void buttonHoldCallback1(void* context);
    static void buttonHoldCallback2(void* context);
    static void buttonHoldCallback3(void* context);
    static void buttonHoldCallback4(void* context);
    static void buttonHoldCallback5(void* context);
    static void buttonHoldCallback12(void* context);
    static void buttonHoldCallback34(void* context);
    static void controlChangeCallback(void* context,uint8_t cc_number,uint8_t cc_value);
    static void programChangeCallback(void* context,uint8_t pc_number);

    // ------------------------
    // [Private] Member Methods
    // ------------------------

    void initHardware();
    void initComponents();
    void assignCallbacks();
    void loadCalibrationData();
    void saveCalibrationData();
    void togglePedalMode();
    void beginCalibration();
    void endCalibration();
    void processButtons();
    void processButtons12();
    void processButtons34();
    void processButton5();
    void processExpressionPedal();
    void processOperationMode();
    void processCalibrationMode();
    void handleButtonGesture(Toggle& toggle,uint8_t cc_number);
    void handleButtonPress1();
    void handleButtonPress2();
    void handleButtonPress3();
    void handleButtonPress4();
    void handleButtonPress5();
    void handleButtonPress12();
    void handleButtonPress34();
    void handleButtonHold1();
    void handleButtonHold2();
    void handleButtonHold3();
    void handleButtonHold4();
    void handleButtonHold5();
    void handleButtonHold12();
    void handleButtonHold34();
    void handlePedalMovement();
    void handleControlChange(uint8_t cc_number,uint8_t cc_value);
    void handleProgramChange(uint8_t pc_number);
    void logJackConnection(const char* id) const;
    void logJackDisconnection(const char* id) const;
    void logButtonPress(const char* id) const;
    void logButtonHold(const char* id) const;
    void logCalibrationInitialization() const;
    void logCalibrationCompletion() const;
    void logCalibratorRawValue() const;
    void logControlChangeMessage(uint8_t cc_number,uint8_t cc_value) const;
    void logProgramChangeMessage(uint8_t pc_number) const;

    // --------------------------
    // [Private] Member Variables
    // --------------------------

    PedalMode mode;
    Jack jack_trs;
    Jack jack_ts;
    Button btn_1;
    Button btn_2;
    Button btn_3;
    Button btn_4;
    Button btn_5;
    ButtonGroup btn_12_group;
    ButtonGroup btn_34_group;
    ButtonHandler btn_5_handler;
    Toggle btn_1_press_toggle;
    Toggle btn_2_press_toggle;
    Toggle btn_3_press_toggle;
    Toggle btn_4_press_toggle;
    Toggle btn_5_press_toggle;
    Toggle btn_12_press_toggle;
    Toggle btn_34_press_toggle;
    Toggle btn_1_hold_toggle;
    Toggle btn_2_hold_toggle;
    Toggle btn_3_hold_toggle;
    Toggle btn_4_hold_toggle;
    Toggle btn_5_hold_toggle;
    Toggle btn_34_hold_toggle;
    Jack jack_exp;
    Potentiometer pot;
    ExpressionPedal pedal;
    Calibrator calibrator;
    Led led;
    LedOperator led_operator;
    MidiController midi;
};