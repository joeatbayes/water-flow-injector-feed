#water flow activated injector feed

Activate hydrogen peroxide injector feed pump when water is flowing through Hall effect water flow sensor YF-B10.  Senses water flow movement through YF-B10 or Gredia G1 water flow sensor.  

The sysem drives a low side switch which activates a SSA-40 DA solid state relay to switch hot line to injector pump on whenever we have water flowing through 
sensors. 

We actually use 2 sensors 1 YB-B10 and one Gredia G1 to minimize water flow 
resistance through the sensors. That means we must compute flow through 
both sensors and add together to get total flow.   The G1 seems much more sensitive for to flow. 

This injector pump is not variable speed so we simply detect any flow greater than the minimum offse and activate the pump.  We ensure the pump stays on for 30 seconds after water flow stops and stays off for at least 30 seconds.  
    For the G1 the minimum detectable flow is 0.54 LPM while minimum 
    flow is 1.35LPM for the YB-B10. Both devices rate their flow detection
    G1 is rated for 1..60LPM   The YB-B10 is rated for 2..60LPM

It computes total water flow and displays on OLED display.  It permenantly saves this once every 10 minutes so total is not lost after reboot. 


Uses ESP32-s3 based RainAmp controller board but should work with any generic ESP32 module with minor pin changes Uses SS1306 olded display over I2C for user interface.  Uses capacitive sensors for Up, Down, Sel, Exit.  This board
supports RS485 on Uart-1 but it is not needed for this purpose 

* Pin LED - 11
* Pin Motor Enable - 16
* Pin SDA - 17
* Pin SCL - 18
* pin button up - 1
* pin button down - 2
* pin button select -4 
* pin button exit  - 5
* Pin meter pulse sensor 1 - 7
* Pin meter pulse sensor 2 - 8 

