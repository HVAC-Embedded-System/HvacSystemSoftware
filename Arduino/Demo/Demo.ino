//simple bluetooth communication
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>

//arbitrarily defined
//waiting for pin diagrams
#define rxPin 10
#define txPin 11

//set up new serial
SoftwareSerial bluetooth = SoftwareSerial(rxPin, txPin);
const int ledPin = 13;
int state = 0;        //if state 1 led turns on, otherwise 0
int flag = 0;         //a flag to prevent duplicate messages
unsigned int lastSensorUpdateTime = 0;
TempSensor tempSensor(A2);
IrSensor irSensor(A4);
LightSensor lightSensor(A3);
WindSensor windSensor(A1, A0);

void setup() {
    bluetooth.begin(9600);
    Serial.begin(9600);
}

void loop() {
    if (bluetooth.available()){
        Serial.print("Msg rx: ");

        while (bluetooth.available()){
            Serial.write(bluetooth.read());

        }
        
        Serial.println();
    }

    if ((micros() - lastSensorUpdateTime) >= 10000000){
        Serial.print("Temperature (F): ");
        Serial.print(tempSensor.ReadTempF());
        Serial.println();

        Serial.print("IR Sensor (V): ");
        Serial.print(irSensor.ReadVolts());
        Serial.println();

        Serial.print("Light Sensor (ohms): ");
        Serial.print(lightSensor.ReadOhms());
        Serial.println();

        Serial.print("Wind Speed (mph): ");
        Serial.print(windSensor.ReadMph());
        Serial.println();
    }
}
