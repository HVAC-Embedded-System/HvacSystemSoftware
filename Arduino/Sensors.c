#include "Sensors.h"

void AnalogMux::SetSelect(uint8_t select)
{
}

AnalogSensor::AnalogSensor(uint8_t pin, AnalogMux* mux, uint8_t muxSel)
{
}

uint8_t AnalogSensor::Update()
{
}

WindSensor::WindSensor(uint8_t rvPin,  AnalogMux* rvMux,  uint8_t rvMuxSel,
                       uint8_t tmpPin, AnalogMux* tmpMux, uint8_t tmpMuxSel)
{
}

uint8_t WindSensor::Update()
{
}

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