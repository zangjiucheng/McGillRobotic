/**
 * @file ModeManager.h
 * @author Elisa Moscato
 * @brief Allows to switch between different modes
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_MODE_MANAGER_H_
#define _INCLUDE_ROU_MODE_MANAGER_H_

#include "Mode.h"

namespace rou
{

class ModeManager
{
public:
	void update(float dt)
	{
		if (m_currentMode)
		{
			m_currentMode->update(dt);
		}

		if (m_nextMode)
		{
			if (m_currentMode)
			{
				m_currentMode->unload();
			}

			m_currentMode = m_nextMode;
			m_currentMode->load();
			m_nextMode = nullptr;
		}
	}

	void changeMode(Mode* nextMode)
	{
		m_nextMode = nextMode;
	}

private:
	Mode* m_nextMode	= nullptr;
	Mode* m_currentMode	= nullptr;
};

} // namespace rou

#endif // _INCLUDE_ROU_MODE_MANAGER_H_
