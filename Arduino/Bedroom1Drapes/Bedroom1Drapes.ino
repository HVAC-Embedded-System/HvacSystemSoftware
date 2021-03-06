//bedroom 1 drapes arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

int servoAngle = 0;
Servo servo;
bool drapesOpen = false;
TempSensor tempSensor(A1);
LightSensor lightSensor(A0);

void setup() {
  //begin bluetooth
  bluetooth.begin(9600);
  Serial.begin(9600);
  //attach servos
  servo.attach(3);
  servoAngle = 94;
  servo.write(servoAngle);
}

void loop() {
  //store bluetooth msg for parsing
  String rxMsg;
  
  /*
  Serial.print(tempSensor.ReadTempF());
  Serial.print("   ");
  Serial.println(lightSensor.ReadOhms());
  */
  
    //if bluetooth available
    if(bluetooth.available()){
       //read msg to string       
       while(bluetooth.available()){
         char c = bluetooth.read();
         rxMsg += c;
         delay(10);
       } 
    
     Serial.println(rxMsg);
    
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
       sndData += ("||");
     
       //send the data as a string
       bluetooth.println(sndData);

       //print end char
       bluetooth.print("$");
     }
    
     //otherwise parse msg
     else{
       if(rxMsg.startsWith("open")){
        servoAngle = 0;
        servo.write(servoAngle);
        //delay for 2 seconds while blinds open
        delay(20000);
        servoAngle = 94;
        servo.write(servoAngle);
        drapesOpen = true;                 
        bluetooth.println("ok$");
       }
       else if (rxMsg.startsWith("close")){
         servoAngle = 180;
         servo.write(servoAngle);
         delay(20000);
         servoAngle = 94;
         servo.write(servoAngle);
         drapesOpen = false;
         bluetooth.println("ok$");    
       }
       else{
         Serial.println("Unidentified command");
         bluetooth.println("Unidentified command");
       }
     }       
    }
        
    servo.write(94);
}
