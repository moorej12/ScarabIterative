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

	public:
		Drive();
		~Drive();
		void RobotMove();
		void RobotActiveStop();
};

#endif /* SRC_DRIVE_H_ */
