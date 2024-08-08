# water flow activated injector feed

Activate hydrogen peroxide injector feed pump when water is flowing through Hall effect water flow sensor YF-B10.  Senses water flow movement through YF-B10 or Gredia G1 water flow sensor.  
### TODO: Add Picture here

The CPU drives a low side switch which activates a SSA-40 DA solid state relay to switch AC hot line to injector pump whenever we have water flowing through 
sensors. 

We use 2 Gredia G1 sensors to minimize water flow 
resistance through the sensors. That means we must compute flow through 
both sensors and add together to get total flow.   

Our hydrogen peroxide injector pump is not variable speed so we simply detect any flow greater than the minimum offset from the sensors and activate the pump.  To minimize pump wear we ensure the pump stays on for 30 seconds after water flow stops and stays off for at least 10 seconds.  
    * For the G1 the minimum detectable flow is 0.54 LPM while minimum 
      flow is 1.35LPM for the YB-B10. Both devices rate their flow detection
      G1 is rated for 1..60LPM   The YB-B10 is rated for 2..60LPM

Total Water and current gallons per minute are displayed on OLED display.  It permenantly saves this once and hour so total is not lost after reboot.    It also computes GPM for each sennsor and displays on OLED


Uses ESP32-s3 based RainAmp controller board but should work with any generic ESP32 module with minor pin changes Uses SH1106 1.3 inch OLED display over I2C for user interface.  Uses push buttons for Up, Down, Sel, Exit.  This board
supports RS485 on Uart-1 but it is not needed for this purpose 

# CPU Pins
* Pin LED - 11
* Pin Motor Enable - 16
* Pin SDA - 17
* Pin SCL - 18
* Pin meter water flow pulse sensor 1 - 7
* Pin meter water flow pulse sensor 2 - 8 
* VCC 3.3V to Sensor 1, sensor 2 and OLED.
* GND to sensor 1, sensor 2 and OLED
* Buton support
    Buttons not used in Version 1 but were added to 
    face place and wired into CPU for when I find a
    need. 
    * pin button up - 1  - (reserved) 
    * pin button down - 2 - (reserved) 
    * pin button select -4  - (reserved) 
    * pin button exit  - 5 - (reserved) 
    * VCC through 47K resistor to each  buttons
    * 1M bleed resistor for each button to ground 


# Main Unit Wiring
* Plug to Box standard 3 prong plug
* Black from wall to 10 Amp Fuse holder to Both USB 5 volt supply and one pole of relay.
  * Black from Switched side Relay to Black Plug Lug
* White from Wall to both USB 5 volt suplly and Neutral Plug Lug
* Green from wall to Ground Plug Lug

# 3D printed parts
* Faceplate for 3 Gang box - Special focus here was reserving room for 
  oled supply,  outlet plug and Digital Relay.  I wanted the activation 
  LED for the relay to show through the face plate.  

* CPU holder mounted below relay


## parts I used
* [Gredia G1 Hall effect wwater flow sensor](https://www.amazon.com/GREDIA-Sensor-Food-Grade-Flowmeter-Counter/dp/B07RF5D156/)  I used 2 sensors
* [3 gang box for assembly of entire unit](https://www.amazon.com/Madison-Electric-Products-MSB3G-Adjustable/dp/B00H8NUVQA)
* [Silicone ribbon cable to connect sensors OLED](https://www.amazon.com/MECCANIXITY-Ribbon-Silicone-Stranded-Tinned/dp/B0CBB3C91V)

* Face Plate for 3 Gang box -  3D printed - TODO: ADD Picture and 
  CAD drawing here.
    * QTY 2  6/32 by 1.5" machine screws - hold relay and cpu support to faceplate
    * Qty 6  #4 X 3/4" philips screw - connect faceplate to box
    * Qty 6   #4 X 1/2" philips screw - connect oled to faceplate

* CPU board holder to mount CPU board below digital relay - TODO: Add picture 
  and CAD drawing here.

* [5v usb power supply 5V](https://www.amazon.com/Adapter-UorMe-Charger-Charging-Compatible/dp/B08LGRN2NR)  My board 
  accepts 5V to 40V in.  Other boards may need 3V power supply. This one was 
  small enough to keep inside the 3 gang unit.
* [OLED display](https://www.aliexpress.us/item/2251832498844654.html)
* [40 amp Digital Relay for AC](https://www.aliexpress.us/item/3256804475347699)
* [Recomended CPU](https://www.aliexpress.us/item/3256805991471052.html) I used a propriatary board I made for another purpose but this CPU would have done just as well.
* [Fuse holder for 10 amp fuse](https://www.amazon.com/KOLACEN-Automotive-Inline-5x20mm-Holder/dp/B071G1L98V) Installed on Live wire 
* Wall Plug Genric 3 prong 120V outlet
* 3 prong male plug to supply power
* 7 foot 3 conductor flexible wire for power supply cord


## Recomended Changes 
* Use a 3.3V gate Triac such as [BTB06-600B](https://www.aliexpress.us/item/3256806576807703.html) in liue of solid state relay.  The Triac is smaller and capable of carrying the current needed for this applicaiton.
* Make a new PCB with exact match for this use.
* Use Circuit breaker with external reset button in liue of inline fuse.