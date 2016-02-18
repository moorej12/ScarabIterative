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
	m_drive->SetMaxOutput(DRIVE_MAX_SPEED);
	m_outputMagnitude = 0;
	m_curve = 0;
	m_moveValue = 0;
	m_rotateValue = 0;
}

Drive::~Drive() {
	delete m_drive;
}

void Drive::ManualRobotDrive() {
	m_drive->ArcadeDrive(m_joy1->GetY(), m_joy1->GetZ(), true);
}

//(+) for forwards and (-) for backwards; sets the current
//velocity for the robot
void Drive::AutoRobotDrive(float outputMagnitude, float curve) {
	m_outputMagnitude = outputMagnitude;
	m_curve = curve;
	m_drive->Drive(outputMagnitude, curve);
}

void Drive::AutoRobotHoldPosition(float moveValue, float rotateValue) {
	m_moveValue = moveValue;
	m_rotateValue = rotateValue;

	m_drive->ArcadeDrive(moveValue, rotateValue, true);

}

void Drive::RobotActiveStop() {

}
