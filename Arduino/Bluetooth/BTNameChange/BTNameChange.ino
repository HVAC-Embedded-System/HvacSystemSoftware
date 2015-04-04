#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // RX, TX

void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  bluetooth.begin(9600);
  bluetooth.println("Hello, world?");
}

void loop() // run over and over
{
  if (bluetooth.available())
    Serial.write(bluetooth.read());
  if (Serial.available())
    bluetooth.write(Serial.read());
}
