/*
 * Autonomous.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: jpaet
 */

#include "Autonomous.h"


Autonomous::Autonomous(Drive *drive, Shooter *shooter, Arms *arms, AnalogGyro *xGyro, AnalogGyro *yGyro, Encoder *encoder) {

//	m_autonomousType = SmartDashboard::GetNumber("Autonomous Obstacle Type:", -1);

	m_timer = new Timer();
	m_xAxisGyro = xGyro;
	m_yAxisGyro = yGyro;
	m_encoder = encoder;
	m_drive = drive;

	m_autonomousType = -1;
	m_stage = kAutonomousUNINITIALIZED;
	m_flatTime = 0;
	m_kP = 0.5;
	m_desiredHeading = 0;
}

Autonomous::~Autonomous() {

	delete m_timer;

}

void Autonomous::AutonomousInit(int autoMode) {
	m_autonomousType = autoMode;
	m_stage = kAutonomousUNINITIALIZED;
	m_timer->Reset();
	m_encoder->Reset();
	m_xAxisGyro->Reset();
	m_yAxisGyro->Reset();

	SmartDashboard::PutNumber("Encoder Distance", m_encoder->GetDistance());
	SmartDashboard::PutNumber("Encoder Value", m_encoder->GetRaw());
}

void Autonomous::Update() {
	AutonomousCompare();

}

void Autonomous::AutonomousCompare() {

	switch(m_stage) {
		case kAutonomousUNINITIALIZED:
			m_stage = kAutonomousDRIVING;

		break;


		case kAutonomousDRIVING:
			BeginDrive();

		break;

		case kAutonomousCORRECTING:


		break;


		case kAutonomousFINISHED:
			m_drive->AutoRobotDrive(0, -m_xAngle * m_kP);

		break;


		case kAutonomousROUGHTERRAIN:

			m_drive->AutoRobotDrive(0.5, -m_xAngle * m_kP);
			CheckCompletedDefense();

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
			m_drive->AutoRobotDrive(0.5, -m_xAngle * m_kP);
			CheckCompletedDefense();

		break;


		case kAutonomousLOWBAR:
			m_drive->AutoRobotDrive(0.5, -m_xAngle * m_kP);
			if(m_encoder->GetDistance() >= 84) { //Needs proper value
				m_stage = kAutonomousFINISHED;
			}

		break;
	}
}


void Autonomous::Correction() {

	float xAngle = m_xAxisGyro->GetAngle(); // get heading

	float correctionDirection5064EXTREMEXD1337x8K = 0;

	if(xAngle < (-1 * AUTO_ERROR_MARGIN)) {

		correctionDirection5064EXTREMEXD1337x8K = 1;
	}

	else if(xAngle > AUTO_ERROR_MARGIN) {

		correctionDirection5064EXTREMEXD1337x8K = -1;
	}

	m_drive->AutoRobotHoldPosition(0, correctionDirection5064EXTREMEXD1337x8K * AUTO_CORRECTION_SPEED);

//	m_drive->AutoRobotHoldPosition(0, -xAngle * CORRECTION_SPEED);
	//m_drive->AutoRobotDrive(-0.2, -xAngle * kP); // turn to correct heading
//	printf("\n The angle is: %f", xAngle);

}
//handles everything before moving up the ramp
void Autonomous::BeginDrive() {

	ProportionalCurve();
	m_drive->AutoRobotDrive(0.5, -m_xAngle * m_kP); // turn to correct heading

	printf("/n The Y axis angle is: %f", m_yAngle);
	if(m_yAngle >= RAMP_ANGLE) {
		m_stage = kAutonomousCORRECTING;
		Correction();
	}
}

void Autonomous::CorrectStage() {
	if(m_xAngle > -AUTO_ERROR_MARGIN && m_xAngle < AUTO_ERROR_MARGIN) {
		m_stage = static_cast<Stage>(m_autonomousType);  //this changes m_autonomousType int into enum Stage
	}
	else {
		Correction();
	}
}

void Autonomous::CheckCompletedDefense() {
	if(m_yAngle >= 1 && m_yAngle <= 1 && m_flatTime >= 50) {
		m_stage = kAutonomousFINISHED;
		m_flatTime = 0;
	}
	else if(m_yAngle >= 1 && m_yAngle <= 1) {
		m_flatTime++;
	}
	else {
		m_flatTime = 0;
	}
}

 void Autonomous::ProportionalCurve() {

	//x divided by the square root of x^2+1

	double angle = m_xAxisGyro->GetAngle();
	double error = angle - m_desiredHeading;
	m_kP = (error)/(sqrt((pow(error,2)) + STRETCH_CONSTANT));
}
