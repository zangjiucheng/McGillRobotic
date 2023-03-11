/**
 * @file Controller.h
 * @author Gabriel Saberian
 * @brief Controller header file for Vanier Robotics' RobotUtils library, controls the robot by pressing
 * digital and analog buttons on a controller.
 *
 * @copyright Copyright (c) 2023 Vanier Robotics (MIT License)
 */

#include <ArduinoExtra.h>
#include <CrcLib.h>

#ifndef _INCLUDE_ROU_CONTROLLER_H_
#define _INCLUDE_ROU_CONTROLLER_H_

namespace rou
{

class Controller
{
	// Structure that contains the variables and fuctions for the digital binding
	struct DigitalBinding
	{
		Crc::BUTTON 				buttonID; //variable of type BUTTON (from CRC lib) that stores a specific button
		aex::Function<void(bool)>	callback; //pointer function used to do some action with a digital button
	};

	//Structure that contains the variables and fuctions for the toggle binding
	struct ToggleBinding
	{
		Crc::BUTTON					buttonID; //variable of type BUTTON (from CRC lib) that stores a specific button
		aex::Function<void(bool)>	callback; //pointer function used to do some action with a toggle action

		bool isToggled; //boolean variable that stores the state of the button (Toggled = true and not toggled = false)
		// boolean variable that stores the last value of a button and used to defined the isToggled value
		//(if lastValue = true, then the last button was pressed and if lastValue = false, then the last button wasn't pressed)
		bool lastValue;
	};

	//Structure that contains the variables and fuctions for the analog binding
	struct AnalogBinding
	{
		Crc::ANALOG 				analogID; //variable of type ANALOG (from CRC lib) that stores a specific button
		aex::Function<void(int8_t)>	callback; //pointer function used to do some action with an analog button
	};

	//Structure that contains the variables and fuctions for the digital sensor binding
	struct DigitalSensorBinding
	{
		uint8_t						pin; //variable of type uint8_t that stores the number of the pin on the crcDuino board change type
		aex::Function<void(bool)>	callback;
	};

	//Structure that contains the variables and fuctions for the analog sensor binding
	struct AnalogSensorBinding
	{
		uint8_t								pin; //variable of type uint8_t that stores the number of the pin on the crcDuino board change type
		aex::Function<void(unsigned int)>	callback;
	};

public:
	//callback functions (pointer functions) of the different structures
	//callback function for digital bindings
	void digitalBind(Crc::BUTTON buttonID, aex::Function<void(bool)> callback)
	{
		m_digitalBindings.pushBack({buttonID, callback});
	}

	//callback function for toggle bindings
	void toggleBind(Crc::BUTTON buttonID, aex::Function<void(bool)> callback)
	{
		m_toggleBindings.pushBack({buttonID, callback, false, false});
	}

	//callback function for analog bindings
	void analogBind(Crc::ANALOG analogID, aex::Function<void(int8_t)> callback)
	{
		m_analogBindings.pushBack({analogID, callback});
	}

	//callback function for digital sensor bindings
	void digitalSensorBind(uint8_t pin, aex::Function<void(bool)> callback)
	{
		m_digitalSensorBindings.pushBack({pin, callback});
	}

	//callback function for analog sensor binding
	void analogSensorBind(uint8_t pin, aex::Function<void(unsigned int)> callback)
	{
		m_analogSensorBindings.pushBack({pin, callback});
	}

	void update()
	{
		//For each frame, verify which button are pressed and call the corresponding methods
		//Digital Bindings verification
		for (int i = 0; i < m_digitalBindings.getSize(); i++)
		{
			m_digitalBindings[i].callback(
				Crc::CrcLib::ReadDigitalChannel(m_digitalBindings[i].buttonID));
		}

		//Analog Bindings verification
		for (int i = 0; i < m_analogBindings.getSize(); i++)
		{
			m_analogBindings[i].callback(
				Crc::CrcLib::ReadAnalogChannel(m_analogBindings[i].analogID));
		}

		//Toggle Bindings verification
		for (int i = 0; i < m_toggleBindings.getSize(); i++)
		{
			bool status = Crc::CrcLib::ReadDigitalChannel(m_toggleBindings[i].buttonID);
			if (m_toggleBindings[i].lastValue != status && status)
			{
				m_toggleBindings[i].isToggled != m_toggleBindings[i].isToggled;
				m_toggleBindings[i].callback(m_toggleBindings[i].isToggled);
			}

			m_toggleBindings[i].lastValue = status;
		}

		//Digital Sensor Bindings verification
		for (int i = 0; i < m_digitalSensorBindings.getSize(); i++)
		{
			m_digitalSensorBindings[i].callback(
				(Crc::CrcLib::GetDigitalInput(m_digitalSensorBindings[i].pin) == HIGH));
		}

		//Analog Sensor Bindings verification
		for (int i = 0; i < m_analogSensorBindings.getSize(); i++)
		{
			m_analogSensorBindings[i].callback(
				Crc::CrcLib::GetAnalogInput(m_analogSensorBindings[i].pin));
		}
	}

private:
	//Vector arrays
	aex::Vector<DigitalBinding>			m_digitalBindings; //Create a vector array of type DigitalBinding
	aex::Vector<ToggleBinding>			m_toggleBindings; //Create a vector array of type ToggleBinding
	aex::Vector<AnalogBinding>			m_analogBindings; //Create a vector array of type AnalogBinding
	aex::Vector<DigitalSensorBinding>	m_digitalSensorBindings; //Create a vector array of type DigitalSensorBinding
	aex::Vector<AnalogSensorBinding>	m_analogSensorBindings; //Create a vector array of type AnalogBinding
};

} // rou

#endif // _INCLUDE_ROU_CONTROLLER_H_
