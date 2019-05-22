int lightsense = A3;

#define ZUNO_CHANNEL_NUMBER_ONE   1

byte lastValue;

ZUNO_SETUP_CHANNELS(ZUNO_SENSOR_MULTILEVEL_GENERAL_PURPOSE(getter));
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE);


void setup() {
  pinMode(lightsense, INPUT);
  Serial.begin();
}

void loop() {
  // read sensor value and save it inside a variable
  //byte currentValue = (byte) (analogRead(PENT) / 4);
  byte currentlightvalue = (byte)(analogRead(lightsense)/4);
  Serial.print("Light Sense = ");
  Serial.println(currentlightvalue);

  // if the value is different then the previously measured one
  // save it and send a report
  if (currentlightvalue != lastValue) {
    // save the value
    lastValue = currentlightvalue;
    // send report to the controller
    zunoSendReport(1);
  }
  delay(2000);
}

byte getter(void) {
  byte tempVariable;
  tempVariable = (byte)((((word) lastValue) * 100) / 0xff);
  return tempVariable;
}
   
