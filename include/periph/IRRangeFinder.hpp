//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_ALPHA_IRRANGEFINDER_HPP
#define ATAR_ALPHA_IRRANGEFINDER_HPP

#include <mcu/io/AnalogInputPin.hpp>
#include <mcu/io/AnalogInputController.hpp>


class IRRangeFinder
{
public:

    IRRangeFinder (uint8_t channel,
                  AnalogInputController& analogInputController);

    uint8_t GetRawDistance ();


private:

    AnalogInputPin m_Pin;


};


#endif //ATAR_ALPHA_IRRANGEFINDER_HPP
