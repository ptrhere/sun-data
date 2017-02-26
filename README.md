# sun-data

Sun sensor for Pepa Ivanova
 
## Initial Implementation

Consists of nodemcu + microSD shield + (OLED shield not yet)
 
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

\** Sun sensor TSL2591 I2C Address - 0x29

## Used libraries (require installation in Arduino using Include Library / Manage Libraries ...)

 - Sparkfun TSL2561 library required (install using library manager) - 
[SparkFun TSL2561 library](https://github.com/sparkfun/SparkFun_TSL2561_Arduino_Library/blob/master/examples/SparkFunTSL2561Example/SparkFunTSL2561Example.ino)
 - SD by Arduino, SparkFun 1.1.1 - [SD](https://www.arduino.cc/en/Reference/SD)


## TODO List

 - [ ] Create test cases

 - [ ] Compile each needed library individually

 - [ ] Start the project
 

