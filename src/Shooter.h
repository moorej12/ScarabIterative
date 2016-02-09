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
		void SetAngle(float m_targetAngle);
		void AdjustPosition();
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
		Timer *m_timer;
		Status m_status;
		bool m_lastPressed;
		Debounce *m_shootButton;
		Debounce *m_loadButton;
		Debounce *m_unloadButton;
		Debounce *m_idleButton;
		Debounce *m_loadedButton;

		float m_targetAngle;
		DigitalInput *m_ballLoadedButton;
		bool m_ballLoaded;
		Joystick *m_joy2;

};
#endif /* SRC_SHOOTER_H_ */
