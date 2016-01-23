/*
 * Shooter.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Seth
 */

#include "Shooter.h"
#include "config.h"
		/**
		* Makes a shooter
		*/
		Shooter::Shooter() {
			m_leftMotorController = new VictorSP(SHOOTER_LEFT_LAUNCH_MOTOR_CHANNEL);
			m_rightMotorController = new VictorSP(SHOOTER_RIGHT_LAUNCH_MOTOR_CHANNEL);
			m_targetAngle = 0;
			m_armSpeed = 0;
			m_ballLoaded = new DigitalInput(SHOOTER_BALL_LOADED_SENSOR_CHANNEL);

			m_leftMotorController->SetInverted(true);
		}


		Shooter::~Shooter() {
			delete m_ballLoaded;
			delete m_targetAngle;
		}

		/**
		* Yo holmes - This is how you slurp up the dodgeballs
		*/
		void Shooter::Load() {
			if(BallLoaded == false){
			m_leftMotorController->Set(SHOOTER_RETRACT_SPEED);
			m_leftMotorController->Set(SHOOTER_RETRACT_SPEED);
			}
		}

		void Shooter::SetAngle(float m_targetAngle) {

		}

		void Shooter::AdjustPosition(float m_armSpeed) {

		}

		/**
		* Hey pal - This is how you throw the ball like a pro
		*/
		void Shooter::Shoot() {
			if(BallLoaded == true) {
			m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
			m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
			}
		}

		/**
		* You clearly did something, and now you wants to undo's it
		*/
		void Shooter::Idle() {
			m_leftMotorController->Set(SHOOTER_RETRACT_SPEED);
			m_rightMotorController->Set(SHOOTER_RETRACT_SPEED);
		}

		//Tells whether the ball is loaded
		bool Shooter::BallLoaded() {
			return m_ballLoaded->Get();
		}

		float Shooter::Constrain(float var, float min, float max) {
			// Needlessly complicated ternary (but just so quick to write)
			return (min < var && var < max ? var : (var < min ? min : max));
		}

		//Slowly rotates the gripper wheels to eject the ball.
		//Should only be called when the sensor shows the ball is loaded.
		void Shooter::Unload(){
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

		//Returns a bool representing whether or not the shooter is able to shoot,
		//based on whether the ball is loaded.
		bool Shooter::CanShoot(/*not implemented*/){
		//To return true:
		//Touch Sensor == True
		}
