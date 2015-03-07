//simple bluetooth communication
#include <SoftwareSerial.h>

//arbitrarily defined
//waiting for pin diagrams
#define rxPin 10
#define txPin 11

//set up new serial
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
const int ledPin = 13;
int state = 0;        //if state 1 led turns on, otherwise 0
int flag = 0;         //a flag to prevent duplicate messages

void setup() {
  //define pin modes for communication
  pinMode(ledPin, OUTPUT);
  mySerial.begin(9600);
  digitalWrite(ledPin, LOW); //turn off LED initial
  
}

void loop() {
  if (mySerial.available()>0){
      state = mySerial.read();
      flag=0;
  }
  if (state == '0'){
    digitalWrite(ledPin, LOW);
    if(flag == 0){
      mySerial.println("LED: off");
      flag = 1;
    }
  }
  else if (state == '1'){
    digitalWrite(ledPin, HIGH);
    if (flag ==0){
      mySerial.println("LED: on");
      flag = 1;
    }
  }
}
