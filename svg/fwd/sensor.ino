/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("ONLINE");ONLINE = 1;
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
  Serial.print  ("Gain:         ");Serial.println(tsl.getGain() >> 4);
  Serial.print  ("Timing:       ");Serial.println(tsl.getTiming());
  Serial.print  ("Laps:         ");Serial.println(lap);
  Serial.print  ("Capturing:    ");Serial.println(CAPTURE);
  
}

void readSensorData(){
  lum = tsl.getFullLuminosity();  
  ir = lum >> 16;
  full = lum & 0xFFFF;
  lux = tsl.calculateLux(full, ir);
  if (lux >> 16 == 0xFFFF){
    readSensorData();
    delay(2);
  }
}

void displayLiveData(){
  readSensorData();
  Serial.print("data ");
  Serial.print(ir);
  Serial.print(" ");
  Serial.print(full);
  Serial.print(" ");
  Serial.print(lux >> 16);
  Serial.print(" ");
  Serial.println(lux & 0xFFFF);
}

void blinkLed(){
  digitalWrite(ledPin,HIGH);
  delay(50);
  digitalWrite(ledPin,LOW);
}

void setSensorGain(int val){
  switch(val){
      
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

void setSensorTiming(int val){
  switch(val){
      
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

