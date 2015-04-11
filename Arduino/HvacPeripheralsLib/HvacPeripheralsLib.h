#if !defined HVACPERIPHERALSLIB_h
#define HVACPERIPHERALSLIB_h

#include <stdint.h>

// Class used to control analog mux that expands the amount
// of analog inputs the system can use.
class AnalogMux
{
public:
    // Initialize with pin to read for inputs and each select pin.
    AnalogMux(uint8_t analogPin, uint8_t sel0, uint8_t sel1, uint8_t sel2, uint8_t sel3);
    void SetSelect(uint8_t select);
    uint8_t GetSelect();
    int ReadAnalogPin();
private:
    uint8_t analogPin;
    uint8_t sel0;
    uint8_t sel1;
    uint8_t sel2;
    uint8_t sel3;
};

// Class used to obtain measurements from analog signals.
class AnalogSensor
{
public:
    // If analog pin is muxed, a pointer to the mux object is required.
    AnalogSensor(AnalogMux* mux, uint8_t muxSel);

    // If analog pin is not muxed, just a pin number is required.
    AnalogSensor(uint8_t pin);

    float ReadVolts();

private:
    uint8_t pin;

    AnalogMux* mux;
    uint8_t muxSel;
};

// Class used to obtain temperature measurements from TMP36 device
class TempSensor : public AnalogSensor
{
public:
    TempSensor(AnalogMux* mux, uint8_t muxSel):
        AnalogSensor(mux, muxSel)
    {}

    TempSensor(uint8_t pin):
        AnalogSensor(pin)
    {}

    float ReadTempC();
    float ReadTempF();
};

const float IR_THRESH_DEFAULT = 2.5; // Default threshold of IR sensor

// Class used to obtain readings from HC-SR501 IR sensor device
class IrSensor : public AnalogSensor
{
public:
    IrSensor(AnalogMux* mux, uint8_t muxSel, float threshold = IR_THRESH_DEFAULT):
        AnalogSensor(mux, muxSel),
        threshold(threshold)
    {}

    IrSensor(uint8_t pin, float threshold = IR_THRESH_DEFAULT):
        AnalogSensor(pin),
        threshold(threshold)
    {}

    bool IsHumanPresent();

private:
    float threshold;
};

// Default voltage divider resistance used with LightSensor
const float LIGHT_SENSOR_DIV_DEFAULT = 10000; 

// Class used to obtain reading from photoresistor
class LightSensor : public AnalogSensor
{
public:
   LightSensor (AnalogMux* mux, uint8_t muxSel, float dividerOhms = LIGHT_SENSOR_DIV_DEFAULT):
        AnalogSensor(mux, muxSel),
        dividerOhms(dividerOhms)
    {}

    LightSensor(uint8_t pin, float dividerOhms = LIGHT_SENSOR_DIV_DEFAULT):
        AnalogSensor(pin),
        dividerOhms(dividerOhms)
    {}

    float ReadOhms();

    float ReadLux();

public:
    float dividerOhms;
};

class WindSensor
{
public:
    WindSensor(AnalogMux* mux, uint8_t rvMuxSel, uint8_t tmpMuxSel);
    WindSensor(uint8_t rvPin, uint8_t tmpPin);

    float ReadMph();
    float ReadRv();
    float ReadTmp();

private:
    uint8_t rvPin;
    uint8_t tmpPin;

    AnalogMux* mux;
    uint8_t rvMuxSel;
    uint8_t tmpMuxSel;
};

// Controls a vent damper.
class VentDamper
{
public:
    VentDamper(uint8_t pin);

    // Returns true if open, false otherwise.
    bool IsOpen();

    void Open();

    void Close();
};

// Controls a door.
class Door
{
    Door(uint8_t pin);

    // Returns true if open, false otherwise.
    bool IsOpen();

    void Open();

    void Close();
};

// Controls drapes.
class Drapes
{
    Drapes(uint8_t pin);

    // Returns true if open, false otherwise.
    bool IsOpen();

    void Open();

    void Close();
};



#endif
