//
// Created by Brendan Berg on 2019-04-21.
//

#include <periph/Accelerometer.hpp>
#include <math.h>


Accelerometer::Accelerometer (AnalogInputController& analogInputController)
    : m_AnalogInputController(analogInputController), m_RegisteredPins(0),
    m_Sensitivity(0x12), m_Bias(0x54)
{ }


void Accelerometer::RegisterAxis (uint8_t channel, int16_t initialAccel)
{
    m_Pins[m_RegisteredPins] = AnalogInputPin(channel, 0x10);
    m_InitialAcceleration[m_RegisteredPins] = initialAccel;
    m_AnalogInputController.RegisterAnalogPin(&m_Pins[m_RegisteredPins]);
    ++m_RegisteredPins;
}


void Accelerometer::Calibrate ()
{
    for (uint8_t i = 0; i < m_RegisteredPins; ++i)
    {
        m_InitialRawValue[i] = m_Pins[i].GetValue();
    }

    int16_t sensitivity = 0x0000;
    uint8_t sensitivityValues = 0x00;
    for (uint8_t i = 0; i < m_RegisteredPins; ++i)
    {
        for (uint8_t j = (i + 1); j < m_RegisteredPins; ++j)
        {
            if (CalculateSensitivity(i, j, sensitivity))
            {
                ++sensitivityValues;
            }
        }
    }
    sensitivity = sensitivity / sensitivityValues;
    m_Sensitivity = sensitivity;

    int16_t bias = 0x0000;
    for (uint8_t i = 0; i < m_RegisteredPins; ++i)
    {
        bias += m_InitialRawValue[i] - static_cast<uint16_t>(
            sensitivity * m_InitialAcceleration[i] / 0xff);
    }
    bias = bias / m_RegisteredPins;
    m_Bias = bias;
}


int16_t Accelerometer::GetAcceleration (uint8_t axis)
{
    auto offset = m_Pins[axis].GetValue() - m_Bias;
    return 0xff * offset / m_Sensitivity;
}


double Accelerometer::GetFloatAcceleration (uint8_t axis)
{
    return static_cast<double>(GetAcceleration(axis)) /
        static_cast<double>(0xff);
}


int8_t Accelerometer::GetClimbAngle (uint8_t downAxis, uint8_t fwdAxis)
{
    double total = sqrt(square(GetFloatAcceleration(downAxis)) +
        square(GetFloatAcceleration(fwdAxis)));
    double accelDown = GetFloatAcceleration(downAxis) / total;
    double accelFwd = GetFloatAcceleration(fwdAxis) / total;

    accelDown = fmin(accelDown, 1.0);
    double falpha = acos(accelDown) / M_1_PI;

    auto alpha = static_cast<int8_t>(0x7f * falpha) * ((accelFwd < 0) ? -1 : 1);

    return alpha;
}


bool Accelerometer::CalculateSensitivity (uint8_t axis1, uint8_t axis2,
                                          int16_t& sensitivity)
{
    if (m_InitialAcceleration[axis1] == m_InitialAcceleration[axis2])
    {
        return false;
    }

    auto dRaw = m_InitialRawValue[axis1] - m_InitialRawValue[axis2];
    auto dAccel = m_InitialAcceleration[axis1] - m_InitialAcceleration[axis2];

    sensitivity += 0xff * dRaw / dAccel;

    return true;
}
