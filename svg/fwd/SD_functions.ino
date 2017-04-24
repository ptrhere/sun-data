/**************************************************************************/
/*
    SD functions
    SD and wire lib
*/
/**************************************************************************/

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

  if(File file = SD.open("thl")){
    String val;
    while (file.available()) val += (char)file.read(); 
    TLS2591_INT_THRESHOLD_LOWER = val.toInt();
    setThreshold();
  }
}

void writeSD(char* add, uint32_t data){
 
  if(SD.exists(add)) SD.remove(add);
  if(File file = SD.open(add,FILE_WRITE)){
    file.print(data);
    file.close();
  }
}

void printDirectory(File dir, int numTabs) {
  
  while (true) {
    File entry =  dir.openNextFile();
    
    if (!entry) break;// no more files
    
    Serial.print("read ");
    Serial.println(entry.name());
    /*
    Serial.print("ID ");
    Serial.println (ID);
    */
    while (entry.available()) Serial.write(entry.read());
    
    entry.close();

    Serial.println("read done");

  }
  Serial.println("read finish");
}
