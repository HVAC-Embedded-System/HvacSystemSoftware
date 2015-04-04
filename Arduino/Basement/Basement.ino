//basement arduino code
#include <SoftwareSerial.h>
#include <HvacPeripheralsLib.h>
#include <Servo.h>

//set up new bluetooth
SoftwareSerial bluetooth = SoftwareSerial(10,11);

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
  servo1.attach();
  servo2.attach();
  servo3.attach();
}

void loop() {
    //if bluetooth available
    if(bluetooth.available()){
      
        //String to store message from bluetooth
        //Define here to reset string each iteration
        String rxMsg;
      
       //read msg to string       
       while(bluetooth.available()){
         //store read data to char
         char c = bluetooth.read();
         //append char to string
         rxMsg += c;
         delay(10);
       } 
        
       //print to serial for debugging       
       Serial.println(rxMsg);
    
     if (rxMsg.equals("poll")){
       //append all data to a string
       String sndData;
       sndData +=("motor1: ");
       sndData += servoAngle1;
       sndData += ("||");
       sndData += ("wind1: ");
       sndData += windSensor1.ReadMph();
       sndData += ("||");
       sndData +=("motor2: ");
       sndData += servoAngle2;
       sndData += ("||");
       sndData += ("wind2: ");
       sndData += windSensor2.ReadMph();
       sndData += ("||");
       sndData +=("motor3: ");
       sndData += servoAngle3;
       sndData += ("||");
       sndData += ("wind3: ");
       sndData += windSensor3.ReadMph();
       
       //send the data
       bluetooth.println(sndData);

       //print end char
       bluetooth.print("$");
     }
    
     //otherwise parse msg
     else{
       if(rxMsg.startsWith("change")){
         //find id of motor to be opened
         int delim = rxMsg.indexOf(":");
         int motorID = rxMsg.charAt(delim+2);
         String angleStr = rxMsg.substring(motorID+2);
         int angle = angleStr.toInt();
         //open motor code here
         if(motorID == 1){
           servoAngle1 = angle;
          }
          else if (motorID == 2){
            servoAngle2 = angle;
          }    
          else if (motorID == 3){
            servoAngle3 = angle;
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
}
