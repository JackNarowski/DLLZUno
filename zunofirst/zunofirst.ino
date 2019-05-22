int LED = A1;
byte currentLEDValue;
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(getter, setter));
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE);

void setup() {
  pinMode (LED, OUTPUT);
}

void loop() {
}

void setter(byte value){
   if (value > 0) {               // if greater then zero
    digitalWrite (LED, HIGH); //turn the LED on (HIGH is the voltage level)
  } else {                         // if equals zero
    digitalWrite(LED, LOW);   //turn the LED off by making the voltage LOW
  }
  // we'll save our value for the situation, when the controller will ask us about it
  currentLEDValue = value;
}

byte getter() {
   return currentLEDValue;
}
