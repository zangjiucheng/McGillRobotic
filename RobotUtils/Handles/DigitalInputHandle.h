/**
 * @file DigitalInputHandle.h
 * @author Jiucheng Zang
 * @brief Digital Input Handle
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_DIGITAL_INPUT_HANDLE_H_
#define _INCLUDE_ROU_DIGITAL_INPUT_HANDLE_H_

#include "../Handle.h"
#include <CrcLib.h>

namespace rou
{

/**
 * @brief Digital Input Handle class
 *
 */
class DigitalInputHandle : public Handle
{
public:
	/**
	 * @brief Construct a new Digital Input Handle object
	 *
	 * @param pin pin be used in this handle
	 */
	DigitalInputHandle(uint8_t pin)
	{
		m_pin = pin;
	}

	/**
	 * @brief Check if Digitial Input in HIGH mode (True -> HIGH, False -> LOW)
	 *
	 * @return bool
	 */
	bool getValue()
	{
		return (Crc::CrcLib::GetDigitalInput(m_pin) == HIGH);
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
	 * @brief Set the pin mode
	 * 
	 */
	void setup() override
	{
		Crc::CrcLib::SetDigitalPinMode(m_pin, INPUT);
	}

private:
	uint8_t m_pin;
};

} // namespace rou

#endif // _INCLUDE_ROU_DIGITAL_INPUT_HANDLE_H_
