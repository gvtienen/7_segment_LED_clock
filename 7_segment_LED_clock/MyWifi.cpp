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

#include "MyWifi.h"
#include "config.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntp_server, timezone_offset, 60000);// server, offset, interval_ms
int sta_retry = 0;
int sta_max_retries = 30;
unsigned long previousMillis = 0;


MyWifi::MyWifi()
  : status(WifiStatus::startup)
{}

void wifi_connect_to(const char* ssid, const char* passwd)
{
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(ssid, passwd);
  Serial.print(ssid);
  sta_retry = 0;
}

void MyWifi::setup()
{
  WiFi.mode(WIFI_STA);
}

void MyWifi::handleStartup()
{
  wifi_connect_to(ssid1, password1);
  status = WifiStatus::connecting;
  previousMillis = millis();
}

void MyWifi::handleConnecting()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 500) // every 0.5s
  {
    previousMillis = currentMillis;
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("\nConnected !");
      WiFi.setAutoReconnect(true);
      timeClient.begin();
      delay(30);
      timeClient.update();
      status = WifiStatus::connected;
      previousMillis = millis();
    }
    else
    {
      // TODO check (sta_retry < sta_max_retries)
      Serial.print(".");
      sta_retry++;
    }
  }
}

void MyWifi::handleConnected()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 60000) // every 60s
  {
    previousMillis = currentMillis;
    timeClient.update();
  }
}

bool MyWifi::isConnected() const
{
	return ((WiFi.status() == WL_CONNECTED) and (status == WifiStatus::connected));
}

void MyWifi::getTime(uint8_t& hours, uint8_t& minutes)
{
   hours = timeClient.getHours();
   minutes = timeClient.getMinutes();
}

void MyWifi::loop()
{
  switch(status)
  {
    case WifiStatus::startup : handleStartup(); break;
    case WifiStatus::connecting : handleConnecting(); break;
    case WifiStatus::connected : handleConnected(); break;
  }	
}
