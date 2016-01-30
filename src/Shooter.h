/*
 * Shooter.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Seth
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

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

		float m_targetAngle;
		float m_armSpeed;
		DigitalInput *m_ballLoaded;
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
		bool DeBounce();
		void PneumaticTest(bool status); //Test Code
};
#endif /* SRC_SHOOTER_H_ */
