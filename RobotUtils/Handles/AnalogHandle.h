/**
 * @file AnalogHandle.h
 * @author Jiucheng Zang
 * @brief Analog Handle
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_ANALOG_HANDLE_H_
#define _INCLUDE_ROU_ANALOG_HANDLE_H_

#include "../Handle.h"
#include <CrcLib.h>

namespace rou
{

/**
 * @brief Analog Handle class
 *
 * @extends Handle class
 */
class AnalogHandle : public Handle
{
public:
	/**
	 * @brief Construct a new Analog Handle object
	 *
	 * @param pin pin be used in this handle
	 */
	AnalogHandle(uint8_t pin)
	{
		m_pin = pin;
	}

	/**
	 * @brief The value of the AI mentioned as the function’s argument. Value between(0 to 1023)
	 *
	 * @return int
	 */
	int getValue()
	{
		return Crc::CrcLib::GetAnalogInput(m_pin);
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

private:
	uint8_t m_pin;
};

} // namespace rou

#endif // _INCLUDE_ROU_ANALOG_HANDLE_H_
