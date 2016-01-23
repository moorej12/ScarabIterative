/*
 * Shooter.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Seth
 */

#include "Shooter.h"

class Shooter {
	private:
		VictorSP *m_leftMotorController;
		VictorSP *m_rightMotorController;
		float m_rSpeed;
		float m_fSpeed;
		float m_iSpeed;
	public:
		/**
		* Makes a shooter with a left motor channel, a right one, the speed to launch at, and the speed for retracting (sucking up) a ball into the launcher
		*/
		Shooter(int leftChannel, int rightChannel, int fSpeed, int rSpeed) {
			m_leftMotorController = new Jaguar(leftChannel);
			m_leftMotorController = new Jaguar(rightChannel);
			m_fSpeed = Constrain(fSpeed, -1, 1);
			m_rSpeed = Constrain(rSpeed, -1, 1);
			m_iSpeed = 0;

			m_leftMotorController->SetInverted(true);
		}

		/**
		* Takes all the standard variables, but includes a speed to idle at between -1 and 1.
		* -N will pull objects in, and N will repel them.
		*/
		Shooter(int leftChannel, int rightChannel, int fSpeed, int rSpeed, int iSpeed) {
			m_leftMotorController = new Jaguar(leftChannel);
			m_leftMotorController = new Jaguar(rightChannel);
			m_fSpeed = Constrain(fSpeed, -1, 1);
			m_rSpeed = Constrain(rSpeed, -1, 1);
			m_iSpeed = Constrain(iSpeed, -1, 1);

			m_leftMotorController->SetInverted(true);
		}

		/**
		* Yo holmes - This is how you slurp up the dodgeballs
		*/
		void Load() {
			m_leftMotorController->Set(m_rSpeed);
			m_leftMotorController->Set(m_rSpeed);
		}

		/**
		* Hey pal - This is how you throw the ball like a pro
		*/
		void Shoot() {
			m_leftMotorController->Set(m_fSpeed);
			m_leftMotorController->Set(m_fSpeed);
		}

		/**
		* You clearly did something, and now you wants to undo's it
		*/
		void Idle() {
			m_leftMotorController->Set(m_iSpeed);
			m_leftMotorController->Set(m_iSpeed);
		}

		int Constrain(int var, int min, int max) {
			// Needlessly complicated ternary (but just so quick to write)
			return (min < var && var < max ? var : (var < min ? min : max));
		}
		//Slowly rotates the gripper wheels to eject the ball.
		//Should only be called when the sensor shows the ball is loaded.
		void Unload(){
			if(BallLoaded == true) {

			}
		}
		//returns a bool representing whether or not the shooter is able to load,
		//based on if the piston is retracted and the ball is loaded.
		bool Shooter::CanLoad(/*not implemented*/){
			//To return true:
			//-Piston Extended == False
			//-Touch Sensor == False
		}
};
