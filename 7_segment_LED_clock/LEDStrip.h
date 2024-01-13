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
#include "LEDLib.h"

enum class ClockModus : char { none, wifiConnect, selfTest1, showTime};

class LEDStrip
{
  public:
    LEDStrip(const Configuration& config);
    void setup();
    void loop();
    void updateTime(uint8_t hours, uint8_t minutes);
    void setModus(ClockModus modus);
    //TODO setBrightness()

  private:
    void handleModusWifiConnect();
    void handleModusShowTime();
    void showTime(uint8_t hours, uint8_t minutes);
    void showNumber(int digitId, uint8_t num);
    void showDots(bool dotHigh, bool dotLow);
    void initPatternColors();
    void updatePatternColors();
    CRGB get_led_color(int digit_id, char segment, int lednr);
    CRGB get_dots_color(int dot_id);

  private:
    const Configuration& config;
    ClockModus modus;
    ColorPattern pattern;
    unsigned long previousMillis;
    uint8_t current_hours;
    uint8_t current_minutes;
};
