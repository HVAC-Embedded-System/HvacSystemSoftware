#if !defined PERIPHERALS_h
#define PERIPHERALS_h

#include <stdint.h>

// Class used to control analog mux that expands the amount
// of analog inputs the system can use.
class AnalogMux
{
public:
    // Initialize with pin to read for inputs and each select pin.
    AnalogMux(uint8_t analogPin, uint8_t sel0, uint8_t sel1, uint8_t sel2);
    void SetSelect(uint8_t select);
    int ReadAnalogPin();
private:
    uint8_t analogPin;
    uint8_t sel0;
    uint8_t sel1;
    uint8_t sel2;
};

// Class used to obtain measurements from analog signals.
class AnalogSensor
{
public:
    // If analog pin is muxed, a pointer to the mux object is required.
    AnalogSensor(AnalogMux* mux, uint8_t muxSel);

    // If analog pin is not muxed, just a pin number is required.
    AnalogSensor(uint8_t pin);

    int Read();

private:
    uint8_t pin;

    AnalogMux* mux;
    uint8_t muxSel;
};

// Controls the inputs of Modern Device wind sensor.
// Based on example Arduino code: https://github.com/moderndevice/Wind_Sensor
const float ZERO_WIND_ADJUSTMENT = 0.2;

class WindSensor
{
public:
    WindSensor(AnalogMux* mux, uint8_t rvMuxSel, uint8_t tmpMuxSel);
    WindSensor(uint8_t rvPin, uint8_t tmpPin);

    float ReadMph();

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
