/**** logger: folder per day*******/

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)

File path;
File dataFile;


const int chipSelect = 10;
const int ledPin = 13;


RTC_PCF8523 rtc;

#define MAXSIZE 20
byte inByte;
byte rxOffset;
char rxData[MAXSIZE];
boolean DATA_AVAILABLE;
char outParse[MAXSIZE];

boolean CAPTURE = 1;
uint32_t lum,lux,timestamp;
uint16_t ir, full, lInt,hInt; // infrored, full, low interrupt, hight interrupt

boolean ONLINE = false;
boolean MONITOR = false;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char entry[12];
char fileName[20];
char dataString[50];

uint16_t gain,timing,lap;
uint16_t timeLap, timeLap_;
uint16_t YEAR,MONTH,DAY,DAYOFTHEWEEK,HOUR,MINUTE,SECOND;

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
    /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* Configure the board */
  delay(1000);
  loadSettings();
delay(1000);
  if(!SD.exists("DATA/")) SD.mkdir("DATA/");

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

  if (MONITOR) displayLiveData();
  
  if((timer = millis() / 1000) != timer_){    // routine every 1000ms
    timer_ = timer;
    checkTime();

    if (CAPTURE){
  
      if (((timeLap = (MINUTE * 60) + SECOND) % lap ) == 0){
        sprintf(fileName,"DATA/%04d%02d%02d.TXT",YEAR,MONTH,DAY);
        sprintf(entry,"%02d%02d%02d",HOUR,MINUTE,SECOND);
        timestamp = (HOUR * 3600) + (MINUTE * 60) + SECOND;

        if(dataFile = SD.open(fileName, FILE_WRITE)){
        
          if(ONLINE){Serial.print("write ");Serial.println(fileName);}          
    
          readSensorData();
          
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
        } else digitalWrite(ledPin,HIGH); // swith off led ... something is wrong!
      }
    }
  }
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    dataFile =  dir.openNextFile();
    if (!dataFile) break;// no more files
      
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print("read ");
    Serial.println(dataFile.name());
    
    while (dataFile.available()) Serial.write(dataFile.read());
    
    dataFile.close();
    Serial.println("read done");
    
    dataFile.close();
  }
}



