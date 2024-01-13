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


enum class ClockFunction : char {time=0, selftest, countdown};
enum class ColorPattern : char {solid=0, hline, vline, solidDuo, rainbow, matrix, fire, sunset, max};

class Configuration
{
  public:
    Configuration();
    void setup();

    void setClockFunction(ClockFunction cf);
    void setColorPattern(ColorPattern cp);
    void setColor(uint32_t col);

    const char* getHostName() const;
    ClockFunction getClockFunction() const;
    ColorPattern getColorPattern() const;
    uint32_t getColor() const;

  private:
    ClockFunction function;
    ColorPattern  pattern;
    uint32_t      color;
};