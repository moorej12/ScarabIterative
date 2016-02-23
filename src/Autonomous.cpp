/*
 * Autonomous.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: jpaet
 */

#include "Autonomous.h"


Autonomous::Autonomous(Drive *drive, Shooter *shooter, Arms *arms, AnalogGyro *xGyro, AnalogGyro *yGyro, Encoder *rightEncoder, Encoder *leftEncoder, Ultrasonic *ultrasonic) {

//	m_autonomousType = SmartDashboard::GetNumber("Autonomous Obstacle Type:", -1);

	m_timer = new Timer();
	m_xAxisGyro = xGyro;
	m_yAxisGyro = yGyro;
	m_ultrasonicSensor = ultrasonic;
	m_rightSideEncoder = rightEncoder;
	m_leftSideEncoder = leftEncoder;
	m_drive = drive;
<<<<<<< HEAD
=======
	m_autonomousType = -1;
	m_stage = kAutonomousUNINITIALIZED;
>>>>>>> 52ba3d8960080e160bd7e3bd6ebe86f59bda5285
}

Autonomous::~Autonomous() {



}

void Autonomous::AutonomousInit(int autoMode) {
	m_autonomousType = autoMode;
	m_xAxisGyro->Reset();
<<<<<<< HEAD
=======
	m_yAxisGyro->Reset();
	m_xAxisGyro->SetDeadband(GYRO_DEADBAND);
	m_yAxisGyro->SetDeadband(GYRO_DEADBAND);
	m_stage = kAutonomousUNINITIALIZED;\
	m_timer->Reset();
>>>>>>> 52ba3d8960080e160bd7e3bd6ebe86f59bda5285

}

void Autonomous::AutonomousCompare() {

	switch(m_stage) {
		case kAutonomousUNINITIALIZED:


		break;


		case kAutonomousDRIVING:


		break;


		case kAutonomousROUGHTERRAIN:


		break;


		case kAutonomousPORTCULLIS:


		break;


		case kAutonomousROCKWALL:


		break;


		case kAutonomousMOAT:


		break;


		case kAutonomousTEETERTOTTER:


		break;


		case kAutonomousRAMPARTS:


		break;


		case kAutonomousLOWBAR:


		break;

	}

}


void Autonomous::Correction() {

	float xAngle = m_xAxisGyro->GetAngle(); // get heading

<<<<<<< HEAD
	m_drive->AutoRobotHoldPosition(0, -xAngle * CORRECTION_SPEED);
	//m_drive->AutoRobotDrive(-0.2, -xAngle * kP); // turn to correct heading
=======
//	printf("\n The angle is: %f", xAngle);

}
>>>>>>> 52ba3d8960080e160bd7e3bd6ebe86f59bda5285

//handles everything before moving up the ramp
void Autonomous::BeginDrive() {

	float xAngle = m_xAxisGyro->GetAngle();
	float yAngle = m_yAxisGyro->GetAngle();
	float kP = 0.5;

//	m_drive->AutoRobotDrive(-0.2, -xAngle * kP); // turn to correct heading

	printf("The Y axis angle is: %f", yAngle);
//	if(yAngle >= RAMP_ANGLE) {


//	}

}
