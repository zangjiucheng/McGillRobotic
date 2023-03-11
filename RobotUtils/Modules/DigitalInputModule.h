/**
 * @file DigitalInputModule.h
 * @author Diana Riscanu
 * @brief DigitalInputModule class
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_DIGITAL_INPUT_MODULE_H_
#define _INCLUDE_ROU_DIGITAL_INPUT_MODULE_H_

#include "../Handles/DigitalInputHandle.h"
#include <CrcLib.h>

namespace rou
{

class DigitalInputModule
{
public:
	DigitalInputModule(DigitalInputHandle* digitalInputHandle)
	{
		m_digitalInputHandle = digitalInputHandle;
	}

	bool getStatus()
	{
		return (Crc::CrcLib::GetDigitalInput(m_digitalInputHandle->getPin()) == HIGH);
	}

private:
	DigitalInputHandle* m_digitalInputHandle;
};

} // namespace rou

#endif // _INCLUDE_ROU_DIGITAL_INPUT_MODULE_H_
