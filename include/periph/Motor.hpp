//
// Created by Brendan Berg on 2019-04-20.
//

#ifndef AVR_PERIPH_MOTOR_HPP
#define AVR_PERIPH_MOTOR_HPP

#include <stdint.h>

#include <mcu/io/AnalogOutputPin.hpp>
#include <mcu/io/DigitalOutputPin.hpp>
#include <mcu/io/DigitalInputPin.hpp>
#include <mcu/timer/TimerFastPWM.hpp>


class Motor
{
public:

    Motor (volatile uint8_t* directionPinAPort, uint8_t directionPinABit,
           volatile uint8_t* directionPinBPort, uint8_t directionPinBBit,
           volatile uint8_t* encoderPinAPin, uint8_t encoderPinABit,
           volatile uint8_t* encoderPinBPin, uint8_t encoderPinBBit,
           volatile uint8_t* velocityPinPort, uint8_t velocityPinBit,
           Timer* timer, uint8_t timerOCR);

    void SetVelocity (int16_t velocity);

    int16_t GetVelocity ();

    void Update ();

    int32_t GetEncoderSteps ();


private:

    DigitalOutputPin m_DirectionPinA;

    DigitalOutputPin m_DirectionPinB;

    DigitalInputPin m_EncoderPinA;

    DigitalInputPin m_EncoderPinB;

    AnalogOutputPin m_VelocityPin;

    bool m_LastEncoderPinAState;

    int32_t m_EncoderSteps;

    int16_t m_Velocity;


};


#endif //AVR_PERIPH_MOTOR_HPP
