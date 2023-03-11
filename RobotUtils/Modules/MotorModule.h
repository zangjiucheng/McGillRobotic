/**
 * @file MotorModule.h
 * @author Diana Riscanu
 * @brief MotorModule class
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_MOTOR_MODULE_H_
#define _INCLUDE_ROU_MOTOR_MODULE_H_

#include "../Handles/PwmHandle.h"
#include <CrcLib.h>

namespace rou
{

class MotorModule
{
public:
	MotorModule(PwmHandle* motorHandle)
	{
		m_motorHandle = motorHandle;
	}

	void setSpeed(int8_t motorSpeed)
	{
		Crc::CrcLib::SetPwmOutput(m_motorHandle->getPin(), motorSpeed);
	}

private:
	PwmHandle* m_motorHandle;
};

} // namespace rou

#endif // _INCLUDE_ROU_MOTOR_MODULE_H_
