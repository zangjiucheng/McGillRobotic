/**
 * @file DigitalOutputModule.h
 * @author Diana Riscanu
 * @brief DigitalOutputModule class
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_DIGITAL_OUTPUT_MODULE_H_
#define _INCLUDE_ROU_DIGITAL_OUTPUT_MODULE_H_

#include "../Handles/DigitalOutputHandle.h"
#include <CrcLib.h>

namespace rou
{

class DigitalOutputModule
{
public:
	DigitalOutputModule(DigitalOutputHandle* digitalOuptutHandle)
	{
		m_digitalOutputHandle = digitalOuptutHandle;
	}

	void setStatus(bool isHigh)
	{
		if (m_digitalOutputHandle->use())
		{
			Crc::CrcLib::SetDigitalOutput(m_digitalOutputHandle->getPin(), (isHigh ? HIGH : LOW));
		}
	}

private:
	DigitalOutputHandle* m_digitalOutputHandle;
};

} // namespace rou

#endif // _INCLUDE_ROU_DIGITAL_OUTPUT_MODULE_H_
