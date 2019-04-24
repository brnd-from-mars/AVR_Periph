//
// Created by Brendan Berg on 2019-04-21.
//

#include <periph/LightEmittingDiode.hpp>


template<int N>
LightEmittingDiode<N>::LightEmittingDiode ()
    : m_RegisteredPins(0)
{ }


template<int N>
void LightEmittingDiode<N>::RegisterPin (volatile uint8_t* port, uint8_t bit)
{
    m_Pins[m_RegisteredPins] = DigitalOutputPin(port, bit);
    ++m_RegisteredPins;
}


template<int N>
void LightEmittingDiode<N>::Enable (uint8_t pin)
{
    m_Pins[pin].Enable();
}


template<int N>
void LightEmittingDiode<N>::Disable (uint8_t pin)
{
    m_Pins[pin].Disable();
}


template<int N>
void LightEmittingDiode<N>::Flip (uint8_t pin)
{
    m_Pins[pin].Flip();
}


template<int N>
void LightEmittingDiode<N>::SetAll (uint8_t states)
{
    for (uint8_t i = 0; i < m_RegisteredPins; ++i)
    {
        m_Pins[i].Set((states >> i) & 1);
    }
}


template class LightEmittingDiode<1>;
template class LightEmittingDiode<2>;
template class LightEmittingDiode<3>;