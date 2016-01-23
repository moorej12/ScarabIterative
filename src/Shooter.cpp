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
		float m_rSpeed;
		float m_fSpeed;
		float m_iSpeed;
		float *m_setArmAngle;
		float *m_armSpeed;
		DigitalInput *m_ballLoaded;
	public:
		/**
		* Makes a shooter with a left motor channel, a right one, the speed to launch at, and the speed for retracting (sucking up) a ball into the launcher
		*/
		Shooter(int fSpeed, int rSpeed) {
			m_leftMotorController = new Jaguar(SHOOTER_LEFT_LAUNCH_MOTOR_CHANNEL);
			m_leftMotorController = new Jaguar(SHOOTER_RIGHT_LAUNCH_MOTOR_CHANNEL);
			m_fSpeed = Constrain(fSpeed, -1, 1);
			m_rSpeed = Constrain(rSpeed, -1, 1);
			m_iSpeed = 0;
			float m_setArmAngle = 0;
			float m_armSpeed = 0;
			m_ballLoaded = new DigitalInput(SHOOTER_BALL_LOADED_SENSOR_CHANNEL);

			m_leftMotorController->SetInverted(true);
		}

		/**
		* Takes all the standard variables, but includes a speed to idle at between -1 and 1.
		* -N will pull objects in, and N will repel them.
		*/
		Shooter(int fSpeed, int rSpeed, int iSpeed) {
			m_leftMotorController = new Jaguar(SHOOTER_LEFT_LAUNCH_MOTOR_CHANNEL);
			m_leftMotorController = new Jaguar(SHOOTER_RIGHT_LAUNCH_MOTOR_CHANNEL);
			m_fSpeed = Constrain(fSpeed, -1, 1);
			m_rSpeed = Constrain(rSpeed, -1, 1);
			m_iSpeed = Constrain(iSpeed, -1, 1);

			m_leftMotorController->SetInverted(true);
		}

		~Shooter() {
			delete m_ballLoaded;
			delete m_setArmAngle;
		}

		/**
		* Yo holmes - This is how you slurp up the dodgeballs
		*/
		void Load() {
			if(BallLoaded == false){
			m_leftMotorController->Set(m_rSpeed);
			m_leftMotorController->Set(m_rSpeed);
			}
		}

		void SetAngle(m_setArmAngle) {

		}

		void AdjustPosition(m_armSpeed) {

		}

		/**
		* Hey pal - This is how you throw the ball like a pro
		*/
		void Shoot() {
			if(BallLoaded == true) {
			m_leftMotorController->Set(m_fSpeed);
			m_leftMotorController->Set(m_fSpeed);
			}
		}

		/**
		* You clearly did something, and now you wants to undo's it
		*/
		void Idle() {
			m_leftMotorController->Set(m_iSpeed);
			m_leftMotorController->Set(m_iSpeed);
		}

		//Tells whether the ball is loaded
		bool BallLoaded() {
			return m_ballLoaded->Get();
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
