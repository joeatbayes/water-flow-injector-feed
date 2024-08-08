#water flow activated injector feed

Activate hydrogen peroxide injector feed pump when water is flowing through Hall effect water flow sensor YF-B10.  Senses water flow movement through YF-B10 or Gredia G1 water flow sensor.  

The sysem drives a low side switch which activates a SSA-40 DA solid state relay to switch hot line to injector pump on whenever we have water flowing through 
sensors. 

We actually use 2 Gredia G1 sensor to minimize water flow 
resistance through the sensors. That means we must compute flow through 
both sensors and add together to get total flow.   The G1 seems much more sensitive for to flow. 

This injector pump is not variable speed so we simply detect any flow greater than the minimum offse and activate the pump.  We ensure the pump stays on for 30 seconds after water flow stops and stays off for at least 30 seconds.  
    For the G1 the minimum detectable flow is 0.54 LPM while minimum 
    flow is 1.35LPM for the YB-B10. Both devices rate their flow detection
    G1 is rated for 1..60LPM   The YB-B10 is rated for 2..60LPM

Software total water flow and displays on OLED display.  It permenantly saves this once and hour so total is not lost after reboot.    It also computes GPM for each sennsor and displays on OLED


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


## parts I used
* [3 gang box for assembly of entire unit](https://www.amazon.com/Madison-Electric-Products-MSB3G-Adjustable/dp/B00H8NUVQA)

* Face Plate for 3 Gang box -  3D printed - TODO: ADD Picture and 
  CAD drawing here.

* CPU board holder to mount CPU board below digital relay - TODO: Add picture 
  and CAD drawing here.

* [5v usb power supply 5V](https://www.amazon.com/Adapter-UorMe-Charger-Charging-Compatible/dp/B08LGRN2NR)  My board 
  accepts 5V to 40V in.  Other boards may need 3V power supply. This one was 
  small enough to keep inside the 3 gang unit.
* [OLED display](https://www.aliexpress.us/item/2251832498844654.html)
* [40 amp Digital Relay for AC](https://www.aliexpress.us/item/3256804475347699)
* [Recomended CPU](https://www.aliexpress.us/item/3256805991471052.html) I used a propriatary board I made for another purpose but this CPU would have done just as well.
* [Fuse holder for 10 amp fuse](https://www.amazon.com/KOLACEN-Automotive-Inline-5x20mm-Holder/dp/B071G1L98V) Installed on Live wire 


## Recomended Changes 
* Use a 3.3V gate Triac such as [BTB06-600B](https://www.aliexpress.us/item/3256806576807703.html) in liue of solid state relay.  The Triac is smaller and capable of carrying the current needed for this applicaiton.
* Make a new PCB with exact match for this use.
* Use Circuit breaker with external reset button in liue of inline fuse.