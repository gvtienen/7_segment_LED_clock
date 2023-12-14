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

/* ************************************************************************************************
 *  
 *  7-segment-LED-clock
 *  
 ***************************************************************************************************
 * HW         : Wemos D1 mini + WS2812B ledstrip
 *              See: https://www.printables.com/model/610020-big-wall-mounted-7-segment-led-clock
 * Board      : LOLIN(WEMOS) D1 R2 & mini
 * Needed libs: FastLED (version 3.6.0)
 ***************************************************************************************************/

#include "LEDClock.h"

LEDClock ledclock;
void setup()
{
  ledclock.setup();
}

void loop()
{
  ledclock.loop();
}
