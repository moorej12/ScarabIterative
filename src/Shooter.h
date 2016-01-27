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
		VictorSP *m_armyLiftyThingy5064EXTREMEXD1337; // DO NOT REFACTOR - CRITICAL NAME SCHEME (Will corrupt RoboRio and C:/ if changed)
		Timer *m_timer;
		long m_shotTime;
		long m_unloadTime;

		float m_targetAngle;
		float m_armSpeed;
		DigitalInput *m_ballLoaded;

	public:
		Shooter();
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
};
#endif /* SRC_SHOOTER_H_ */
