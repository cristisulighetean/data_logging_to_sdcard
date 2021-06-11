#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "max6675.h"

/* Pins for SD card SPI
  CS - 10
  SCK - 13
  MOSI - 11
  MISO - 12
*/

// SPI MAX6675 pins
int thermoCLK = 2;
int thermoSO = 3;

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
MAX6675 tc1(thermoCLK, thermoCS1, thermoSO);
MAX6675 tc2(thermoCLK, thermoCS2, thermoSO);
MAX6675 tc3(thermoCLK, thermoCS3, thermoSO);
MAX6675 tc4(thermoCLK, thermoCS4, thermoSO);

MAX6675 tc5(thermoCLK, thermoCS5, thermoSO);
MAX6675 tc6(thermoCLK, thermoCS6, thermoSO);
MAX6675 tc7(thermoCLK, thermoCS7, thermoSO);
MAX6675 tc8(thermoCLK, thermoCS8, thermoSO);

// SD Card 
File dataLogFile;

// Thermocouples
float c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;

// Function headers
void writeData(void);
void getTempReading(void);

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    delay(2000);

    Serial.println("DataLogging from Thermocuples");

    // Init SD Card
    Serial.print("Initializing SD card...");
    if (!SD.begin(10)) {
        Serial.println("initialization failed!");
        while (1);
    }
    Serial.println("initialization done.");
    
}
void loop() {

  writeData();
  delay(1000);

}

void getTempReading(void){

   Serial.print("C1 = ");
   c1 = tc1.readCelsius();
   Serial.println(tc1.readCelsius());

   Serial.print("C2 = ");
   c2 = tc2.readCelsius();
   Serial.println(tc2.readCelsius());

   Serial.print("C3 = ");
   c3 = tc3.readCelsius();
   Serial.println(tc3.readCelsius());

   Serial.print("C4 = ");
   c4 = tc4.readCelsius();
   Serial.println(tc4.readCelsius());

   Serial.print("C5 = ");
   c5 = tc5.readCelsius();
   Serial.println(tc5.readCelsius());

   Serial.print("C6 = ");
   c6 = tc6.readCelsius();
   Serial.println(tc6.readCelsius());

   Serial.print("C7 = ");
   c7 = tc7.readCelsius();
   Serial.println(tc7.readCelsius());

   Serial.print("C8 = ");
   c8 = tc8.readCelsius();
   Serial.println(tc8.readCelsius());
}

void writeData(void){
  // Open the file, read temp, write to file
  dataLogFile = SD.open("log.txt", FILE_WRITE);


  // Write to the file
  if (dataLogFile) {
    getTempReading();

    dataLogFile.print(c1);
    dataLogFile.print(",");

    dataLogFile.print(c2);
    dataLogFile.print(",");
    
    dataLogFile.print(c3);
    dataLogFile.print(",");

    dataLogFile.print(c4);
    dataLogFile.print(",");

    dataLogFile.print(c5);
    dataLogFile.print(",");

    dataLogFile.print(c6);
    dataLogFile.print(",");

    dataLogFile.print(c7);
    dataLogFile.print(",");

    dataLogFile.print(c8);
    dataLogFile.println(",");


    // Close the file:
    dataLogFile.close();
    Serial.println("Done writing.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error opening log.txt");
  }

}