//simple bluetooth communication
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//arbitrarily defined
//waiting for pin diagrams
#define rxPin 10
#define txPin 11

//set up new serial
SoftwareSerial bluetooth = SoftwareSerial(rxPin, txPin);
const int ledPin = 13;
int state = 0;        //if state 1 led turns on, otherwise 0
int flag = 0;         //a flag to prevent duplicate messages
unsigned long lastSensorUpdateTime = 0;
TempSensor tempSensor(A2);
IrSensor irSensor(A4);
LightSensor lightSensor(A3);
WindSensor windSensor(A1, A0);

bool doorOpen = false;
int servoAngle = 10;
Servo servo;

void setup() {
    bluetooth.begin(9600);
    Serial.begin(115200);
    servo.attach(9);
}

void loop() {
    if (bluetooth.available()){
        
        float temp = tempSensor.ReadTempF();
        
        Serial.print("Msg rx: ");

        while (bluetooth.available()){
            char c = bluetooth.read();
            Serial.print(c);
            //Serial.write("\0");
            
            if (c == '1'){
                doorOpen = true;
                servoAngle = 170;
            }
            else{
                doorOpen = false;
                servoAngle = 10;
            }
            
            delay(1);
        }
        Serial.println();
        
        if (doorOpen){
          bluetooth.println("Door Open");
        }
        else{
            bluetooth.println("Door Closed");
        }

        bluetooth.print("Temperature (F): ");
        bluetooth.print(temp);
        bluetooth.println();

        bluetooth.print("IR Sensor (V): ");
        bluetooth.print(irSensor.ReadVolts());
        bluetooth.println();

        bluetooth.print("Light Sensor (ohms): ");
        bluetooth.print(lightSensor.ReadOhms());
        bluetooth.println();

        bluetooth.print("Wind Speed: tmp: ");
        bluetooth.print(windSensor.ReadTmp());
        bluetooth.print("   rv: ");
        bluetooth.print(windSensor.ReadRv());
        bluetooth.println();
        bluetooth.println();
       
        bluetooth.print("$");
        Serial.println();
    }

    if ((millis() - lastSensorUpdateTime) >= 2000){
        if (doorOpen){
            Serial.println("Door open");
        }
        else{
            Serial.println("Door closed");
        }
        
        Serial.print("Temperature (F): ");
        Serial.print(tempSensor.ReadTempF());
        Serial.println();

        Serial.print("IR Sensor (V): ");
        Serial.print(irSensor.ReadVolts());
        Serial.println();

        Serial.print("Light Sensor (ohms): ");
        Serial.print(lightSensor.ReadOhms());
        Serial.println();

        Serial.print("Wind Speed: tmp: ");
        Serial.print(windSensor.ReadTmp());
        Serial.print("   rv: ");
        Serial.print(windSensor.ReadRv());
        Serial.println();
        Serial.println();
        
        lastSensorUpdateTime = millis();
    }
    
    servo.write(servoAngle);
}
