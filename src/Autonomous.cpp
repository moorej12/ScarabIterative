/*
 * Autonomous.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: jpaet
 */

#include "Autonomous.h"


Autonomous::Autonomous(Drive *drive, Shooter *shooter, Arms *arms, AnalogGyro *xGyro, AnalogGyro *yGyro, Encoder *rightEncoder, Encoder *leftEncoder) {

//	m_autonomousType = SmartDashboard::GetNumber("Autonomous Obstacle Type:", -1);
//
	m_xAxisGyro = xGyro;
	m_yAxisGyro = yGyro;

	m_rightSideEncoder = rightEncoder;
	m_leftSideEncoder = leftEncoder;
	m_drive = drive;
	m_autonomousType = -1;
}

Autonomous::~Autonomous() {



}

void Autonomous::AutonomousInit() {

	m_autonomousType = SmartDashboard::GetNumber("Autonomous Obstacle Type:", -1);
	m_xAxisGyro->Reset();
	m_xAxisGyro->SetDeadband(GYRO_DEADBAND);


}

void Autonomous::AutonomousCompare() {

	if(m_autonomousType == ROUGH_TERRAIN) {


	}
	else if(m_autonomousType == PORTCULLIS) {


	}
	else if(m_autonomousType == ROCK_WALL) {


	}
	else if(m_autonomousType == MOAT) {


	}
	else if(m_autonomousType == TEETER_TOTTERS) {


	}
	else if(m_autonomousType == RAMPARTS) {


	}
	else if(m_autonomousType == LOW_BAR) {


	}
	else {
		printf("\n ERROR: Autonomous did not receive an appropriate value. Current value: %lf", m_autonomousType);

	}
}

//Functions specifically for each gate type



//Functions that can be for any gate type
void Autonomous::BeginDrive() {

	float xAngle = m_xAxisGyro->GetAngle(); // get heading
	float check = 0;

	if(xAngle < (-1 * AUTO_ERROR_MARGIN)) {

		check = 1;
	}

	else if(xAngle > AUTO_ERROR_MARGIN) {

		check = -1;
	}

	m_drive->AutoRobotHoldPosition(0, check * AUTO_CORRECTION_SPEED);

	//m_drive->AutoRobotDrive(-0.2, -xAngle * kP); // turn to correct heading


	printf("\n The angle is: %f", xAngle);

}



