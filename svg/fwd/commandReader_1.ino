
void cmdReader(){
  uint16_t val = parseVal(2);
   
  if (rxData[0] == 'O') ONLINE = val;           // set online tag

  if (rxData[0] == 'I') displaySensorDetails(); // **** update board info
  
  if (rxData[0] == 'L') {                       // **** set timelap (seconds) 
    writeSD("lap", val);
    lap = val;
  }

   if (rxData[0] == 'G'){                       // **** set gain value
    writeSD("gain", val);
    setSensorGain(val);  
   }

   if (rxData[0] == 'T'){                       // **** set intergration time value
    writeSD("timing", val);
    setSensorTiming(val);
   }

   if (rxData[0] == 'l') {                       // **** set lower therhold value
    TLS2591_INT_THRESHOLD_LOWER = val;
    writeSD("thl", TLS2591_INT_THRESHOLD_LOWER);
    setThreshold();
   }

   if (rxData[0] == 'D'){
    uint16_t YYYY = ((rxData[2] - 48) * 1000) + ((rxData[3] - 48) * 100) + ((rxData[4] - 48) * 10) + (rxData[5] - 48);
    uint16_t MM = ((rxData[6] - 48) * 10) + (rxData[7] - 48);
    uint16_t DD = ((rxData[8] - 48) * 10) + (rxData[9] - 48);
    uint16_t hh = ((rxData[11] - 48) * 10) + (rxData[12] - 48);
    uint16_t mm = ((rxData[13] - 48) * 10) + (rxData[14] - 48);
    uint16_t ss = ((rxData[15] - 48) * 10) + (rxData[16] - 48);
    rtc.adjust(DateTime(YYYY,MM,DD,hh,mm,ss));
    /*
    Serial.println (YYYY);
    Serial.println (MM);
    Serial.println (DD);
    Serial.println (hh);
    Serial.println (mm);
    Serial.println (ss);
    */
   }
 
   if (rxData[0] == 'U'){                       // **** upload data
    path = SD.open("DATA/");
    ONLINE = 0;
    LOWLIGHT = 1;
    printDirectory(path,0);
    }
 
  DATA_AVAILABLE = 0;
  rxOffset = 0;
}

 long parseVal(int offset){
  
  for(int i = 0; i < MAXSIZE; i++) outParse[i] = -1;
  
  int i = offset;
  
  while(i < rxOffset){
    if(rxData[i] == ' ') break;
    outParse[i - offset] = rxData[i];
    i ++;
  }
  
  return(atol(outParse));
}
