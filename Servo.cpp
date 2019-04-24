//
// Created by Brendan Berg on 2019-04-23.
//

#include <periph/Servo.hpp>


Servo::Servo (uint8_t timerID, uint8_t ocr, volatile uint8_t* port, uint8_t bit)
    : Timer(GetModeConfig(timerID, 0x0400), timerID),
    m_ModeCfgLow(GetModeConfig(timerID, 0x0400)),
    m_ModeCfgHigh(GetModeConfig(timerID, 0x0080)),
    m_OCR(ocr), m_Pin(port, bit), m_WaveState(false), m_Position(0), m_OCRB(0)
{
    instancePtr[timerID] = this;

    TimerCompareMatchConfig comCfg(
        m_OCR, TimerCompareMatchConfig::compareMatchModeToggle);

    SetCompareMatchMode(comCfg);
    EnableCompareMatchInterrupt(0x00);
    SetOutputCompareRegister(0x00ff, 0x00);
    SetOutputCompareRegister(0x00ff, m_OCR);
}


void Servo::SetPosition (uint8_t position)
{
    m_Position = position;
    uint16_t t = position * 0x6e / 0xff;
    m_OCRB = t + 0x84;
}


void Servo::CompareMatchInterrupt (uint8_t ocr)
{
    if (ocr != 0x00)
    {
        return;
    }

    if (m_WaveState)
    {
        SetOutputCompareRegister(0x00ff, m_OCR);
        SetClockSource(m_ModeCfgLow);
        Enable();
    }
    else
    {
        SetOutputCompareRegister(m_OCRB, m_OCR);
        SetClockSource(m_ModeCfgHigh);
        Enable();
    }

    m_WaveState = !m_WaveState;
}


TimerModeConfig Servo::GetModeConfig (uint8_t timerID, uint16_t prescaler)
{
    TimerRegisterConfig rgtrCfg(timerID);
    TimerModeConfig modeCfg = {};

    if (rgtrCfg.twoBytes)
    {
        modeCfg.waveform = TimerModeConfig::waveform16Ctc;
    }
    else
    {
        modeCfg.waveform = TimerModeConfig::waveform8Ctc;
    }

    switch (prescaler)
    {
        default:
        case 0x0001:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs1;
            break;
        case 0x0008:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs8;
            break;
#if defined(__AVR_ATmega328P__)
        case 0x0020:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs32;
            break;
#endif
        case 0x0040:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs64;
            break;
#if defined(__AVR_ATmega328P__)
        case 0x0080:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs128;
            break;
#endif
        case 0x0100:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs256;
            break;
        case 0x0400:
            modeCfg.clockSource = TimerModeConfig::clockSourcePs1024;
            break;
    }

    return modeCfg;
}
