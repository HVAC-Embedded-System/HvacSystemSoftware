//bed2bath arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

//store bluetooth msg for parsing
String rxMsg;

//hardware connections
Servo servo1, servo2, servo3, servo4;
bool door1Open = false;
bool door2Open = false;
int servoAngle1 = 0;
int servoAngle2 = 0;
int servoAngle3 = 0;
int servoAngle4 = 0;
TempSensor tempSensor1();
TempSensor tempSensor2();
IrSensor irSensor();
WindSensor windSensor1();
WindSensor windSensor2();

void setup() {
  //begin bluetooth
  bluetooth.begin(9600);
  Serial.begin(9600);
  //attach servos
  servo.attach();
  
  
}

void loop() {
    //if bluetooth available
    if(bluetooth.available()){
      
       //read msg to string       
       while(bluetooth.available()){
         rxMsg += bluetooth.read();
         Serial.println(rxMsg);
         delay(10);
       } 
    
     if (rxMsg == "poll"){
       //send all data
       String sndData;
       sndData +=("temp1: ");
       sndData += tempSensor1.ReadTempF();
       sndData += ("||");
       sndData +=("temp2: ");
       sndData += tempSensor2.ReadTempF();
       sndData += ("||");
       sndData += ("motor1: ");
       sndData += servoAngle1;
       sndData += ("||");
       sndData += ("motor2: ");
       sndData += servoAngle2;
       sndData += ("||");
       sndData += ("motor3: ");
       sndData += servoAngle3;
       sndData += ("||");
       sndData += ("motor4: ");
       sndData += servoAngle4;
       sndData += ("||");
       sndData += ("wind1: ");
       sndData += windSensor1.ReadMph();
       sndData += ("||");
       sndData += ("wind2: ");
       sndData += windSensor2.ReadMph();
       sndData += ("||");
       sndData +=("ir: ");
       sndData += irSensor.ReadVolts();
       
       //send the data as a string
       bluetooth.println(sndData);

       //print end char
       bluetooth.print("$");
     }
    
     //otherwise parse msg
     else{
       if(rxMsg.startsWith("open")){
         //servoAngle = some angle

       }
       else if (rxMsg.startsWith("close")){
         //servoAngle = some angle

       }
       else{
         Serial.println("Unidentified command");
         bluetooth.println("Unidentified command");
       }
     }       
    }
    
    servo1.write(servoAngle1);
    servo2.write(servoAngle2);
    servo3.write(servoAngle3);
    servo4.write(servoAngle4);
}
