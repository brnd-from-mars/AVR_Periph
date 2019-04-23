//
// Created by Brendan Berg on 2019-04-23.
//

#include <periph/IRRangeFinder.hpp>


IRRangeFinder::IRRangeFinder (uint8_t channel,
                              AnalogInputController& analogInputController)
    : m_Pin(channel, 4)
{
    analogInputController.RegisterAnalogPin(&m_Pin);
}


uint8_t IRRangeFinder::GetRawDistance ()
{
    return m_Pin.GetValue();
}
