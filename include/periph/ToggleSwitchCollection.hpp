//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_ALPHA_TOGGLESWITCHCOLLECTION_HPP
#define ATAR_ALPHA_TOGGLESWITCHCOLLECTION_HPP

#include "mcu/io/DigitalInputPin.hpp"


template <int N>
class ToggleSwitchCollection
{
public:

    ToggleSwitchCollection ();

    void RegisterPin (volatile uint8_t* pin, uint8_t bit);

    uint8_t GetStates ();


private:

    DigitalInputPin m_Pins[N];

    uint8_t m_LastStates;

    uint8_t m_RegisteredPins;


};


#endif //ATAR_ALPHA_TOGGLESWITCHCOLLECTION_HPP
