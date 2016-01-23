/*
 * Shooter.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Seth
 */

#include "Shooter.h"
#include "config.h"

class Shooter {
	private:
		VictorSP *m_leftMotorController;
		VictorSP *m_rightMotorController;
	public:
		/**
		* Makes a shooter with a left motor channel, a right one, the speed to launch at, and the speed for retracting (sucking up) a ball into the launcher
		*/
		Shooter() {
			m_leftMotorController = new VictorSP(SHOOTER_LAUNCH_LEFT_MOTOR_CHANNEL);
			m_rightMotorController = new VictorSP(SHOOTER_LAUNCH_RIGHT_MOTOR_CHANNEL);

			m_leftMotorController->SetInverted(true);
		}

		/**
		* Yo holmes - This is how you slurp up the dodgeballs
		*/
		void Load() {
			m_leftMotorController->Set(SHOOTER_RETRACT_SPEED);
			m_rightMotorController->Set(SHOOTER_RETRACT_SPEED);
		}

		/**
		* Hey pal - This is how you throw the ball like a pro
		*/
		void Shoot() {
			m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
			m_rightMotorController->Set(SHOOTER_SHOOT_SPEED);
		}

		/**
		* You clearly did something, and now you wants to undo's it
		*/
		void Idle() {
			m_leftMotorController->Set(SHOOTER_RETRACT_SPEED);
			m_rightMotorController->Set(SHOOTER_RETRACT_SPEED);
		}

		int Constrain(int var, int min, int max) {
			// Needlessly complicated ternary (but just so quick to write)
			return (min < var && var < max ? var : (var < min ? min : max));
		}
};
