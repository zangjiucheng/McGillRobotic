/**
 * @file HolonomicDriveModule.h
 * @author Diana Riscanu
 * @brief HolonomicDriveModule class
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_HOLONOMIC_DRIVE_MODULE_H_
#define _INCLUDE_ROU_HOLONOMIC_DRIVE_MODULE_H_

#include "../Handles/PwmHandle.h"
#include <CrcLib.h>

namespace rou
{

class HolonomicDriveModule
{
public:
	HolonomicDriveModule(PwmHandle* frontLeftMotor, PwmHandle* backLeftMotor,
		PwmHandle* frontRightMotor, PwmHandle* backRightMotor)
	{
		m_frontLeftMotor	= frontLeftMotor;
		m_backLeftMotor		= backLeftMotor;
		m_frontRightMotor	= frontRightMotor;
		m_backRightMotor	= backRightMotor;
	}

	virtual void move(int8_t forwardChannel, int8_t yawChannel, int8_t strafeChannel)
	{
		if (m_frontLeftMotor->isAvailable() && m_backLeftMotor->isAvailable()
			&& m_frontRightMotor->isAvailable() && m_backRightMotor->isAvailable())
		{
			m_frontLeftMotor->use();
			m_backLeftMotor->use();
			m_frontRightMotor->use();
			m_backLeftMotor->use();

			Crc::CrcLib::MoveHolonomic(forwardChannel, strafeChannel, yawChannel,
				m_frontLeftMotor->getPin(), m_backLeftMotor->getPin(),
				m_frontRightMotor->getPin(), m_backRightMotor->getPin());
		}
	}

private:
	PwmHandle* m_frontLeftMotor;
	PwmHandle* m_backLeftMotor;
	PwmHandle* m_frontRightMotor;
	PwmHandle* m_backRightMotor;
};

} //namespace rou

#endif // _INCLUDE_ROU_HOLONOMIC_DRIVE_MODULE_H_
