//basement arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

//store bluetooth msg for parsing
String rxMsg;

//declare 3 wind sensors here
WindSensor windSensor1();
WindSensor windSensor2();
WindSensor windSensor3();

//give these better names
//correlating to where the duct goes
int servoAngle1 = 0;
int servoAngle2 = 0;
int servoAngle3 = 0;
Servo servo1, servo2, servo3;

void setup() {
  //begin bluetooth
  bluetooth.begin(9600);
  Serial.begin(9600);
  //attach servos
  
  
  
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
       sndData +=("motor1: ");
       sndData += servoAngle1;
       sndData += ("||");
       sndData += ("wind1: ");
       sndData += windSensor1.ReadMph();
       sndData +=("motor2: ");
       sndData += servoAngle2;
       sndData += ("||");
       sndData += ("wind2: ");
       sndData += windSensor2.ReadMph();
       sndData +=("motor3: ");
       sndData += servoAngle3;
       sndData += ("||");
       sndData += ("wind3: ");
       sndData += windSensor3.ReadMph();
       
       //send the data as a string
       bluetooth.println(sndData);

       //print end char
       bluetooth.print("$");
     }
    
     //otherwise parse msg
     else{
       if(rxMsg.startsWith("open")){
         //find id of motor to be opened
         int delim = rxMsg.indexOf(":");
         int motorID = rxMsg.charAt(delim+2);
         //open motor code here
                   
         bluetooth.println("Motor " +motorID+ " opened successfully.");
       }
       else if (rxMsg.startsWith("close")){
         //find id of motor to close
         int delim = rxMsg.indexOf(":");
         char motorID = rxMsg.charAt(delim+2);
         //close motor code here
           if (motorID=='1'){
             //servoAngle1 = some angle
           }
           else if (motorID == '2'){
             //servoAngle2 = some angle
           }
           else (motorID == '3'){
             //servoAngle3 = some angle
           }
         //send success message
         bluetooth.println("Motor " +motorID+ " closed successfully.");    
       }
       else{
         Serial.println("Unidentified command");
         bluetooth.println("Unidentified command");
       }
     }       
    }
}
