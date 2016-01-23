/*
 * Drive.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: jpaet
 */
#include "WPIlib.h"
#include "Drive.h"
#include "config.h"

class Drive {
	private:
		RobotDrive *m_drive;
		Joystick *m_joy1;

	public:
		Drive() {
			m_drive = new RobotDrive(/*Needs motor channels */);
			m_joy1 = new Joystick(0);
		}

		~Drive() {
			delete m_drive;
			delete m_joy1;
		}

		//(+) for forwards and (-) for backwards; sets the current
		//velocity for the robot
		void RobotMove() {

		}

		//put in power to actively stop the movement of the robot
		void RobotActiveStop() {

		}

};


