
void cmdReader(){

  if (rxData[0] == 'M') MONITOR = parseVal(2);// live data monitor

  if (rxData[0] == 'C') CAPTURE = parseVal(2);// Capture on/off
   
  if (rxData[0] == 'O') ONLINE = parseVal(2);// online board

  if (rxData[0] == 'I') displaySensorDetails();// update board info
  
  if (rxData[0] == 'L') {
    lap = parseVal(2);
    if(SD.exists("lap")) SD.remove("lap");
    if(File file = SD.open("lap",FILE_WRITE)){
      file.print(lap);
      file.close();
    }
  }

   if (rxData[0] == 'G'){
    int gain = parseVal(2);
    if(SD.exists("gain")) SD.remove("gain");
    if(File file = SD.open("gain",FILE_WRITE)){
      file.print(gain);
      file.close();
    }
    setSensorGain(gain);
   }

   if (rxData[0] == 'T'){
    int timing = parseVal(2);
    if(SD.exists("timing")) SD.remove("timing");
    if(File file = SD.open("timing",FILE_WRITE)){
      file.print(timing);
      file.close();
    }
    setSensorTiming(timing);
   }

  if (rxData[0] == 'U'){ // uplodad data
    //boolean temp = CAPTURE = 0;
    //ONLINE = 0;
    path = SD.open("DATA/");
    printDirectory(path,0);
    //ONLINE = 1;
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
