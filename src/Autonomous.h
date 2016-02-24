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
#include "math.h"

#define ROUGH_TERRAIN 0
#define PORTCULLIS 1
#define ROCK_WALL 2
#define MOAT 3
#define TEETER_TOTTERS 4
#define RAMPARTS 5
#define LOW_BAR 6

class Autonomous {

	public:
		Autonomous(Drive *drive, Shooter *shooter, Arms *arms, AnalogGyro *xGyro, AnalogGyro *yGyro, Encoder *encoder);
		~Autonomous();
		void AutonomousInit(int autoMode);
		void Update();
		void AutonomousCompare();
		void BeginDrive();
		void SetMode(int mode);
		void Correction();
		void CorrectStage();
		void CheckCompletedDefense();
		typedef enum {kAutonomousROUGHTERRAIN, kAutonomousPORTCULLIS, kAutonomousROCKWALL, kAutonomousMOAT, kAutonomousTEETERTOTTER, kAutonomousRAMPARTS, kAutonomousLOWBAR, kAutonomousUNINITIALIZED, kAutonomousDRIVING, kAutonomousCORRECTING, kAutonomousFINISHED} Stage;
		void ProportionalCurve();

	private:

		double m_autonomousType;
		AnalogGyro *m_xAxisGyro;
		AnalogGyro *m_yAxisGyro;
		Drive *m_drive;
		Encoder *m_encoder;
		Stage m_stage;
		Timer *m_timer;
		int m_flatTime;
		float m_xAngle;
		float m_yAngle;
		float m_kP;
		float m_desiredHeading;
		Shooter *m_shooter;
};


#endif /* AUTONOMOUS_H_ */
