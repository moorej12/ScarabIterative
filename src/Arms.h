/*
 * Arms.h
 *
 *  Created on: Jan 19, 2016
 *      Author: Jonathan
 */

#ifndef SRC_ARMS_H_
#define SRC_ARMS_H_

#include "WPIlib.h"
#include "config.h"
class Arms {
	private:
		float m_armAngle;
		Encoder *m_leftEncoder;
		Encoder *m_rightEncoder;
		float m_targetArmsAngle;
//		Potentiometer *m_leftArmsPotentiometer;
//		Potentiometer *m_rightArmsPotentiometer;
		PIDController *m_leftArmsPIDController;
		PIDController *m_rightArmsPIDController;
		VictorSP *m_rightArmsMotorController;
		VictorSP *m_leftArmsMotorController;
	public:
		Arms();
		~Arms();
		void Update();
		void SetPosition(float m_setArmAngle);
		void Move();
		float GetPosition();

		void Init(); //Resets all values to zero

		void ArmsAngle();

};

#endif /* SRC_ARMS_H_ */
