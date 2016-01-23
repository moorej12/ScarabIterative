/*
 * Drive.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: jpaet
 */
#include "WPIlib.h"
#include "Drive.h"
#include "config.h"

Drive::Drive() {
	m_drive = new RobotDrive(DRIVE_MOTOR_LEFT_FRONT_CHANNEL, DRIVE_MOTOR_LEFT_REAR_CHANNEL, DRIVE_MOTOR_RIGHT_FRONT_CHANNEL, DRIVE_MOTOR_RIGHT_REAR_CHANNEL);
	m_joy1 = new Joystick(0);
}

Drive::~Drive() {
	delete m_drive;
	delete m_joy1;
}

//(+) for forwards and (-) for backwards; sets the current
//velocity for the robot
void Drive::RobotMove() {

}

//put in power to actively stop the movement of the robot
void Drive::RobotActiveStop() {

}
