# Dancing_lights
Dancing lights is an interactive sensitive light installation where 300 programmable LEDs in a tube filled with crushed glass responds to rythmic movement.

![horiz_light_jakob_bitraf](img/horiz_light_jakob_bitraf.jpg)

## Status and todos
*Under development*
* Move power connector to start of strip side so the microcontroller can go in the base, and attach to the antenna
* Sensor needs more testing (select / build mega resistor?) or alternative developed. 
* 3D print the parts
* Assembly and testing
* Power brick mount
* PCB mount
* Do I make a new PCB? Have headers? 


## Principles and inspiration
* The glass shard filled LED diffusor tube is inspired by [Invento3Ds Instructable: Glass Stone LED Tube](https://www.instructables.com/Glass-Stone-LED-Tube-WiFi-Controlled-Through-Smart/)
* The motion sensor is based on Capacitive touch [Arduino playground: Capacitive Sensing Library
 by Paul Badger](https://playground.arduino.cc/Main/CapacitiveSensor/) and [My own lesson material on pulldown and EMC noise](https://github.com/KubenKoder/Arduino/tree/master/Egna%20exempel/pulldown)
* It uses the Arduino [FastLED library](https://fastled.io/) to make the pretty light patterns

## Bill of Materials
Purchased in or imported to Norway. NOK = Norwegian kroner.

* 300 WS2812B GRB LEDs on a 5 m tape strip IP30 5V (60/m). WS2812B GRB ~$10 from [Aliexpress](https://www.aliexpress.com/item/32682015405.html) 
* 1m Ø50 mm Acrylic tube 383 NOK from [Sløjd-Detaljer](https://www.sloyd-detaljer.no/produkter/tre-metallsloyd/plast-gummi/ror-stenger/akrylror-1757)
* Used 2 kg 4-10 mm size crushed glass, 175 NOK for 3 Kg from [My stone](https://mystonebrukskunst.no/dekorasjonsglass)
* 3D-printed endcaps for the tube, modeled in Fusion360 [STL](models/50mm_plug.stl) Printed for free on a Pruse at [Bitraf makerspace](https://bitraf.no/)
* Copper tube, Ø15mm wall thickness 1.5mm, Recyled scrap. 
* 2 5V 8A Power bricks, ~10$ each from [Aliexpress](https://www.aliexpress.com/item/32986101102.html)
* 3 pin connector cheap from [Aliexpress](https://www.aliexpress.com/item/32920894203.html)
* 2 pin barrel jack connector cheap from [Aliexpress](https://www.aliexpress.com/item/32966940042.html)
* Base material TBD
* Vero-board
* Capacitors
* Antenna (FIA 137 47-68MHz, 87,5-104MHz or 174-230MHz depending on expended length) from flea market

## Components
### 5x1m LED strips mounted on Ø15mm copper tube
![Led strip specifications](img/led_strip_specs.jpg)

![5_1m_strips_on_15mm_dia_tube](img/5_1m_strips_on_15mm_dia_tube.jpg)

Diameter 15mm => cicumference 47mm, 5 strips that are 10mm wide should not work in theory but works in practice since the edges don't follow the curve of the tube perfectly.
The tape attatches well to the tube. Didn't feel there was need to secure it further.

![connected_leds_and_arduino](img/connected_leds_and_arduino.jpg)

Note that I staggered the ends of the strips. They are soldered together like as if they still were one long strip.

![leds_on_copper_tube_alternates](img/leds_on_copper_tube_alternates.jpg)

Default configuration for the LED coordinates.

![leds_on_copper_tube_wrapped](img/leds_on_copper_tube_wrapped.jpg)

Alternative LED coordinates increases the axial resolution from 60 leds / m to 300 leds / m. 

### 3D models

![fusion model](img/fusion_model.jpg)

[Fusion model (online view, can be downloaded)](https://a360.co/3SHoL3g) 

[STEP file (right click and "save link as" or it will open as text](models/LED-tube_v21.step)

![base freecad](img/base_freecad.jpg)

[Freecad file](models/main_shape.FCStd)

![Tube endcaps, 3D-printed](img/endcaps.jpg)

[STL file](models/50mm_plug.stl)

The idea is to clamp the copper tube tight so that any load on the acrylic tube is transfered to the copper via the endcaps and not via the LEDs. I also want it to cover the ends of the led strips.

![clamp_leds_and_copper_tube](img/clamp_leds_and_copper_tube.jpg)

Didn't fit very well. Had to file off some plastic to get it over the edges of the LED_strip tape and since I did it didn't clamp as well. Compensated with white electricans tape. I consider adding metal hose clamps.

![top_cap.jpg](img/top_cap.jpg)

Concept of a top cap to hide the end and allow airflow through the pipe. Allows space for a large capacitor inside the cap, for the end of the strip. 

[STL file](models/top_cap.stl)

![top_cap.jpg](img/top_cap_slim_mounted.jpg)

Slim version of top cap to hide the end and allow airflow through the pipe. Requires trimming the copper pipe tight to the plastic clamp. No space for capacitor here, needs to be attached to the other ends of the strips.

[STL file](models/top_cap_slim.stl)

![fan_mount_freecad](img/fan_mount_freecad.jpg)

Fan mount for bottom 

[STL file](models/fan_holder_bottom.stl)

![brick holder](img/power_brick_holder.jpg)

For holding the power bricks in place.

[STL file](models/brick_holder.stl)

