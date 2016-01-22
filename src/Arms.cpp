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
		VictorSP *m_leftArmsMotor;
		VictorSP *m_rightArmsMotor;
		float *m_armAngle;

	public:
		Arms::Arms() {
			m_leftArmsMotor = new VictorSP(ARMS_LEFT_MOTOR_CHANNEL);
			m_rightArmsMotor = new VictorSP(ARMS_RIGHT_MOTOR_CHANNEL);
			m_armAngle = 0;
		}
		Arms::~Arms() {
			delete m_leftArmsMotor;
			delete m_rightArmsMotor;
			delete m_armAngle;
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
