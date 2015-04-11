//kitchen door arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

//hardware connections
Servo servo;
bool doorOpen = false;
int servoAngle = 0;
TempSensor tempSensor(A0);
IrSensor irSensor(A1);

void setup() {
  //begin bluetooth
  bluetooth.begin(9600);
  Serial.begin(9600);
  //attach servos
  servo.attach(9);
  
  
}

void loop() {
    
    String rxMsg;
    
    //if bluetooth available
    if(bluetooth.available()){
      
       //read msg to string       
       while(bluetooth.available()){
         rxMsg += bluetooth.read();
         delay(10);
       } 
     
     Serial.println(rxMsg);
             
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
         servoAngle = 170;
         bluetooth.println("ok$");
       }
       else if (rxMsg.startsWith("close")){
         servoAngle = 10;
         bluetooth.println("ok$");
       }
       else{
         Serial.println("Unidentified command");
         bluetooth.println("Unidentified command");
       }
     }       
    }
    
    servo.write(servoAngle);
}
