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

#define ssid1       "xxxxx"
#define password1   "xxxxx"

#define ntp_server "europe.pool.ntp.org"
// See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
#define my_timezone "CET-1CEST,M3.5.0,M10.5.0/3" // Europe/Brussels

#define DEFAULT_PATTERN_ID 4

#define LED_PIN           D4
#define LDR_PIN           A0
