//
// Created by Brendan Berg on 2019-04-21.
//

#ifndef ATAR_CENTRAL_ACCELEROMTER_HPP
#define ATAR_CENTRAL_ACCELEROMTER_HPP

#include <mcu/io/AnalogInputPin.hpp>
#include <mcu/io/AnalogInputController.hpp>


class Acceleromter
{
public:

    Acceleromter(uint8_t channelX, uint8_t channelY, uint8_t channelZ,
                 AnalogInputController& analogInputController);


private:

    AnalogInputPin m_PinX;

    AnalogInputPin m_PinY;

    AnalogInputPin m_PinZ;

    void RegisterAnalogPin(AnalogInputPin& pin, uint8_t channel,
                           AnalogInputController& analogInputController);


};


#endif //ATAR_CENTRAL_ACCELEROMTER_HPP
