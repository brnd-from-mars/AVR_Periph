//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_ALPHA_SERVO_HPP
#define ATAR_ALPHA_SERVO_HPP

#include "mcu/io/DigitalOutputPin.hpp"
#include "mcu/timer/Timer.hpp"



class Servo : public Timer
{
public:

    explicit Servo (uint8_t timerID, uint8_t ocr,
                    volatile uint8_t* port, uint8_t bit);

    void SetPosition (uint8_t position);


protected:

    void CompareMatchInterrupt (uint8_t ocr) override;


private:

    static TimerModeConfig GetModeConfig(uint8_t timerID, uint16_t prescaler);

    uint8_t m_OCR;

    DigitalOutputPin m_Pin;

    TimerModeConfig m_ModeCfgLow;

    TimerModeConfig m_ModeCfgHigh;

    bool m_WaveState;

    uint8_t m_Position;

    uint8_t m_OCRB;


};


#endif //ATAR_ALPHA_SERVO_HPP
