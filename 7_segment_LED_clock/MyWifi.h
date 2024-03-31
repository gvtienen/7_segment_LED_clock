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

class Configuration;

enum class WifiStatus : char { startup, connecting, connected};

class MyWifi
{
  public:
    MyWifi(const Configuration& config);
    void setup();
    void loop();
    bool isConnected() const;
    void setWebserverIsStarted();
    void getTime(uint8_t& hours, uint8_t& minutes);

  private:
    void handleStartup();
    void handleConnecting();
    void handleConnected();
    void init_time();

  private:
    const Configuration& config;
    WifiStatus status;
    unsigned long previousMillis;
};
