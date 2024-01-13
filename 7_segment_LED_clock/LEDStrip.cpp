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

#include "LEDStrip.h"
#include "config.h"
#include "LEDPattern.h"


#define NUM_LEDS          86
#define BRIGHTNESS        150
#define FRAMES_PER_SECOND 20

// Define the array of leds
CRGB leds[NUM_LEDS] = {CRGB::Black};

typedef int Digit[21];

// Physical LED nbrs  in order abcdefg from left to right and from top to bottom
// So first number in the array is left most LED nb of segment a, last led is the right Led of segment g
Digit digit1 = {28, 29, 30, 31, 32, 33, 13, 14, 15, 18, 17, 16, 21, 20, 19, 27, 26, 25, 22, 23, 24};
int digit2[21] = {37, 38, 39, 40, 41, 42,  1,  2,  3,  6,  5,  4,  9,  8,  7, 36, 35, 34, 10, 11, 12};
int digit3[21] = {47, 48, 49, 50, 51, 52, 64, 63, 62, 59, 60, 61, 56, 57, 58, 46, 45, 44, 55, 54, 53};
int digit4[21] = {80, 81, 82, 83, 84, 85, 73, 72, 71, 68, 69, 70, 65, 66, 67, 79, 78, 77, 76, 75, 74};
int dot1 = 43;
int dot2 = 0;

String segments0 = "abcdef";
String segments1 = "bc";
String segments2 = "abged";
String segments3 = "abcdg";
String segments4 = "fgbc";
String segments5 = "afgcd";
String segments6 = "afgedc";
String segments7 = "abc";
String segments8 = "abcdefg";
String segments9 = "abcdfg";
String NO_segments = "";

uint32_t current_color = 0xff0000; // Red
uint8_t initialhue = 100;

Digit& get_digit(int digit_id)
{
  switch(digit_id)
  {
    case 1 : return digit1; break;
    case 2 : return digit2; break;
    case 3 : return digit3; break;
    case 4 : return digit4; break;
  }
  // Wrong number ?
  return digit1;
}

// digit_id : 1-4, segment: a-g, lednb: 1-3
int get_physical_LED_id(int digit_id, char segment, int lednb)
{
  Digit& digit = get_digit(digit_id);
  int index = 0;
  switch(segment)
  {
    case 'a' : index = 0; break;
    case 'b' : index = 3; break;
    case 'c' : index = 6; break;
    case 'd' : index = 9; break;
    case 'e' : index = 12; break;
    case 'f' : index = 15; break;
    case 'g' : index = 18; break;
  }
  if ((lednb >= 1) and (lednb <= 3 ))
  {
    index += (lednb -1);
  }

  return digit[index];
}

const String& getNumberSegments(int num)
{
  switch(num)
  {
    case 0 : return segments0;
    case 1 : return segments1;
    case 2 : return segments2;
    case 3 : return segments3;
    case 4 : return segments4;
    case 5 : return segments5;
    case 6 : return segments6;
    case 7 : return segments7;
    case 8 : return segments8;
    case 9 : return segments9;
  }
  return NO_segments;
}

CRGB LEDStrip::get_led_color(int digit_id, char segment, int lednb)
{
  if (pattern == ColorPattern::solid)
    return current_color;
  else if (pattern == ColorPattern::rainbow)
  {
    CHSV hsv;
    hsv.hue = initialhue + (digit_id-1) * 50;
    hsv.val = 255;
    hsv.sat = 240;
    return hsv;
  }
  else
    return get_matrix_color(digit_id, segment, lednb);
}

// dot_id : 1-2
CRGB LEDStrip::get_dots_color(int dot_id)
{
  if (modus == ClockModus::wifiConnect)
    return CRGB::Blue;
  else if (pattern == ColorPattern::solid)
    return current_color;
  else if (pattern == ColorPattern::rainbow)
  {
    CHSV hsv;
    hsv.hue = initialhue + 75;
    hsv.val = 255;
    hsv.sat = 240;
    return hsv;
  }
  else
    return get_matrix_dots_color(dot_id);
}

void clearAllLEDs()
{
  // TODO fill_solid(leds, NUM_LEDS, CRGB::Black);
  // TODO use FastLED.clear() cmd
  for (int i=0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
}

void LEDStrip::showDots(bool dotHigh, bool dotLow)
{
	leds[dot1] = dotHigh ? get_dots_color(1) : CRGB::Black;
	leds[dot2] = dotLow ? get_dots_color(2) : CRGB::Black;
}

void LEDStrip::showNumber(int digitId, uint8_t num)
{
  const String& segments = getNumberSegments(num);
  int len = segments.length();
  for (int i= 0; i<len; i++)
  {
    for (int lednb=1; lednb<=3; lednb++)
    {
      int physled = get_physical_LED_id(digitId, segments[i], lednb);
      if (physled < NUM_LEDS)
        leds[physled] = get_led_color(digitId, segments[i], lednb);
    }
  }
}

void LEDStrip::initPatternColors()
{
  if (config.getColorPattern() != pattern)
  {
    pattern = config.getColorPattern();
    if (pattern != ColorPattern::solid)
    {
      initColorMatrix(pattern);
    }
  }
}

void LEDStrip::updatePatternColors()
{
  if (pattern == ColorPattern::solid)
    ; // Nothing todo
  else if (pattern == ColorPattern::rainbow)
    initialhue += 7;
  else
  {
    setNextColorMatrixIteration(pattern);
  }
}

void LEDStrip::showTime(uint8_t hours, uint8_t minutes)
{
  uint8_t hours_D1 = hours / 10;
  uint8_t hours_D2 = hours % 10;
  uint8_t minutes_D1 = minutes / 10;
  uint8_t minutes_D2 = minutes % 10;

  current_color = config.getColor();
  initPatternColors();
  clearAllLEDs();
  showDots(true, true);
  if (hours_D1 != 0)
    showNumber(1, hours_D1);
  showNumber(2, hours_D2);
  showNumber(3, minutes_D1);
  showNumber(4, minutes_D2);
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  updatePatternColors();
}

LEDStrip::LEDStrip(const Configuration& config)
  : config(config),
    modus(ClockModus::none),
    pattern(ColorPattern::solid),
    previousMillis(0),
    current_hours(12),
    current_minutes(0)
{}

void LEDStrip::setup()
{
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(BRIGHTNESS); // 0-255
  delay(100);
}

void LEDStrip::updateTime(uint8_t hours, uint8_t minutes)
{
  if ((current_hours != hours) or (current_minutes != minutes))
  {
    current_hours = hours;
    current_minutes = minutes;
    Serial.printf("Time update : %d:%d\n", hours, minutes);
    /*if (modus == ClockModus::showTime)
    {
      showTime(current_hours, current_minutes);
    }*/
  }
}

void LEDStrip::setModus(ClockModus newModus)
{
  switch(newModus)
  {
    case ClockModus::none : Serial.println("setModus none"); break;
    case ClockModus::wifiConnect : Serial.println("\nsetModus wifiConnect"); break;
    case ClockModus::selfTest1 : Serial.println("setModus selfTest1"); break;
    case ClockModus::showTime : Serial.println("setModus showTime"); showTime(current_hours, current_minutes); break;
  }
  modus = newModus;
}

void LEDStrip::handleModusWifiConnect()
{
  static bool blinking_dot = false;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 500) // 0.5s
  {
    previousMillis = currentMillis;
    blinking_dot = not blinking_dot;
    clearAllLEDs();
    showDots(false, blinking_dot);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
}

void LEDStrip::handleModusShowTime()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 200) // 0.2s
  {
    previousMillis = currentMillis;
    showTime(current_hours, current_minutes);
  }
}

void LEDStrip::loop()
{
  switch(modus)
  {
    case ClockModus::none : break;
    case ClockModus::wifiConnect : handleModusWifiConnect(); break;
    case ClockModus::selfTest1 : break;
    case ClockModus::showTime : handleModusShowTime(); break;
  }
}
