/**
 * @file Mode.h
 * @author Elisa Moscato
 * @brief The base of modes
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_MODE_H_
#define _INCLUDE_ROU_MODE_H_

#include <ArduinoExtra.h>
#include "Controller.h"

namespace rou
{

class ModeManager;

class Mode
{
public:
	virtual void update(float dt) = 0;

	virtual void load()		= 0;
	virtual void unload()	= 0;

protected:
	Controller			m_controller;
	static ModeManager&	ModeManager;
};

} // namespace rou

#endif // _INCLUDE_ROU_MODE_H_
