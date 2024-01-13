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

#include "WebServer.h"
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include "Configuration.h"

ESP8266WebServer server(80);

const char htmlPage[]PROGMEM=R"=====(
<!DOCTYPE html>
<html>
<head><title>7 Segment LED clock</title></head>
<body>
<h3>7 Segment LED clock</h3>
<p>Config</p>
<form action="/config">
  <label for="ledp">Led pattern:</label>
  <input type="number" id="ledp" name="pattern">
  <label for="p1">Color:</label>
  <input type="color" id="p1" name="param1" value="#ff0000">
  <input type="submit" value="Submit">
</form>
<p>Firmware</p>
<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>

</body>
</html>
)=====";

void handleRoot()
{
  //server.send(200, "text/plain", "hello from esp8266!");
  // TODO 
  // Current time = ..:..
  // LDR sensor value: 120  
  server.send(200,"text/html",htmlPage);
}

void handleNotFound()
{
  String message = "URL Not Found: ";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

WebServer::WebServer(Configuration& config)
    : config(config),
      is_running(false)
{
}

void WebServer::handleConfig()
{
  const String& new_pattern = server.arg("pattern");
  String new_color = server.arg("param1");
  Serial.print("Led pattern: ");
  Serial.println(new_pattern);
  Serial.printf("Led pattern in number: %ld\n", new_pattern.toInt());
  if ((new_pattern.toInt() >= 0) and (new_pattern.toInt() < int(ColorPattern::max)))
    config.setColorPattern(ColorPattern(new_pattern.toInt()));
  Serial.print("Led color: ");
  Serial.println(new_color);
  new_color.remove(0, 1);// remove first char
  Serial.print("Led color (ed): ");
  Serial.println(new_color);
 
  uint32_t col = strtol(new_color.c_str(), NULL, 16);
  Serial.printf("Color in (hex)number: 0x%x\n", col);
  config.setColor(col);
  server.sendHeader("Connection", "close");
  server.send(200, "text/plain", "Lets configure something");
}

void WebServer::handleUpdate() /* Firmware update */
{
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
}

void WebServer::fileUploadHandler()
{
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
      Serial.setDebugOutput(true);
      WiFiUDP::stopAll();
      Serial.printf("Update: %s\n", upload.filename.c_str());
      uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
      if (!Update.begin(maxSketchSpace))  // start with max available size
      {
        Update.printError(Serial);
      }
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
      {
        Update.printError(Serial);
      }
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
      if (Update.end(true))  // true to set the size to the current progress
      {
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      }
      else
      {
        Update.printError(Serial);
      }
      Serial.setDebugOutput(false);
    }
    yield();
}

void WebServer::setup()
{
    server.on("/", handleRoot);
    server.on("/config", HTTP_GET, std::bind(&WebServer::handleConfig, this));
    server.on("/update", HTTP_POST, std::bind(&WebServer::handleUpdate, this), std::bind(&WebServer::fileUploadHandler, this));

    server.onNotFound(handleNotFound);
    server.begin();
    is_running = true;
}

void WebServer::loop()
{
    if (is_running)
        server.handleClient();
}

