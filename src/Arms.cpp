/*
 * Arms.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: Jonathan
 */
#include "WPIlib.h"
#include "Arms.h"
#include "config.h"

class Arms {
	private:
		//make sure to update the arm angle every cycle...
		float m_armAngle;
		Encoder *m_leftEncoder;
		Encoder *m_rightEncoder;
		float m_targetArmsAngle;
		VictorSP *m_leftArmsMotor;
		VictorSP *m_rightArmsMotor;

	public:
		Arms() {
			m_leftArmsMotor = new VictorSP(LEFT_ARMS_MOTOR_CHANNEL);
			m_rightArmsMotor = new VictorSP(RIGHT_ARMS_MOTOR_CHANNEL);
			m_armAngle = 0;
		}
		~Arms() {
			delete m_leftArmsMotor;
			delete m_rightArmsMotor;
		}
		//Sets arm position based on value in degrees
		void SetPosition(float m_setArmAngle) {

		}

		//Allows driver to move arms manually
		void Move() {

		}

		//Gets the angle of the arms from the potentiometer
		float GetPosition() {
			return m_armAngle;
		}


};
