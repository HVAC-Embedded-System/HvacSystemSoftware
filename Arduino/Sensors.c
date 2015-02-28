#include "Sensors.h"

/* AnalogMux */
void AnalogMux::AnalogMux(uint8_t analogPin, uint8_t sel0, uint8_t sel1, uint8_t sel2):
    this->analogPin(analogPin),
    this->sel0(sel0),
    this->sel1(sel1),
    this->sel2(sel2)
{
}

void AnalogMux::SetSelect(uint8_t select){
    bool sel0State;
    bool sel1State;
    bool sel2State;

    sel0State = select & 0x01 ? HIGH : LOW;
    sel1State = select & 0x02 ? HIGH : LOW;
    sel2State = select & 0x04 ? HIGH : LOW;

    digitalWrite(sel0, sel0State);
    digitalWrite(sel1, sel1State);
    digitalWrite(sel2, sel2State);
}

int AnalogMux::ReadAnalogPin(){
    return analogRead(analogPin);
}

/* AnalogSensor */
AnalogSensor::AnalogSensor(AnalogMux* mux, uint8_t muxSel):
    this->mux(mux),
    this->muxSel(muxSel)
{}

AnalogSensor::AnalogSensor(uint8_t pin):
    this->pin(pin),
    this->mux(0)
{}

int AnalogSensor::Read()
{
    int reading;

    if (mux != 0)
    {
        mux->SetSelect(muxSel);
        reading = mux->ReadAnalogPin();
    }
    else
    {
        reading = analogRead(pin);
    }

    return reading;
}

/* WindSensor */
WindSensor::WindSensor(AnalogMux* mux, uint8_t rvMuxSel, uint8_t tmpMuxSel):
    this->mux(mux),
    this->rvMuxSel(rvMuxSel),
    this->tmpMuxSel(tmpMuxSel)
{}

WindSensor::WindSensor(uint8_t rvPin, uint8_t tmpPin):
    this->rvPin(rvPin),
    this->tmpPin(tmpPin),
    this->mux(0)
{}

float WindSensor::ReadMph()
{
    float rvReading;
    float tmpReading;
    float rvWindVolts;
    float tempCTimes100;
    float zeroWindReference;
    float zeroWindVolts;
    float windSpeedMph;

    if (mux != 0)
    {
        mux->SetSelect(rvMuxSel);
        rvMuxSel = (float) (mux->ReadAnalogPin());

        mux->SetSelect(tmpMuxSel);
        tmpReading = (float) (mux->ReadAnalogPin());
    }
    else
    {
        rvReading = (float) (analogRead(rvPin));
        tmpReading = (float) (analogRead(tmpPin));
    }

    // Calculate wind speed from sensor readings.
    // Equations taken from Modern Device Arduino code: https://github.com/moderndevice/Wind_Sensor
    zeroWindReference = (-0.0006 * tmpReading * tmpReading) + (1.0727 * tmpReading) + 47.172;
    zeroWindVolts = (0.0048828125 * zeroWindReference) - ZERO_WIND_ADJUSTMENT;

    rvWindVolts = 0.0048828125 * rvReading;

    windSpeedMph = pow(((rvWindVolts - zeroWindVolts) / .23), 2.7265);
}

/* VentDamper */
VentDamper::VentDamper(uint8_t pin)
{
}

bool VentDamper::IsOpen()
{
}

void VentDamper::Open()
{
}

void VentDamper::Close()
{
}

/* Door */
Door::Door(uint8_t pin)
{
}

bool Door::IsOpen()
{
}

void Door::Open()
{
}

void Door::Close()
{
}

/* Drapes */
Drapes::Drapes(uint8_t pin)
{
}

bool Drapes::IsOpen()
{
}

void Drapes::Open()
{
}

void Drapes::Close()
{
}
