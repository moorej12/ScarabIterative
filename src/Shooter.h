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

		float *m_targetAngle;
		float *m_armSpeed;
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
};
#endif /* SRC_SHOOTER_H_ */
