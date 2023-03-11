/**
 * @file RobotUtils.h
 * @author Eliot Fondere
 * @brief Main header file for Vanier Robotics' RobotUtils library
 * 
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#ifndef _INCLUDE_ROU_ROBOT_UTILS_H_
#define _INCLUDE_ROU_ROBOT_UTILS_H_

// Check if the correct board is selected
#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
#error please select the proper board for the CrcDuino (Mega or Mega2560)
#endif // __AVR_ATmega1280__ or __AVR_ATmega2560__

#include "RobotUtils/Controller.h"
#include "RobotUtils/Handle.h"
#include "RobotUtils/HandleManager.h"
#include "RobotUtils/Handles.h"
#include "RobotUtils/Mode.h"
#include "RobotUtils/ModeManager.h"
#include "RobotUtils/Modules.h"

#endif // _INCLUDE_ROU_ROBOT_UTILS_H_
