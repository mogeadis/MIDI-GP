/**
 * @file main.cpp
 * 
 * @brief `MIDI-GP`: Main File
 * 
 * @author Alexandros Iliadis (https://github.com/mogeadis)
 * @date 26-10-2026
 */
#include <Arduino.h>

#include "Application.h"

static Application app;

void setup()
{
    app.begin();
}

void loop()
{
    app.process();
}