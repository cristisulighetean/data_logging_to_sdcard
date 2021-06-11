#include<Arduino.h>

// SEN0257  parameter
#define SEN0257PIN A0
const float offSet = 0.483 ;
float voltage, pressure;

void setup(){

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
    
    voltage = analogRead(0) * 5.00 / 1024; //Sensor output voltage
    pressure = (voltage - offSet) * 400; //Calculate water pressure

    // Print output
    Serial.print("Voltage:");
    Serial.print(voltage, 3);
    Serial.println("V");
    Serial.print(" Pressure:");
    Serial.print(pressure, 1);
    Serial.println(" KPa");
    Serial.println();

    delay(500);

}