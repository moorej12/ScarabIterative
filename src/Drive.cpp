/*
 * Drive.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: jpaet
 */
#include "WPIlib.h"
#include "Drive.h"
#include "config.h"

Drive::Drive(Joystick *joy1) {
	m_drive = new RobotDrive(DRIVE_MOTOR_LEFT_FRONT_CHANNEL,
			DRIVE_MOTOR_LEFT_REAR_CHANNEL,
			DRIVE_MOTOR_RIGHT_FRONT_CHANNEL,
			DRIVE_MOTOR_RIGHT_REAR_CHANNEL);
	m_joy1 = joy1;
}

Drive::~Drive() {
	delete m_drive;
}

//(+) for forwards and (-) for backwards; sets the current
//velocity for the robot
void Drive::RobotMove() {
	m_drive->ArcadeDrive(m_joy1->GetY(), m_joy1->GetZ(), true);
}

//put in power to actively stop the movement of the robot
void Drive::RobotActiveStop() {

}
