/*
 * Drive.h
 *
 *  Created on: Jan 23, 2016
 *      Author: jpaet
 */

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_

class Drive {
	private:
		RobotDrive *m_drive;
		Joystick *m_joy1;
		Joystick *m_dance1;
		float m_outputMagnitude;
		float m_curve;
		float m_moveValue;
		float m_rotateValue;

	public:
		Drive(Joystick *joy1);
		~Drive();
		void ManualRobotDrive();
		void AutoRobotDrive(float outputMagnitude, float curve);
		void AutoRobotHoldPosition(float moveValue, float rotateValue);
		void Idle();
		void RobotActiveStop();
};

#endif /* SRC_DRIVE_H_ */
