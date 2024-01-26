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

#include "Configuration.h"
#include "config.h"

Configuration::Configuration()
  : function(ClockFunction::time),
    pattern(ColorPattern(DEFAULT_PATTERN_ID)),
    color(0xff0000) // Red
{
}

void Configuration::setup()
{
}

void Configuration::setClockFunction(ClockFunction cf)
{
    function = cf;
}

void Configuration::setColorPattern(ColorPattern cp)
{
    pattern = cp;
}

void Configuration::setColor(uint32_t col)
{
    color = col;
}

const char* Configuration::getHostName() const
{
    return "ledclock";
}

ClockFunction Configuration::getClockFunction() const
{
    return function;
}

ColorPattern Configuration::getColorPattern() const
{
    return pattern;
}

uint32_t Configuration::getColor() const
{
    return color;
}
