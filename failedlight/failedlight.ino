
#include "ZUNO_DHT.h"
int lightsense = A1;
 byte currentlightvalue;
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE);
ZUNO_SETUP_CHANNELS(
   ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_LUMINANCE, 
                          SENSOR_MULTILEVEL_SCALE_LUX,  
                          SENSOR_MULTILEVEL_SIZE_ONE_BYTE, 
                          SENSOR_MULTILEVEL_PRECISION_ZERO_DECIMALS,
                          getterLight)
);

int level;  // here we will store the data sensor
int levelpercent;  // here we will store the value level percent

void setup() {
    pinMode (lightsense, INPUT);
    Serial.begin();
    Serial.println("start");  
}

void loop() {
    // obtaining readings from the level water sensor
    currentlightvalue  = (byte)(analogRead(lightsense));
    Serial.print("currentlightvalue = ");
    Serial.println(currentlightvalue);     
    // send data to channel
    zunoSendReport(1);     
    // send every 30 second
    delay(10000);
}

byte getterLight() {
  Serial.println("GETTER");
    return currentlightvalue;
}
