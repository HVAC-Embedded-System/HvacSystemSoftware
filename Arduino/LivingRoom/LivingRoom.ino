#include <HvacPeripheralsLib.h>

TempSensor tempSensor1(A0);
TempSensor tempSensor2(A2);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println("----------------------");
    Serial.println(tempSensor1.ReadTempF());
    Serial.println(tempSensor2.ReadTempF());
    Serial.println("----------------------");
    
    delay(1000);
}
