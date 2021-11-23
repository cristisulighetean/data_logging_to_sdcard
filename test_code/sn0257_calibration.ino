#include<Arduino.h>

// SEN0257  parameters
#define SEN0257PIN_1 A0
#define SEN0257PIN_2 A1

// Offset to calibrate
const float offSet = 0.483 ;

float voltage1, pressure1;
float voltage2, pressure2;


void setup(){
    Serial.begin(115200);
}


void loop(){
    calibateSensor();
}

void calibateSensor(){
    /************************************************************
     Water Sensor Calibration

    The output voltage offset of the sensor is 0.5V (norminal).
    However, due to the zero-drifting of the internal circuit, the
    no-load output voltage is not exactly 0.5V. Calibration needs to
    be carried out as follow.

    Calibration: connect the 3 pin wire to the Arduio UNO (VCC, GND and Signal)
    without connecting the sensor to the water pipe and run the program
    for once. Mark down the LOWEST voltage value through the serial
    monitor and revise the "OffSet" value to complete the calibration.
    After the calibration the sensor is ready for measuring!
    **************************************************************/
    
    // Sensor 1
    voltage1 = analogRead(0) * 5.00 / 1024; //Sensor output voltage
    pressure1 = (voltage1 - offSet) * 400; //Calculate water pressure

    // Sensor 2
    voltage2 = analogRead(1) * 5.00 / 1024; //Sensor output voltage
    pressure2 = (voltage2 - offSet) * 400; //Calculate water pressure

    // Print output
    Serial.print("Voltage Sensor 1:");
    Serial.print(voltage1, 3);
    Serial.println("V");
    Serial.print("Pressure Sensor 1:");
    Serial.print(pressure1, 1);
    Serial.println(" KPa");
    Serial.println();

    Serial.print("Voltage Sensor 2:");
    Serial.print(voltage2, 3);
    Serial.println("V");
    Serial.print("Pressure Sensor 2:");
    Serial.print(pressure2, 1);
    Serial.println(" KPa");
    Serial.println();

    delay(500);
}