/*
 * Shooter.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Seth
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include "WPIlib.h"
#include "Debounce.h"

class Shooter {
	public:
		Shooter(Joystick *joy1);
		~Shooter();
		typedef enum {kShooterUNINITIALIZED, kShooterIDLE, kShooterLOADING, kShooterLOADED, kShooterUNLOADING, kShooterSHOOTING, kShooterUNLOAD, kShooterSHOOT} Status;
		void StateMachine();
		void Load();
		void ShooterAngle(float targetAngle);
		void Shoot();
		void Idle();
		bool BallLoaded();
		void Unload();
		bool CanLoad();
		bool CanShoot();
		void Update();
		void Debug();
		void PneumaticTest(bool status); //Test Code
		void Init(); //Resets all values to zero
	private:
		VictorSP *m_leftMotorController;
		VictorSP *m_rightMotorController;
		VictorSP *m_angleMotorController;
		Solenoid *m_ballyLaunchyThingy5064EXTREMEXD1337; // DO NOT REFACTOR - CRITICAL NAME SCHEME (Will corrupt RoboRio and C:/ if changed)
		AnalogPotentiometer *m_shooterPotentiometer;
		PIDController *m_shooterPIDController;
		Timer *m_timer;
		Status m_status;
		bool m_lastPressed;
		Debounce *m_shootButton;
		Debounce *m_loadButton;
		Debounce *m_unloadButton;
		Debounce *m_idleButton;
		Debounce *m_loadedButton;
		Debounce *m_shootAngleButton;
		Debounce *m_shooterLowAngleButton;
		Debounce *m_shooterHighAngleButton;
		Debounce *m_shooterLittleLowAngleButton;
		Debounce *m_shooterLittleHighAngleButton;

		float m_targetAngle;
		DigitalInput *m_ballLoadedButton;
		DigitalInput *m_maxAngleButton;
		DigitalInput *m_minAngleButton;
		bool m_ballLoaded;
		Joystick *m_joy2;

};
#endif /* SRC_SHOOTER_H_ */
