/*
 * Drive.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: jpaet
 */
#include "WPIlib.h"
#include "Drive.h"
#include "config.h"


//IMPORTANT NOTE:  - is forwards... + values are backwards...

Drive::Drive(Joystick *joy1, AnalogGyro *xGyro, AnalogGyro *yGyro) {
	m_drive = new RobotDrive(DRIVE_MOTOR_LEFT_FRONT_CHANNEL,
			DRIVE_MOTOR_LEFT_REAR_CHANNEL,
			DRIVE_MOTOR_RIGHT_FRONT_CHANNEL,
			DRIVE_MOTOR_RIGHT_REAR_CHANNEL);
	m_joy1 = joy1;
	m_drive->SetMaxOutput(DRIVE_MAX_SPEED);
	m_drive->SetSensitivity(DRIVE_TURNING_SENSITIVITY);
	m_outputMagnitude = 0;
	m_curve = 0;
	m_moveValue = 0;
	m_rotateValue = 0;
	m_yAxisGyro = yGyro;
	m_xAxisGyro = xGyro;
//	m_drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
//	m_drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
}

Drive::~Drive() {
	delete m_drive;
}

void Drive::ManualRobotDrive() {
	m_drive->ArcadeDrive(m_joy1->GetY(), m_joy1->GetZ(), true);
	SmartDashboard::PutNumber("X Axis Gyro: ", m_xAxisGyro->GetAngle());
}

void Drive::DriveInit() {

	m_yAxisGyro->Reset();
	m_xAxisGyro->Reset();

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

void Drive::Idle() {
	m_drive->ArcadeDrive(0, 0, true);
}

void Drive::RobotActiveStop() {

}

//this function must be run after the manual drive one!!!!!!!!
void Drive::EmergencyResponseDrive() {

	float emergencyValue = m_xAxisGyro->GetAngle();  //should be y gyro

	if(emergencyValue >= BACK_TIP_ANGLE) {

		m_drive->ArcadeDrive(0.5, 0, true);  //for real usage the first value must be much higher for effect

	}
}
