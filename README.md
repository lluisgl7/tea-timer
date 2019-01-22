# Automatic Tea Timer
This is a simple gadget that will help you prepare your teas and infusions. Just put the tea bag (or infuser) and the cup with hot water in place and select the desired steeping time. The Tea Timer will automatically infuse the tea during the selected time and will notify you with a beep when your drink is ready.

See it in action: https://youtu.be/dda5ccRVNXM  <br>
Thingiverse link: http://www.thingiverse.com/thing:1049056 <br>
Instructables link: http://www.instructables.com/id/Automatic-Tea-Timer

3ders.org article link: http://www.3ders.org/articles/20151012-make-perfect-tea-every-time-with-this-3d-printed-automatic-tea-timer.html

![](https://github.com/lluisgl7/tea-timer/blob/master/img/IMG_1.JPG)

## Printed parts

  The printed parts have been designed with FreeCAD. The original parametric files are supplied along with the generated STL files.
  For the main part of the Tea Timer, in addition to the unsupported version, I created a version with the minimal supports needed (although it will depend on the printer).

## Required hardware

- Arduino Pro Mini or another small and compatible Arduino board. 
- LCD Display compatible with the Hitachi HD44780 driver (typical 2x16 Arduino LCD)
- Micro Servo 
- 2x Rotary Potentiometers: http://www.banggood.com/1-2-5-10-20-50-100-250-500-1000K-Ohm-Potentiometers-Single-Linear-p-919185.html 
- Push Button: http://www.banggood.com/BOUTTON-Switch-Commutateur-DC-50V-Noir-Rouge-p-87567.html
- Slide Switch: http://www.banggood.com/5pcs-6-Pins-Slide-Switch-OnOn-Vertical-Mini-Miniature-Terminals-p-993806.html
- 11.8 mm Buzzer: http://www.banggood.com/5V-Electromagnetic-Active-Buzzer-Continuous-Beep-Continuously-p-928005.html
- 5V Power Supply (USB supply, phone charger…)
- Power Jack Plug: http://www.banggood.com/Wholesale-2_1-x-5_5mm-DC-Power-Male-Plug-Jack-Adapter-Connector-For-CCTV-Camera-p-39991.html
- Power Jack Socket: http://www.banggood.com/5_5mm-X-2_1mm-DC-Power-Supply-Metal-Jack-Socket-With-Nut-And-Washer-p-934446.html
- 7x M3 bolts and nuts (LCD display and lid)
- 4x M2 bolts and nuts (servo and power switch)
	
You may also need some type of adhesive (I used double sided foam to fasten the arduino board and the contrast potentiometer on the inside), an USB-to-TTL serial converter board to upload the sketch and wiring material (wires, solder, heatshrink tubing…).

![](https://github.com/lluisgl7/tea-timer/blob/master/img/IMG_2.JPG)
![](https://github.com/lluisgl7/tea-timer/blob/master/img/IMG_3.JPG)

## Ideas for possible improvements

- Micro USB connector for power
- Battery powering option
- Hardware debouncer for the button (instead of software debouncer)
- Tea bag shaking option
- LCD progress bar
- Sleep mode
