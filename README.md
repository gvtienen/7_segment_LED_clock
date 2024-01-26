# 7_segment_LED_clock
Software for a Wemos D1 mini + WS2812B based Led clock.
Building information: https://www.printables.com/model/610020-big-wall-mounted-7-segment-led-clock

# Installation

## Arduino IDE
 * Open the 7_segment_LED_clock.ino file with the arduino IDE (only tried with v1.8.19)
 * Select the Board:  LOLIN(WEMOS) D1 R2 & mini
 * Install libraries: FastLED (version 3.6.0) and NTPClient
 * Compile and upload to the wemos

## PlatformIO
 * Open the projectfolder in PlatformIO
 * Click on Build (or Ctrl+Alt+B)
 * PlatformIO should automatically download libraries and compile the code
 * Click on Upload (or Ctrl+Alt+U)

 ## VSCode
 * Open the project folder in VSCode and let it install PlatformIO IDE
 * Click on Build
 * Click on Upload
 * After that, you can use the updateFirmware.sh (from Linux)

# Notes:
 * Do not connect the USB together with the power supply to the LED-clock
 * Do not keep the LED-clock running via the USB power, it will get too hot

# TODO later: 
 * Configure Wifi + ... from webpage (AP mode)
 * MQTT
 * use LDR value to set brightness
 * other LED patterns


