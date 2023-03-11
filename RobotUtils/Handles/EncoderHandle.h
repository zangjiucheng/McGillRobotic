/**
 * @file EncodereHandle.h
 * @author Jiucheng Zang
 * @brief Encoder Handle
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 *
 */

#ifndef _INCLUDE_ROU_ENCODER_HANDLE_H_
#define _INCLUDE_ROU_ENCODER_HANDLE_H_

#include "../Handle.h"
#include <CrcLib.h>
#include <Encoder.h>

namespace rou
{

/**
 * @brief Encoder Handle class
 *
 * @extends Handle class
 */
class EncoderHandle : public Handle
{
public:
    /**
     * @brief Construct a new Encoder Handle object with one interrupt
     *
     * @param PinA Singal A
     * @param PinB SIngle B
     */
    EncoderHandle(int8_t pinA, int8_t pinB)
	: m_encoder(pinA, pinB)
    {
        m_pinA = pinA;
        m_pinB = pinB;
    }

    /**
     * @brief Get the Position object
     *
     * @return long int
     */
    int32_t getPosition()
	{
		m_encoder.read();
    }

    /**
     * @brief Get the A pin
     *
     * @return uint8_t
     */
    uint8_t getPinA()
	{
        return m_pinA;
	}

	uint8_t getPinB()
	{
		return m_pinB;
	}

private:
    Encoder m_encoder;
    int8_t m_pinA;
    int8_t m_pinB;
};

} // namespace rou

#endif // _INCLUDE_ROU_ENCODER_HANDLE_H_
