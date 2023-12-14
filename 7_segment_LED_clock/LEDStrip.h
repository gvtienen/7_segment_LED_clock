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
enum class ClockModus : char { none, wifiConnect, selfTest1, showTime};

class LEDStrip
{
  public:
    LEDStrip();
    void setup();
    void loop();
    void updateTime(uint8_t hours, uint8_t minutes);
    void setModus(ClockModus modus);
    //TODO setBrightness()

  private:
    void handleModusWifiConnect();
    void handleModusShowTime();

  private:
    ClockModus modus;
    unsigned long previousMillis;
    uint8_t current_hours;
    uint8_t current_minutes;
};
