// **** Description:                                                  
// ****  This shetche collects light data

// ****  Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
// ****  Light data functions using a TSL2591 connected via I2C and Adafruit_TSL2591 lib.
// ****  SD card functions using SPI bus via SPI and SD lib (CS pin = 10).
 
// ****  All data are stored on a SD card file day by day.
// ****  File structure: <name> (./DATA/yyyymmdd.TXT)
// ****                    timestamp (sec elapsed from midnight
// ****                    Infra-Red value (gain & integration time dependant)
// ****                    Full spectrum value (gain & integration time dependant)
// ****                    Luminosity (lux) MSB
// ****                    Luminosity (lux) LSB
// ****
// ****  Gain, time integration, time lap and lower threshold can be adjusted
// ****  via the software. Those settings are automatically stored on the SD card.
// ****  Settings are recalled from the SD card on startup.

// ****  The ONLINE tag allow to monitor the board's info/data in the software.

// ****  The debugging led blinks on each time lap capture.
// ****  When a problem has occured (no sensor or no SD card) the debugging led remains ON.
// ****  The board needs to be resetted when a problem occured.



// Fabrice Moinet @2016 Pepa Ivanova- Sun data collecting


#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"



RTC_PCF8523 rtc;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)

#define ID 1 // declare ID board

File path;
File dataFile;

const int chipSelect = 10; // CS for SD card reader
const int ledPin = 13;

#define MAXSIZE 20
byte inByte;
byte rxOffset;
char rxData[MAXSIZE];
boolean DATA_AVAILABLE;
char outParse[MAXSIZE];

uint32_t lux,timestamp;
uint16_t ir, full;

boolean ONLINE = false;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char fileName[20];


// Interrupt thresholds and persistance
#define TLS2591_INT_PERSIST        (TSL2591_PERSIST_60) // Fire on any valid change
uint16_t TLS2591_INT_THRESHOLD_LOWER;
uint16_t TLS2591_INT_THRESHOLD_UPPER = 65535;

uint16_t gain,timing,lap;
uint16_t timeLap, timeLap_;
uint16_t YEAR,MONTH,DAY,DAYOFTHEWEEK,HOUR,MINUTE,SECOND;

boolean LOWLIGHT; // Low condition flag

unsigned int timer, timer_;

void setup () {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,HIGH);    // led ON while board is not ready!

  
  Serial.begin(9600);

  //**********************************************************
  //                    RTC  initialization
  //**********************************************************
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  //**********************************************************
  //                    SD card initialization
  //**********************************************************
   Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  

  //**********************************************************
  //                    Sensor initialization
  //**********************************************************

  Serial.println("Starting Adafruit TSL2591 Test!");
   
  if (tsl.begin()) 
  {
    Serial.println("Found a TSL2591 sensor");
  } 
  else 
  {
    Serial.println("No sensor found ... check your wiring?");
    while (1);
  }
  
  /* Configure the board */
  loadSettings();
  
  /* Display information on this sensor */
  displaySensorDetails();
  

  if(!SD.exists("DATA/")) SD.mkdir("DATA/");

  delay(500);

  // Now we're ready to get readings ... move on to loop()!
  digitalWrite(ledPin,LOW);
  
}

void loop () {
  
  while (Serial.available()> 0){
     byte inByte = Serial.read();
     if (inByte == 13) DATA_AVAILABLE = 1;
     else {
       rxData[rxOffset] = inByte;
       rxOffset++;
     }
   }

  if(DATA_AVAILABLE) cmdReader();
  
  if((timer = millis() / 1000) != timer_){    // routine every 1000ms
    timer_ = timer;
    checkTime();
  
    if(ONLINE){
     char timeNow[50];
     sprintf(timeNow,"date %04d/%02d/%02d %s %02d:%02d:%02d",
            YEAR,MONTH,DAY,
            daysOfTheWeek[DAYOFTHEWEEK],
            HOUR,MINUTE,SECOND);     
     Serial.println(timeNow);
    }
  
    if (((timeLap = (MINUTE * 60) + SECOND) % lap ) == 0){
        
      readSensorData();
      getStatus();
      if(ONLINE){
        Serial.print("status ");
        Serial.print(!LOWLIGHT);
        Serial.print(" ");
        Serial.print(ir);
        Serial.print(" ");
        Serial.print(full);
        Serial.print(" ");
        Serial.print(lux >> 16);
        Serial.print(" ");
        Serial.println(lux & 0xFFFF);
      }
      
      if (!LOWLIGHT){
        
        sprintf(fileName,"DATA/%04d%02d%02d.TXT",YEAR,MONTH,DAY);

        timestamp = (HOUR * 3600) + (MINUTE * 60) + SECOND;

        /*
        if(!SD.exists(fileName)){
          Serial.println("dont");
          if(dataFile = SD.open(fileName, FILE_WRITE)){
            dataFile.print("ID ");
            dataFile.println(ID);
            dataFile.close();
          }
        }
        */

        if(dataFile = SD.open(fileName, FILE_WRITE)){
           
          if(ONLINE){
            Serial.print("write ");
            Serial.println(fileName);
          }
          
          dataFile.print(timestamp);
          dataFile.print(" ");
          dataFile.print(ir);
          dataFile.print(" ");
          dataFile.print(full);
          dataFile.print(" ");
          dataFile.print(lux >> 16);
          dataFile.print(" ");
          dataFile.println(lux & 0xFFFF);
          
          dataFile.close();
          
          blinkLed();
        } else digitalWrite(ledPin,HIGH); // swith ON led ... something is wrong!
      }
    }
  }
}


void checkTime(){
  DateTime now = rtc.now();
  YEAR = now.year(); 
  MONTH = now.month(); 
  DAY = now.day();
  DAYOFTHEWEEK = now.dayOfTheWeek();
  HOUR = now.hour();
  MINUTE = now.minute();
  SECOND = now.second();
}

void blinkLed(){
  digitalWrite(ledPin,HIGH);
  delay(50);
  digitalWrite(ledPin,LOW);
}
