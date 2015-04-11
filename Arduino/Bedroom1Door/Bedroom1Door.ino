//bedroom 1 door arduino code
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
    /*
    Serial.print(tempSensor.ReadTempF());
    Serial.print("   ");
    Serial.println(irSensor.ReadVolts());
    */
    
    //if bluetooth available
    if(bluetooth.available()){
        
        //String to store message from bluetooth
        //Define here to reset string each iteration
        String rxMsg;
        
       //read msg to string       
       while(bluetooth.available()){
         char c = bluetooth.read();
         rxMsg += c;
         delay(10);
       } 
     //print for debugging
     Serial.println(rxMsg);
    
     if (rxMsg.equals("poll")){
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
           doorOpen = true;
         bluetooth.println("ok$");
       }
       else if (rxMsg.startsWith("close")){
           servoAngle = 10;
           doorOpen = false;
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
