/*
 * Autonomous.h
 *
 *  Created on: Feb 9, 2016
 *      Author: jpaet
 */

#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

#include "WPILIB.h"
#include "config.h"
#include "Autonomous.h"
#include "Arms.h"
#include "Shooter.h"
#include "Drive.h"

#define ROUGH_TERRAIN 0
#define PORTCULLIS 1
#define ROCK_WALL 2
#define MOAT 3
#define TEETER_TOTTERS 4
#define RAMPARTS 5
#define LOW_BAR 6

class Autonomous {

	public:
		Autonomous(Drive *drive, Shooter *shooter, Arms *arms, AnalogGyro *xGyro, AnalogGyro *yGyro, Encoder *rightEncoder, Encoder *leftEncoder);
		~Autonomous();
		void AutonomousInit();
		void AutonomousCompare();
		void BeginDrive();
	private:

		double m_autonomousType;
		AnalogGyro *m_xAxisGyro;
		AnalogGyro *m_yAxisGyro;
		Drive *m_drive;
		Encoder *m_rightSideEncoder;
		Encoder *m_leftSideEncoder;


};


#endif /* AUTONOMOUS_H_ */
