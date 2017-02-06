# sun-data

Sun sensor for Pepa Ivanova
 
## Initial Implementation

Consists of nodemcu + microSD shield + OLED shield
 
Pin | Function | ESP8266 Pin | MicroSD Shield | OLED Shield* | TSL2591**
---| --- | --- |---|---|---
TX | TXD | TXD |
RX | RXD | RXD |
A0 | Analog input, max 3.3V input | A0
D0 | IO | GPIO16
D1 | IO, SCL | GPIO5 |   | SCL | SCL
D2 | IO, SDA | GPIO4 |   | SDA | SDA
D3 | IO, 10k Pull-up | GPIO0
D4 | IO, 10k Pull-up, BUILTIN_LED |GPIO2
D5 | IO, SCK | GPIO14 | CLK
D6 | IO, MISO | GPIO12 | MISO
D7 | IO, MOSI | GPIO13 | MOSI
D8 | IO, 10k Pull-down, SS | GPIO15 | CS
G  | Ground | GND | GND | GND | GND
5V | 5V | -
3V3 | 3.3V | 3.3V | 3.3V | 3.3V | 3.3V
RST | Reset | RST

\* OLED Shield I2C Address - 0x3C or 0x3D

\** Sun sensor TSL2591 I2C Address - 0x29


## TODO List

 - [ ] Create test cases

 - [ ] Compile each needed library individually

 - [ ] Start the project
 
### Links \& References

[NodeMCU WebServer with SD Card Support](https://www.hackster.io/draw2dtouch/nodemcu-webserver-with-sd-card-support-169adc) 

[Tech Note 008 NTP controlled OLED CLOCK and demos the WIFI Manager](https://www.youtube.com/watch?v=RTKQMuWPL5A#t=416.58195)

