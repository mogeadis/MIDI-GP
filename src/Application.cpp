/**
 * @file Application.cpp
 * 
 * @brief `MIDI-GP`: Application Class Implementation File 
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @version 1.0.0
 * @date October 2026
 */
#include "Application.h"

#include "Configuration.h"
#include "Logger.h"
#include "Memory.h"

// -----------------------------------------
// [Public] Constructor & Destructor Methods
// -----------------------------------------

Application::Application() :
    jack_trs(cfg::JACK_TRS_PIN,cfg::JACK_DEBOUNCE_TIME),
    jack_ts(cfg::JACK_TS_PIN,cfg::JACK_DEBOUNCE_TIME),
    btn_1(cfg::BUTTON_1_PIN,cfg::BUTTON_DEBOUNCE_TIME),
    btn_2(cfg::BUTTON_2_PIN,cfg::BUTTON_DEBOUNCE_TIME),
    btn_3(cfg::BUTTON_3_PIN,cfg::BUTTON_DEBOUNCE_TIME),
    btn_4(cfg::BUTTON_4_PIN,cfg::BUTTON_DEBOUNCE_TIME),
    btn_5(cfg::BUTTON_5_PIN,cfg::BUTTON_DEBOUNCE_TIME),
    btn_12_group(btn_1,btn_2,cfg::BUTTON_GROUP_TIME,cfg::BUTTON_HOLD_TIME),
    btn_34_group(btn_3,btn_4,cfg::BUTTON_GROUP_TIME,cfg::BUTTON_HOLD_TIME),
    btn_5_handler(btn_5,cfg::BUTTON_HOLD_TIME),
    btn_1_press_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_1_PRESS_ON),
    btn_2_press_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_2_PRESS_ON),
    btn_3_press_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_3_PRESS_ON),
    btn_4_press_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_4_PRESS_ON),
    btn_5_press_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_5_PRESS_ON),
    btn_12_press_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTONS_12_PRESS_ON),
    btn_34_press_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTONS_34_PRESS_ON),
    btn_1_hold_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_1_HOLD_ON),
    btn_2_hold_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_2_HOLD_ON),
    btn_3_hold_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_3_HOLD_ON),
    btn_4_hold_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_4_HOLD_ON),
    btn_5_hold_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTON_5_HOLD_ON),
    btn_34_hold_toggle(cfg::MIDI_VALUE_ON,cfg::MIDI_VALUE_OFF,cfg::TOGGLE_BUTTONS_34_HOLD_ON),
    jack_exp(cfg::JACK_EXP_PIN,cfg::JACK_DEBOUNCE_TIME),
    pot(cfg::POTENTIOMETER_PIN),
    pedal(pot,cfg::PEDAL_CC_MIN,cfg::PEDAL_CC_MAX,cfg::PEDAL_RAW_MIN,cfg::PEDAL_RAW_MAX,cfg::PEDAL_DEADZONE,cfg::PEDAL_THRESHOLD),
    calibrator(pot),
    led(cfg::LED_PIN),
    led_operator(led,cfg::LED_FLASH_TIME,cfg::LED_BLINK_TIME),
    midi(cfg::MIDI_CHANNEL)
{
    this->mode = PedalMode::OPERATION;
}
Application::~Application() = default;

// -----------------------
// [Public] Member Methods
// -----------------------

void Application::begin()
{
    DBG_INIT(cfg::LOGGER_BAUD_RATE);
    this->initHardware();
    this->assignCallbacks();
    this->loadCalibrationData();
    this->initComponents();
    this->led_operator.flash();
    DBG_PRINTLN("\nDevice initialized");
}
void Application::process()
{
    this->midi.process();
    this->processButtons();
    this->processExpressionPedal();
    this->led_operator.process();
}

// ------------------------
// [Private] Static Methods
// ------------------------

Application* Application::castContext(void* context)
{
    return static_cast<Application*>(context);
}
void Application::buttonPressCallback1(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonPress1();
}
void Application::buttonPressCallback2(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonPress2();
}
void Application::buttonPressCallback3(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonPress3();
}
void Application::buttonPressCallback4(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonPress4();
}
void Application::buttonPressCallback5(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonPress5();
}
void Application::buttonPressCallback12(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonPress12();
}
void Application::buttonPressCallback34(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonPress34();
}
void Application::buttonHoldCallback1(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonHold1();
}
void Application::buttonHoldCallback2(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonHold2();
}
void Application::buttonHoldCallback3(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonHold3();
}
void Application::buttonHoldCallback4(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonHold4();
}
void Application::buttonHoldCallback5(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonHold5();
}
void Application::buttonHoldCallback12(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonHold12();
}
void Application::buttonHoldCallback34(void* context)
{
    Application* app = Application::castContext(context);
    app->handleButtonHold34();
}
void Application::controlChangeCallback(void* context,uint8_t cc_number,uint8_t cc_value)
{
    Application* app = Application::castContext(context);
    app->handleControlChange(cc_number,cc_value);
}
void Application::programChangeCallback(void* context,uint8_t pc_number)
{
    Application* app = Application::castContext(context);
    app->handleProgramChange(pc_number);
}

// ------------------------
// [Private] Member Methods
// ------------------------

void Application::initHardware()
{
    this->jack_trs.init();
    this->jack_ts.init();
    this->btn_1.init();
    this->btn_2.init();
    this->btn_3.init();
    this->btn_4.init();
    this->btn_5.init();
    this->jack_exp.init();
    this->led.init();
}
void Application::initComponents()
{
    this->pedal.init();
    this->midi.init();
}
void Application::assignCallbacks()
{
    this->btn_12_group.firstButtonHandler().onPress(Application::buttonPressCallback1,this).onHold(Application::buttonHoldCallback1,this);
    this->btn_12_group.secondButtonHandler().onPress(Application::buttonPressCallback2,this).onHold(Application::buttonHoldCallback2,this);
    this->btn_12_group.onPress(Application::buttonPressCallback12,this).onHold(Application::buttonHoldCallback12,this);
    this->btn_34_group.firstButtonHandler().onPress(Application::buttonPressCallback3,this).onHold(Application::buttonHoldCallback3,this);
    this->btn_34_group.secondButtonHandler().onPress(Application::buttonPressCallback4,this).onHold(Application::buttonHoldCallback4,this);
    this->btn_34_group.onPress(Application::buttonPressCallback34,this).onHold(Application::buttonHoldCallback34,this);
    this->btn_5_handler.onPress(Application::buttonPressCallback5,this).onHold(Application::buttonHoldCallback5,this);
    this->midi.onControlChange(Application::controlChangeCallback,this).onProgramChange(Application::programChangeCallback,this);
}
void Application::loadCalibrationData()
{
    CalibrationData data;
    Memory::read(cfg::MEMORY_CALIBRATION_ADDRESS,data);
    if(data.id != cfg::MEMORY_CALIBRATION_ID)
    {
        return;
    }
    this->pedal.assignLowerBound(data.min_value);
    this->pedal.assignUpperBound(data.max_value);
}
void Application::saveCalibrationData()
{
    CalibrationData data{cfg::MEMORY_CALIBRATION_ID,this->calibrator.minValue(),this->calibrator.maxValue()};
    Memory::write(cfg::MEMORY_CALIBRATION_ADDRESS,data);
}
void Application::togglePedalMode()
{
    if(this->mode == PedalMode::OPERATION)
    {
        this->beginCalibration();
        this->mode = PedalMode::CALIBRATION;
    }
    else if(this->mode == PedalMode::CALIBRATION)
    {
        this->endCalibration();
        this->mode = PedalMode::OPERATION;
    }
}
void Application::beginCalibration()
{
    this->calibrator.begin();
    this->led_operator.startBlinking();
    this->logCalibrationInitialization();
}
void Application::endCalibration()
{
    this->saveCalibrationData();
    this->loadCalibrationData();
    this->led_operator.stopBlinking();
    this->logCalibrationCompletion();
}
void Application::processButtons()
{
    this->processButtons12();
    this->processButtons34();
    this->processButton5();
}
void Application::processButtons12()
{
    this->btn_1.update();
    this->btn_2.update();
    this->btn_12_group.process();
}
void Application::processButtons34()
{
    this->jack_trs.update();
    if(this->jack_trs.changed())
    {
        const char* id = "TRS";
        if(this->jack_trs.connected())
        {
            this->logJackConnection(id);
        }
        else
        {
            this->logJackDisconnection(id);
            this->btn_34_group.reset();
        }
    }
    if(!this->jack_trs.connected())
    {
        return;
    }
    this->btn_3.update();
    this->btn_4.update();
    this->btn_34_group.process();
}
void Application::processButton5()
{
    this->jack_ts.update();
    if(this->jack_ts.changed())
    {
        const char* id = "TS";
        if(this->jack_ts.connected())
        {
            this->logJackConnection(id);
        }
        else
        {
            this->logJackDisconnection(id);
            this->btn_5_handler.reset();
        }
    }
    if(!this->jack_ts.connected())
    {
        return;
    }
    this->btn_5.update();
    this->btn_5_handler.process();
}
void Application::processExpressionPedal()
{
    if(this->mode == PedalMode::OPERATION)
    {
        this->processOperationMode();
    }
    else if(this->mode == PedalMode::CALIBRATION)
    {
        this->processCalibrationMode();
    }
}
void Application::processOperationMode()
{
    this->jack_exp.update();
    if(this->jack_exp.changed())
    {
        const char* id = "EXP";
        if(this->jack_exp.connected())
        {
            this->logJackConnection(id);
        }
        else
        {
            this->logJackDisconnection(id);
        }
    }
    if(!this->jack_exp.connected())
    {
        return;
    }
    if(this->pedal.update())
    {
        this->handlePedalMovement();
    }
}
void Application::processCalibrationMode()
{
    if(this->calibrator.update())
    {
        this->logCalibratorRawValue();
    }
}
void Application::handleButtonGesture(Toggle& toggle,uint8_t cc_number)
{
    if(this->mode == PedalMode::CALIBRATION)
    {
        return;
    }
    this->led_operator.flash();
    uint8_t cc_value = toggle.trigger();
    this->midi.sendControlChange(cc_number,cc_value);
    this->logControlChangeMessage(cc_number,cc_value);
}
void Application::handleButtonPress1()
{
    this->logButtonPress("1");
    this->handleButtonGesture(this->btn_1_press_toggle,cfg::MIDI_CC_BUTTON_1_PRESS);
}
void Application::handleButtonPress2()
{
    this->logButtonPress("2");
    this->handleButtonGesture(this->btn_2_press_toggle,cfg::MIDI_CC_BUTTON_2_PRESS);
}
void Application::handleButtonPress3()
{
    this->logButtonPress("3");
    this->handleButtonGesture(this->btn_3_press_toggle,cfg::MIDI_CC_BUTTON_3_PRESS);
}
void Application::handleButtonPress4()
{
    this->logButtonPress("4");
    this->handleButtonGesture(this->btn_4_press_toggle,cfg::MIDI_CC_BUTTON_4_PRESS);
}
void Application::handleButtonPress5()
{
    this->logButtonPress("5");
    this->handleButtonGesture(this->btn_5_press_toggle,cfg::MIDI_CC_BUTTON_5_PRESS);
}
void Application::handleButtonPress12()
{
    this->logButtonPress("1 & 2");
    this->handleButtonGesture(this->btn_12_press_toggle,cfg::MIDI_CC_BUTTONS_12_PRESS);
}
void Application::handleButtonPress34()
{
    this->logButtonPress("3 & 4");
    this->handleButtonGesture(this->btn_34_press_toggle,cfg::MIDI_CC_BUTTONS_34_PRESS);
}
void Application::handleButtonHold1()
{
    this->logButtonHold("1");
    this->handleButtonGesture(this->btn_1_hold_toggle,cfg::MIDI_CC_BUTTON_1_HOLD);
}
void Application::handleButtonHold2()
{
    this->logButtonHold("2");
    this->handleButtonGesture(this->btn_2_hold_toggle,cfg::MIDI_CC_BUTTON_2_HOLD);
}
void Application::handleButtonHold3()
{
    this->logButtonHold("3");
    this->handleButtonGesture(this->btn_3_hold_toggle,cfg::MIDI_CC_BUTTON_3_HOLD);
}
void Application::handleButtonHold4()
{
    this->logButtonHold("4");
    this->handleButtonGesture(this->btn_4_hold_toggle,cfg::MIDI_CC_BUTTON_4_HOLD);
}
void Application::handleButtonHold5()
{
    this->logButtonHold("5");
    this->handleButtonGesture(this->btn_5_hold_toggle,cfg::MIDI_CC_BUTTON_5_HOLD);
}
void Application::handleButtonHold12()
{
    this->logButtonHold("1 & 2");
    this->togglePedalMode();
}
void Application::handleButtonHold34()
{
    this->logButtonHold("3 & 4");
    this->handleButtonGesture(this->btn_34_hold_toggle,cfg::MIDI_CC_BUTTONS_34_HOLD);
}
void Application::handlePedalMovement()
{
    this->led_operator.flash();
    uint8_t cc_value = this->pedal.value();
    this->midi.sendControlChange(cfg::MIDI_CC_EXPRESSION,cc_value);
    this->logControlChangeMessage(cfg::MIDI_CC_EXPRESSION,cc_value);
}
void Application::handleControlChange(uint8_t cc_number,uint8_t cc_value)
{
    this->led_operator.flash();
    this->midi.sendControlChange(cc_number,cc_value);
    this->logControlChangeMessage(cc_number,cc_value);
}
void Application::handleProgramChange(uint8_t pc_number)
{
    this->led_operator.flash();
    this->midi.sendProgramChange(pc_number);
    this->logProgramChangeMessage(pc_number);
}
void Application::logJackConnection(const char* id) const
{
    DBG_PRINT("Jack ");
    DBG_PRINT(id);
    DBG_PRINTLN(" connected");
}
void Application::logJackDisconnection(const char *id) const
{
    DBG_PRINT("Jack ");
    DBG_PRINT(id);
    DBG_PRINTLN(" disconnected");
}
void Application::logButtonPress(const char* id) const
{
    DBG_PRINT("Button(s) ");
    DBG_PRINT(id);
    DBG_PRINTLN(" pressed");
}
void Application::logButtonHold(const char* id) const
{
    DBG_PRINT("Button(s) ");
    DBG_PRINT(id);
    DBG_PRINTLN(" held");
}
void Application::logCalibrationInitialization() const
{
    DBG_PRINTLN("Calibration process initialized:");
    DBG_PRINTLN("Move the pedal through its full range and hold buttons 1 & 2 to finish...");
}
void Application::logCalibrationCompletion() const
{
    DBG_PRINTLN("Calibration process completed:");
    DBG_PRINTLN("The following data has been saved to memory:");
    DBG_PRINT("[*] Min raw value: ");
    DBG_PRINTLN(this->calibrator.minValue());
    DBG_PRINT("[*] Max raw value: ");
    DBG_PRINTLN(this->calibrator.maxValue());
}
void Application::logCalibratorRawValue() const
{
    DBG_PRINT("Raw value: ");
    DBG_PRINTLN(this->calibrator.rawValue());
}
void Application::logControlChangeMessage(uint8_t cc_number,uint8_t cc_value) const
{
    DBG_PRINT("[MIDI CC] ");
    DBG_PRINT("Channel: ");
    DBG_PRINT(this->midi.getChannel());
    DBG_PRINT(" | Number: ");
    DBG_PRINT(cc_number);
    DBG_PRINT(" | Value: ");
    DBG_PRINTLN(cc_value);
}
void Application::logProgramChangeMessage(uint8_t pc_number) const
{
    DBG_PRINT("[MIDI PC] ");
    DBG_PRINT("Channel: ");
    DBG_PRINT(this->midi.getChannel());
    DBG_PRINT(" | Number: ");
    DBG_PRINTLN(pc_number);
}