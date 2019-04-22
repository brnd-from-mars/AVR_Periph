//
// Created by Brendan Berg on 2019-04-21.
//

#ifndef ATAR_CENTRAL_LIGHTEMITTINGDIODE_HPP
#define ATAR_CENTRAL_LIGHTEMITTINGDIODE_HPP

#include <stdint.h>

#include <mcu/io/DigitalOutputPin.hpp>


template <int N>
class LightEmittingDiode
{
public:

    LightEmittingDiode ();

    void RegisterPin (volatile uint8_t* port, uint8_t bit);

    void Enable (uint8_t pin = 0);

    void Disable (uint8_t pin = 0);

    void Flip (uint8_t pin = 0);


private:

    DigitalOutputPin m_Pins[N];

    uint8_t m_RegisteredPins;
    

};


typedef LightEmittingDiode<1> SingleColorLED;
typedef LightEmittingDiode<2> BiColorLED;
typedef LightEmittingDiode<3> TriColorLED;


#endif //ATAR_CENTRAL_LIGHTEMITTINGDIODE_HPP
