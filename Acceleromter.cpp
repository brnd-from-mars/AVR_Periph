//
// Created by Brendan Berg on 2019-04-21.
//

#include <periph/Acceleromter.hpp>


Acceleromter::Acceleromter (uint8_t channelX,
                            uint8_t channelY,
                            uint8_t channelZ,
                            AnalogInputController& analogInputController)
{
    RegisterAnalogPin(m_PinX, channelX, analogInputController);
    RegisterAnalogPin(m_PinY, channelY, analogInputController);
    RegisterAnalogPin(m_PinZ, channelZ, analogInputController);
}


void Acceleromter::RegisterAnalogPin (AnalogInputPin& pin, uint8_t channel,
    AnalogInputController& analogInputController)
{
    if (channel != 0xff)
    {
        pin = AnalogInputPin(channel, 16);
        analogInputController.RegisterAnalogPin(&pin);
    }
}
