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
	private:
		VictorSP *m_leftMotorController;
		VictorSP *m_rightMotorController;
		Solenoid *m_ballyLaunchyThingy5064EXTREMEXD1337; // DO NOT REFACTOR - CRITICAL NAME SCHEME (Will corrupt RoboRio and C:/ if changed)
		Timer *m_timer;
		double m_shotTime;
		double m_unloadTime;
		double m_loadTime;
		bool m_lastPressed;
		Debounce *m_shootButton;
		Debounce *m_loadButton;
		Debounce *m_unloadButton;
		Debounce *m_idleButton;
		bool m_shooting;
		bool m_loading;
		bool m_unloading;

		float m_targetAngle;
		float m_armSpeed;
		DigitalInput *m_ballLoadedButton;
		bool m_ballLoaded;
		Joystick *m_joy2;

	public:
		Shooter(Joystick *joy1);
		~Shooter();
		void Load();
		void SetAngle(float m_targetAngle);
		void AdjustPosition(float m_armSpeed);
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

};
#endif /* SRC_SHOOTER_H_ */
