//kitchen door arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

//store bluetooth msg for parsing
String rxMsg;

//hardware connections
Servo servo;
bool doorOpen = false;
int servoAngle = 0;
TempSensor tempSensor();
IrSensor irSensor();

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
       sndData +=("temp: ");
       sndData += tempSensor.ReadTempF();
       sndData += ("||");
       sndData += ("motor1: ");
       sndData += servoAngle;
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
         bluetooth.println("Kitchen door opened.");
       }
       else if (rxMsg.startsWith("close")){
         //servoAngle = some angle
         bluetooth.println("Kitchen door closed.");
       }
       else{
         Serial.println("Unidentified command");
         bluetooth.println("Unidentified command");
       }
     }       
    }
    
    servo.write(servoAngle);
}
