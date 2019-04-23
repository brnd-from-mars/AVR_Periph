//
// Created by Brendan Berg on 2019-04-23.
//

#include <periph/ToggleSwitchCollection.hpp>


template<int N>
ToggleSwitchCollection<N>::ToggleSwitchCollection ()
: m_RegisteredPins(0), m_LastStates(0)
{ }


template<int N>
void ToggleSwitchCollection<N>::RegisterPin (volatile uint8_t* pin, uint8_t bit)
{
    m_Pins[m_RegisteredPins] = DigitalInputPin(pin, bit);
    ++m_RegisteredPins;

    if (m_RegisteredPins == N)
    {
        GetStates();
    }
}


template<int N>
uint8_t ToggleSwitchCollection<N>::GetStates ()
{
    uint8_t states = 0;

    for (uint8_t i = 0; i < m_RegisteredPins; ++i)
    {
        if (m_Pins[i].GetState())
        {
            states |= (1 << (2 * i));
        }
    }

    uint8_t result = 0;

    result |= states;
    result |= ((states ^ m_LastStates) << 1); // changed

    m_LastStates = states;

    return result;
}


template class ToggleSwitchCollection<1>;
template class ToggleSwitchCollection<2>;
template class ToggleSwitchCollection<3>;
template class ToggleSwitchCollection<4>;
