Example code for Wi-Fi module for BigClown: Flood Detector</br>
Flood detector indicates water on your floor about washing machine, dishwasher or somewhere else.
The detector LD-81 is directly connected to P7 GPIO.
  
CONNECTION: LD-81 detector Black wire - GND, Red wire to P7, Resistor 4k7 from VCC to P7, cut other wires.

If Flood detector detects water, the warning value (it means number 1) is sent to TMEP.cz/TMEP.eu. Otherwise
Wi-Fi module sends number 0 every hour - it means, no water, still alive. 

NOTE: In this example, you don't need to buy Sensor module by BigClown and Core module with Radio (you have Wi-Fi module).

What you need: 
Core module without Radio https://shop.bigclown.com/core-module-nr/ </br>
Flood detector: https://shop.bigclown.com/3d-printed-enclosure-501/ </br>
Mini baterry module: https://shop.bigclown.com/mini-battery-module/ </br>
3D printed enclosure: https://shop.bigclown.com/3d-printed-enclosure-501/</br> 
and Wi-Fi module v1.1: https://www.tindie.com/products/chiptron/wi-fi-module-with-esp8266-for-bigclown-bare-pcb/  </br>

How is it working</br> 
https://www.youtube.com/watch?v=7Jf7yYidH3M

<img align="left" width="60%" src="https://github.com/petus/BigClown-Wi-Fi-module-v1.1/blob/master/FW%20examples/Flood%20Detector/BC_WiFi_FloodDetector_1.jpg">

<img align="left" width="60%" src="https://github.com/petus/BigClown-Wi-Fi-module-v1.1/blob/master/FW%20examples/Flood%20Detector/BC_WiFi_FloodDetector_2.jpg">

<img align="left" width="60%" src="https://github.com/petus/BigClown-Wi-Fi-module-v1.1/blob/master/FW%20examples/Flood%20Detector/BC_WiFi_FloodDetector_3.jpg">
