void loadSettings(){
  Serial.println("loading settings");
  
  if(File file = SD.open("gain")){
    String val;
    while (file.available()) val += (char)file.read(); 
    gain = val.toInt();
    setSensorGain(gain);
  }
  
  if(File file = SD.open("timing")){
    String val;
    while (file.available()) val += (char)file.read(); 
    timing = val.toInt();
    setSensorTiming(timing);
  }
  
  if(File file = SD.open("lap")){
    String val;
    while (file.available()) val += (char)file.read(); 
    lap = val.toInt();
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

  if(ONLINE){
    char timeNow[50];
    sprintf(timeNow,"date %04d/%02d/%02d %s %02d:%02d:%02d",
      YEAR,MONTH,DAY,
      daysOfTheWeek[DAYOFTHEWEEK],
      HOUR,MINUTE,SECOND);     
    Serial.println(timeNow);
  }
}




