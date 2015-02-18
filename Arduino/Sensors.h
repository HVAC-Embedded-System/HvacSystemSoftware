#if !defined SENSORS_h
#define SENSORS_h

// Class used to control analog mux that expands the amount
// of analog inputs the system can use.
class AnalogMux
{
public:
    void SetSelect(uint8_t select);
private:
    uint8_t analogPin;
    uint8_t selPin[3];
};

// Class used to obtain measurements from analog signals.
// Update() must be run many times per second at a fairly
// constant rate because it uses a first order lag filter to
// minimize jitter.
class AnalogSensor
{
public:
    // If analog pin is muxed, a pointer to the mux object is required.
    // If analog pin is not muxed, give a null pointer.
    AnalogSensor(uint8_t pin, AnalogMux* mux, uint8_t muxSel);

    // Obtain and return new filtered sample value.
    uint8_t Update();

private:
    uint8_t pin;
    AnalogMux* mux;
    uint8_t muxSel;

    uint8_t last;
    unsigned long lastUpdateTimeUs;

};

class WindSensor
{
public:
    WindSensor(uint8_t rvPin,  AnalogMux* rvMux,  uint8_t rvMuxSel,
               uint8_t tmpPin, AnalogMux* tmpMux, uint8_t tmpMuxSel);

    // Obtain and return new filtered sample value.
    uint8_t Update();
}

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
