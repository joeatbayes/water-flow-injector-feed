#water flow activated injector feed

Activate hydrogen peroxide injector feed pump when water is flowing through Hall effect water flow sensor YF-B10.
Senses water flow movement through YF-B10 or Gredia G1 water flow sensor.   Drives a low side switch which 
activates a SSA-40 DA solid state relay to switch hot line to injector pump.     

This injector pump is not variable speed so we simply detect pulses from either sensor and if we are seeing
more than 1 pulse every 10 seconds then we activate the injector pump.    We use two sensors in parralell 
to minimize flow reduction across the flow sensors.

Uses ESP32-s3 based RainAmp controller board but should work with any generic ESP32 module with minor pin changes
Uses SS1306 olded display over I2C for user interface.  Uses capacitive sensors for Up, Down, Sel, Exit.  This board
supports RS485 on Uart-1 but it is not needed for this purpose 

* Pin LED - 11
* Pin Motor Enale - 16
* Pin SDA -
* Pin SCL -
* pin button up -
* pin button down -
* pin button select -
* pin button exit  -

