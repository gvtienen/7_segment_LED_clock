/*
   7-segment-LED-clock: https://github.com/gvtienen/7_segment_LED_clock
   Copyright (C) 2023 Geert Vantienen

   This file is part of 7-segment-LED-clock:
   7-segment-LED-clock is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <Arduino.h>
#include "Configuration.h"
#include "MyWifi.h"
#include "LEDStrip.h"
#include "WebServer.h"

enum class ClockStatus : char { startup, waitingForWifi, showTime};

class LEDClock
{
  public:
    LEDClock();
    void setup();
    void loop();
    
  private:
    String get_version() const;
    void updateTime();
	  void handleStartup();
	  void handleWaitingForWifi();
	  void handleShowTime();
	  void handleLDRSensor();
    
  private:
    Configuration config;
	  ClockStatus status;
    unsigned long previousMillis;
	  MyWifi wifi;
	  LEDStrip leds;
    WebServer web;
};
