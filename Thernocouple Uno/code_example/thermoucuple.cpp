#include <Arduino.h>

#include "max6675.h"

int thermoDO = 3;
int thermoCLK = 2;

// Chip select pins
int thermoCS1 = 4;
int thermoCS2 = 5;
int thermoCS3 = 6;
int thermoCS4 = 7;
int thermoCS5 = 8;
int thermoCS6 = 9;
int thermoCS7 = 10;
int thermoCS8 = 11;


// Thermocouple objects
MAX6675 tc1(thermoCLK, thermoCS1, thermoDO);
MAX6675 tc2(thermoCLK, thermoCS2, thermoDO);
MAX6675 tc3(thermoCLK, thermoCS3, thermoDO);
MAX6675 tc4(thermoCLK, thermoCS4, thermoDO);

MAX6675 tc5(thermoCLK, thermoCS5, thermoDO);
MAX6675 tc6(thermoCLK, thermoCS6, thermoDO);
MAX6675 tc7(thermoCLK, thermoCS7, thermoDO);
MAX6675 tc8(thermoCLK, thermoCS8, thermoDO);




void setup() {
  Serial.begin(115200);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(1000);
}

void loop() {
  // basic readout test, just print the current temp
  
   Serial.print("C1 = "); 
   Serial.println(tc1.readCelsius());
   Serial.print("C2 = ");
   Serial.println(tc2.readCelsius());
   Serial.print("C3 = ");
   Serial.println(tc3.readCelsius());
   Serial.print("C4 = ");
   Serial.println(tc4.readCelsius());
   Serial.print("C5 = ");
   Serial.println(tc5.readCelsius());
   Serial.print("C6 = ");
   Serial.println(tc6.readCelsius());
   Serial.print("C7 = ");
   Serial.println(tc7.readCelsius());
   Serial.print("C8 = ");
   Serial.println(tc8.readCelsius());
 
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(2000);
}
