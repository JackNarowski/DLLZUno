int LED = A1;
int PENT = A3;

#define ZUNO_CHANNEL_NUMBER_ONE   1

byte lastValue;

ZUNO_SETUP_CHANNELS(ZUNO_SENSOR_MULTILEVEL_GENERAL_PURPOSE(getter));
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE);


void setup() {
  pinMode(LED, OUTPUT); // setup pin as output
  pinMode(PENT, INPUT);  // setup potentiometer pin as input
}

void loop() {
  // read potentiometer value and save it inside a variable
  byte currentValue = (byte) (analogRead(PENT) / 4);

  // if the value is different then the previously measured one
  // save it and send a report
  if (currentValue != lastValue) {
    // save the value
    lastValue = currentValue;
    // send report to the controller
    zunoSendReport(ZUNO_CHANNEL_NUMBER_ONE);
  }
}

byte getter(void) {
  byte tempVariable;
  tempVariable = (byte)((((word) lastValue) * 100) / 0xff);
  return tempVariable;
}
   
