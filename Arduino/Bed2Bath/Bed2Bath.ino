//bed2bath arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

//hardware connections
Servo servo1, servo2, servo3, servo4;
bool door1Open = false;
bool door2Open = false;
int servoAngle1 = 0;
int servoAngle2 = 0;
int servoAngle3 = 0;
int servoAngle4 = 0;
AnalogMux mux(A0, 7, 6, 5, 4);
TempSensor tempSensor1(&mux, 0x0);
TempSensor tempSensor2(&mux, 1);
IrSensor irSensor(&mux, 2);
WindSensor windSensor1(A2, A1);
WindSensor windSensor2(A4, A3);

void setup() {
  //begin bluetooth
  bluetooth.begin(9600);
  Serial.begin(9600);
  //attach servos
  servo1.attach(9);
  servo2.attach(3);
  servo3.attach(13);
  servo4.attach(12);
}

void loop() {
  
    String rxMsg;  
    tempSensor2.ReadTempF();
    //irSensor.ReadVolts();
    /*
    Serial.print(tempSensor1.ReadTempF());
    Serial.print("   ");
    Serial.println(mux.GetSelect(), HEX);
    */
    /*
    Serial.print("   ");
    Serial.print(tempSensor1.ReadTempF());
    Serial.print("   ");
    Serial.println(irSensor.ReadVolts());
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
         int delim = rxMsg.indexOf(":");
         int motorID = rxMsg.charAt(delim+2);
         if (motorID == 1){
           servoAngle1 = 170;
           door1Open = true;
         }
         else if (motorID == 2){
           servoAngle2 = 170;
           door2Open = true;
         }
         bluetooth.println("ok$");
       }
       else if (rxMsg.startsWith("close")){
         int delim = rxMsg.indexOf(":");
         int motorID = rxMsg.charAt(delim+2);
         if (motorID == 1){
           servoAngle1 = 10;
           door1Open = false;
         }
         else if (motorID == 2){
           servoAngle2 = 10;
           door2Open = false;
         }
         bluetooth.println("ok$");

       }
       else if (rxMsg.startsWith("change")){
         int delim = rxMsg.indexOf(":");
         int motorID = rxMsg.charAt(delim+2);
         String angleStr = rxMsg.substring(motorID+2);
         int angle = angleStr.toInt();
         if (motorID == 3){
           servoAngle3 = angle;  
         }
         else if (motorID == 4){
           servoAngle4 = angle;
         }       
         bluetooth.println("ok$");
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
