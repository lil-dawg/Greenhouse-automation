# Greenhouse Automation
The goal of this project is to automate my moms greenhouses sliding door to control the temperature inside during summer to prevent the plants from overheating. The device should operate automatically but also have an electrical manual override and a mechanical failsafe mechanism, both on the in- and outside. The control box should have a menu on an lcd-display controlled by a rotary encoder.

## Material
### Arduino uno 
### DPDT relay (Double Pole Double Throw)
”Relay 5V 2 Channel” from CASE
### Linear actuator
Something like [this](https://amzn.eu/d/8Mn2aXY)
### Rotary encoder
* [Guide](https://www.youtube.com/watch?v=HJ61Q1K5_Pc)
* Good to know: Has to use debounce and should use interrupt
### hd44780 lcd 
display with i<sup>2</sup>c shield
### Limit switch from CASE
### DS18B20 1-wire termometer
-55&deg;C to +125&deg;C, ”Temperature sensor waterproof” from CASE
* Good to know: The dallasTemperature library is super slow and has to use non-blocking methods, will block the code otherwise

## Sources
[Guide for menu](https://www.youtube.com/watch?v=1B8TZdXDVYc)  
