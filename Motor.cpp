//
// Created by Brendan Berg on 2019-04-20.
//

#include <stdlib.h>

#include <periph/Motor.hpp>


Motor::Motor (volatile uint8_t* directionPinAPort, uint8_t directionPinABit,
              volatile uint8_t* directionPinBPort, uint8_t directionPinBBit,
              volatile uint8_t* encoderPinAPin, uint8_t encoderPinABit,
              volatile uint8_t* encoderPinBPin, uint8_t encoderPinBBit,
              volatile uint8_t* velocityPinPort, uint8_t velocityPinBit,
              Timer* timer, uint8_t timerOCR)
    : m_DirectionPinA(directionPinAPort, directionPinABit),
    m_DirectionPinB(directionPinBPort, directionPinBBit),
    m_EncoderPinA(encoderPinAPin, encoderPinABit),
    m_EncoderPinB(encoderPinBPin, encoderPinBBit),
    m_VelocityPin(velocityPinPort, velocityPinBit, timer, timerOCR)
{
    m_DirectionPinA.Disable();
    m_DirectionPinB.Disable();

    m_EncoderSteps = 0;
    m_LastEncoderPinAState = m_EncoderPinA.GetState();
}


void Motor::SetVelocity (int16_t velocity)
{
    bool forward = (velocity > 0);

    m_DirectionPinA.Set(forward);
    m_DirectionPinB.Set(!forward);

    m_VelocityPin.SetValue(static_cast<uint8_t>(abs(velocity)));
}


void Motor::Update ()
{
    bool encoderPinAState = m_EncoderPinA.GetState();
    bool encoderPinBState = m_EncoderPinB.GetState();

    if (encoderPinAState != m_LastEncoderPinAState)
    {
        m_EncoderSteps += ((encoderPinAState == encoderPinBState) ? -1 : +1);
    }

    m_LastEncoderPinAState = encoderPinAState;
}


int64_t Motor::GetEncoderSteps ()
{
    return m_EncoderSteps;
}
