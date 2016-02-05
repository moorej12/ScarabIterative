/*
 * Arms.h
 *
 *  Created on: Jan 19, 2016
 *      Author: Jonathan
 */

#ifndef SRC_ARMS_H_
#define SRC_ARMS_H_

class Arms {
	private:
		float m_armAngle;
		Encoder *m_leftEncoder;
		Encoder *m_rightEncoder;
		float m_targetArmsAngle;
		VictorSP *m_leftArmsMotor;
		VictorSP *m_rightArmsMotor;

	public:
		Arms();
		~Arms();
		void SetPosition(float m_setArmAngle);
		void Move();
		float GetPosition();

		void Init(); //Resets all values to zero

};

#endif /* SRC_ARMS_H_ */
