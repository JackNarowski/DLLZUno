#define aref_voltage 3.3
int tempsense = A3;
int lightsense = A1;
int tempinput = 0;
int lightinput = 0;

#define CTRL_GROUP_1 1
#define CTRL_GROUP_2 2

ZUNO_SETUP_ASSOCIATIONS(ZUNO_ASSOCIATION_GROUP_SET_VALUE, ZUNO_ASSOCIATION_GROUP_SET_VALUE);

ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE);
ZUNO_SETUP_CHANNELS(
   ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_TEMPERATURE, 
                          SENSOR_MULTILEVEL_SCALE_CELSIUS, 
                          SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 
                          SENSOR_MULTILEVEL_PRECISION_ONE_DECIMAL,
                          getterTemp),

   ZUNO_SENSOR_MULTILEVEL(ZUNO_SENSOR_MULTILEVEL_TYPE_LUMINANCE,
                             SENSOR_MULTILEVEL_SCALE_LUX,  
                             SENSOR_MULTILEVEL_SIZE_TWO_BYTES, 
                             SENSOR_MULTILEVEL_PRECISION_ZERO_DECIMALS, 
                             getterLight)
);

void setup() {
    pinMode (tempsense, INPUT);
    pinMode (lightsense, INPUT);
    Serial.begin();
    Serial.println("start");  
}

void loop() {
    // obtaining readings from the level sensor
    temp();
    light();
    // send data to channel
    zunoSendReport(1);  
    delay(30000); 
    zunoSendReport(2);  
    // send every 30 second
    delay(30000);
}

byte getterTemp() {
  Serial.println("GETTER TEMP");
    return tempinput;
}

byte getterLight() {
  Serial.println("GETTER LIGHT");
    return lightinput;
}

void temp() {
  tempinput = analogRead(tempsense);
  Serial.print("Temp Sense = "); Serial.println(tempinput);

  int Vo;
  float R1 = 10000;
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  R2 = R1 * (1023.0 / (float)tempinput - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
  T = (T * 9.0) / 5.0 + 32.0;

  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" F");
}

void light() {
  lightinput = analogRead(lightsense);
  Serial.print("Light Sense = "); 
  Serial.println(lightinput);
}
