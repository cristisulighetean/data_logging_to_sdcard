#include <Arduino.h>
#include <SPI.h>
#include "SD.h"
#include "max6675.h"

#define DEBUG 

// SEN0257 sensors parameters
#define SEN0257PIN_1 A0
#define SEN0257PIN_2 A1
const float offSet = 0.483 ;
float voltage1, voltage2; 
float pressure1, pressure2;

// SN-S201 Sensor parametes
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 20; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;

void flow () // Interrupt function for flow sensor
{
   flow_frequency++;
}

// Switch 
int switch_pin = 21; 
int led_pin = 22;

/* Pins for SD card SPI
  CS - 53
  SCK - 52
  MOSI - 51
  MISO - 50
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

// Thermocouples variables
float c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;


// Function headers
void writeData(void);
void getTempReading(void);
void getSN025Data(void);
void getFlowData(void);

void setup() {

#ifdef DEBUG 
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    delay(2000);
#endif

/*
    Serial.println("DataLogging from Thermocuples");

    // Init SD Card
    Serial.print("Initializing SD card...");
#endif
    if (!SD.begin(10)) {
#ifdef DEBUG
        Serial.println("initialization failed!");
#endif

        while (1);
    }
#ifdef DEBUG
    Serial.println("initialization done.");
#endif

*/
    // Flow sensor setup
    pinMode(flowsensor, INPUT);
    digitalWrite(flowsensor, HIGH);   // Optional Internal Pull-Up
    attachInterrupt(0, flow, RISING); // Setup Interrupt
    sei(); // Enable interrupts
    
    // Get current time
    currentTime = millis();
    cloopTime = currentTime;

    // Switch
    pinMode(switch_pin, INPUT);

    // Led
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);

}
void loop() {
  
  if (digitalRead(switch_pin) == 1){
    // turn on LED
    digitalWrite(led_pin, HIGH);
    
    currentTime = millis();
    cloopTime = currentTime;

    // Every second, make a request
    if(currentTime >= (cloopTime + 1000))
    {
        cloopTime = currentTime; // Updates cloopTime
        writeData(); 
    }
  }
  else {digitalWrite(led_pin, LOW);}
}

void getTempReading(void){

   c1 = tc1.readCelsius();
   c2 = tc2.readCelsius();
   c3 = tc3.readCelsius();
   c4 = tc4.readCelsius();
   c5 = tc5.readCelsius();
   c6 = tc6.readCelsius();
   c7 = tc7.readCelsius();
   c8 = tc8.readCelsius();

#ifdef DEBUG
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
#endif
}

void writeData(void){
  // Open the file, read temp, write to file
  dataLogFile = SD.open("log.txt", FILE_WRITE);


  // Write to the file
  if (dataLogFile) {

    // Read sensors
    getTempReading();
    getFlowData();
    getSN025Data();

    // Temp data 
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

    // Flow data 
    dataLogFile.print(l_hour);
    dataLogFile.println(",");

    // Pressure data 
    dataLogFile.print(pressure1);
    dataLogFile.println(",");

    dataLogFile.print(pressure2);
    dataLogFile.println(",");

    // Close the file:
    dataLogFile.close();
#ifdef DEBUG
    Serial.println("Done writing.");
#endif
  } else {
#ifdef DEBUG
    // if the file didn't open, print an error:
    Serial.println("Error opening log.txt");
#endif
  }
}


void getSN025Data(void){

  // Sensor 1
  voltage1 = analogRead(SEN0257PIN_1) * 5.00 / 1024; //Sensor output voltage
  pressure1 = (voltage1 - offSet) * 400; //Calculate water pressure

  // Sensor 2
  voltage2 = analogRead(SEN0257PIN_2) * 5.00 / 1024; //Sensor output voltage
  pressure2 = (voltage2 - offSet) * 400; //Calculate water pressure

#ifdef DEBUG 
    // Print output sensor 1
    Serial.print("Voltage:");
    Serial.print(voltage1, 3);
    Serial.println("V");
    Serial.print("Pressure:");
    Serial.print(pressure1, 1);
    Serial.println(" KPa");
    Serial.println();

    // Print output sensor 2
    Serial.print("Voltage:");
    Serial.print(voltage2, 3);
    Serial.println("V");
    Serial.print(" Pressure:");
    Serial.print(pressure2, 1);
    Serial.println(" KPa");
    Serial.println();
#endif
}


void getFlowData(void){
  
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter

#ifdef DEBUG
      Serial.print(l_hour, DEC); // Print litres/hour
      Serial.println(" L/hour");
#endif
}
