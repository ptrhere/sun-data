/**************************************************************************/
/*
    Displays information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("ONLINE");ONLINE = 1;
  Serial.print  ("sensor "); Serial.println(sensor.name);
  Serial.print  ("id "); Serial.println(ID);
  Serial.print  ("max "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("min "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("resolution "); Serial.print(sensor.resolution); Serial.println(" lux");  
  Serial.print  ("gain ");Serial.println(tsl.getGain() >> 4);
  Serial.print  ("timing ");Serial.println(tsl.getTiming());
  Serial.print  ("laps ");Serial.println(lap);
  Serial.print  ("low ");Serial.println(TLS2591_INT_THRESHOLD_LOWER);
  Serial.print  ("capture ");Serial.println(!LOWLIGHT);
  
}

void readSensorData(){
  
  full = tsl.getLuminosity(TSL2591_FULLSPECTRUM);
  ir = tsl.getLuminosity(TSL2591_INFRARED);  
  lux = tsl.calculateLux(full, ir);
  
  //if (ir > full) lux = 0; // lux calculation correction
}


void setSensorGain(int GAIN_){
  
  switch(GAIN_){
      
      case 0:
      tsl.setGain(TSL2591_GAIN_LOW);   // 1x gain
      break;

      case 1:
      tsl.setGain(TSL2591_GAIN_MED);   // 25x gain
      break;

      case 2:
      tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
      break;
      
      case 3:
      tsl.setGain(TSL2591_GAIN_MAX);   // 2591x gain
      break;
      
    }
}

void setSensorTiming(int TIMING_){
  
  switch(TIMING_){
      
      case 0:
      tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);
      break;

      case 1:
      tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
      break;

      case 2:
      tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
      break;
      
      case 3:
      tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
      break;

      case 4:
      tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
      break;

      case 5:
      tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);
      break;
      
    }
}

void setThreshold(){
  tsl.clearInterrupt();
  
  tsl.registerInterrupt(
        TLS2591_INT_THRESHOLD_LOWER, 
        TLS2591_INT_THRESHOLD_UPPER,
        TSL2591_PERSIST_ANY);
}

void getStatus(void)
{
  // bit 4: ALS Interrupt occured
  // bit 5: No-persist Interrupt occurence
  LOWLIGHT = (tsl.getStatus() >> 4) & 1;

  /*Serial.print("Status: ");
  Serial.println(x, BIN);*/
  
  tsl.clearInterrupt();
}
