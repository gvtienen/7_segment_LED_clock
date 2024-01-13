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

#include "LEDClock.h"
#include "config.h"
#include "Configuration.h"

String LEDClock::get_version() const
{
  return "0.2";
}

LEDClock::LEDClock()
  : config(),
    status(ClockStatus::startup),
    previousMillis(0),
    wifi(config),
    leds(config),
    web(config)
{}

void LEDClock::setup()
{
  Serial.begin(115200); // 115200 by default
  delay(100);
  Serial.print("\n\n   *** Booting 7-segment-LED-clock v");
  Serial.print(get_version());
  Serial.println("   ***\n");
  pinMode(LDR_PIN, INPUT);
  config.setup();
  wifi.setup();
  leds.setup();
}

void LEDClock::handleStartup()
{
  status = ClockStatus::waitingForWifi;
  leds.setModus(ClockModus::wifiConnect);
}

void LEDClock::handleWaitingForWifi()
{
	if (wifi.isConnected())
  {
    updateTime();
    status = ClockStatus::showTime;
    previousMillis = millis();
    leds.setModus(ClockModus::showTime);
    web.setup();
    wifi.setWebserverIsStarted();
  }
}

void LEDClock::updateTime()
{
    uint8_t hours = 0;
    uint8_t minutes = 0;
    wifi.getTime(hours, minutes);
    leds.updateTime(hours, minutes);
}

void LEDClock::handleShowTime()
{
  static uint32_t counter = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) // every 1s
  {
    counter++;
    previousMillis = currentMillis;
    updateTime();
    if ((counter % 20) == 0) // every 20s
    {
      handleLDRSensor();
    }
  }
}

void LEDClock::handleLDRSensor()
{
    int ldrValue = analogRead(LDR_PIN);
    Serial.print("LDR value = ");
    Serial.println(ldrValue);
    // Still TODO: set brightness
}

void LEDClock::loop()
{
  switch(status)
  {
    case ClockStatus::startup : handleStartup(); break;
    case ClockStatus::waitingForWifi : handleWaitingForWifi(); break;
    case ClockStatus::showTime : handleShowTime(); break;
  }
  wifi.loop();
  yield();
  leds.loop();
  yield();
  web.loop();
  delay(10);
}
