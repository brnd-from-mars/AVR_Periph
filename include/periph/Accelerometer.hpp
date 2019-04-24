//
// Created by Brendan Berg on 2019-04-21.
//

#ifndef ATAR_CENTRAL_ACCELEROMTER_HPP
#define ATAR_CENTRAL_ACCELEROMTER_HPP

#include <mcu/io/AnalogInputPin.hpp>
#include <mcu/io/AnalogInputController.hpp>


class Accelerometer
{
public:

    explicit Accelerometer (AnalogInputController& analogInputController);

    void RegisterAxis (uint8_t channel, int16_t initialAccel);

    // TODO: save in EEPROM
    void Calibrate ();

    int16_t GetAcceleration (uint8_t axis);

    double GetFloatAcceleration (uint8_t axis);

    int8_t GetClimbAngle (uint8_t downAxis, uint8_t fwdAxis);


private:

    AnalogInputController& m_AnalogInputController;

    AnalogInputPin m_Pins[3];

    uint8_t m_RegisteredPins;

    uint8_t m_InitialRawValue[3] = {0};

    int16_t m_InitialAcceleration[3] = {0};

    int16_t m_Sensitivity;

    int16_t m_Bias;

    bool CalculateSensitivity (uint8_t axis1, uint8_t axis2,
                               int16_t& sensitivity);


};


#endif //ATAR_CENTRAL_ACCELEROMTER_HPP
