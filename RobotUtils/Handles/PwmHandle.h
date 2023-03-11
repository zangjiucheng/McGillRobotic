/**
 * @file PwmHandle.h
 * @author Jiucheng Zang
 * @brief Pwm Handle class
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_PWM_HANDLE_H_
#define _INCLUDE_ROU_PWM_HANDLE_H_

#include "../Handle.h"
#include <CrcLib.h>

namespace rou
{

/**
 * @brief Pwm Handle class
 *
 * @extends Handle class
 */
class PwmHandle : public Handle
{
public:
	/**
	 * @brief Construct a new PwmHandle object
	 *
	 * @param pin pin be used in this handle
	 * @param minPulseWidth The minimum pulse width, in microseconds
	 * @param maxPulseWidth The maximum pulse width, in microseconds
	 * @param reverse Whether or not to invert the rotation direction of the servo
	 */
	PwmHandle(uint8_t pin, int minPulseWidth = 1000, int maxPulseWidth = 2000, bool isReversed = false)
	{
		m_pin			= pin;
		m_minPulseWidth	= minPulseWidth;
		m_maxPulseWidth	= maxPulseWidth;
		m_isReversed	= isReversed;
	}

	PwmHandle(uint8_t pin, bool isReversed)
	{
		m_pin			= pin;
		m_minPulseWidth	= 1000;
		m_maxPulseWidth	= 2000;
		m_isReversed	= isReversed;
	}

	/**
	 * @brief Return the pin be used in this handle
	 *
	 * @return uint8_t m_pin
	 */
	uint8_t getPin()
	{
		return m_pin;
	}

protected:
	/**
	 * @brief Initialize the Pwm Output
	 *
	 */
	void setup() override
	{
		Crc::CrcLib::InitializePwmOutput(m_pin, m_minPulseWidth, m_maxPulseWidth, m_isReversed);
	}

private:
	uint8_t	m_pin;
	int		m_minPulseWidth;
	int		m_maxPulseWidth;
	bool	m_isReversed;
};

} // namespace rou

#endif // _INCLUDE_ROU_PWM_HANDLE_H_
