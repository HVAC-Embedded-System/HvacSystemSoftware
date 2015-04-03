//kitchen drapes arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

//store bluetooth msg for parsing
String rxMsg;

int servoAngle = 0;
Servo servo;
TempSensor tempSensor(A1);
LightSensor lightSensor(A0);

void setup() {
  //begin bluetooth
  bluetooth.begin(9600);
  Serial.begin(9600);
  //attach servos
  servo.attach(3);
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
       sndData +=("light: ");
       sndData += lightSensor.ReadOhms();
       sndData += ("||");
       sndData +=("temp: ");
       sndData += tempSensor.ReadTempF();
       sndData += ("||");
       sndData += ("motor1: ");
       sndData += servoAngle;
       
       //send the data as a string
       bluetooth.println(sndData);

       //print end char
       bluetooth.print("$");
     }
    
     //otherwise parse msg
     else{
       if(rxMsg.startsWith("open")){
         servoAngle = 0;                   
         bluetooth.println("Drapes opened successfully.");
       }
       else if (rxMsg.startsWith("close")){
         servoAngle = 360;
         bluetooth.println("Drapes closed successfully.");    
       }
       else{
         Serial.println("Unidentified command");
         bluetooth.println("Unidentified command");
       }
     }       
    }
    servo.write(servoAngle);
}
