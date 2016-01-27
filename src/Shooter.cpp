/*
 * Shooter.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Seth
 */

#include "WPIlib.h"
#include "Shooter.h"
#include "config.h"

//Makes a shooter
Shooter::Shooter() {
	m_leftMotorController = new VictorSP(SHOOTER_LEFT_LAUNCH_MOTOR_CHANNEL);
	m_rightMotorController = new VictorSP(SHOOTER_RIGHT_LAUNCH_MOTOR_CHANNEL);
	m_targetAngle = 0;
	m_armSpeed = 0;
	m_ballLoaded = new DigitalInput(SHOOTER_BALL_LOADED_SENSOR_CHANNEL);

	m_shotTime = -1;

	m_timer = new Timer();
	m_timer->Reset();
	m_timer->Start();

	m_leftMotorController->SetInverted(true);
	m_armyLiftyThingy5064EXTREMEXD1337 = new VictorSP(ARMY_LIFTY_THINGY_5064_EXTEREME_XD_1337_CHANNEL);
}


Shooter::~Shooter() {
	delete m_ballLoaded;
	delete m_timer;
}

//Yo holmes - This is how you slurp up the dodgeballs
void Shooter::Load() {
	if(BallLoaded() == false){
		m_leftMotorController->Set(SHOOTER_RETRACT_SPEED);
		m_rightMotorController->Set(SHOOTER_RETRACT_SPEED);
	}
}

void Shooter::SetAngle(float targetAngle) {
	m_targetAngle = targetAngle;
}

void Shooter::AdjustPosition(float armSpeed) {
	m_armSpeed = armSpeed;

}

void Shooter::Update() {
	if(m_timer->Get() > SHOOTER_SHOOT_CANCELLATION_TIME_MS + m_shotTime && m_shotTime > -1) {
		Idle();
		if(m_shotTime > -1) {
			m_shotTime = -2;
		}
	}

	if(m_timer->Get() > SHOOTER_PLATFORM_CANCELLATION_TIME_MS + m_shotTime && m_shotTime > -1) {
		m_armyLiftyThingy5064EXTREMEXD1337->Set(0); // TODO: Make this retract in future
	}

	if(m_timer->Get() > SHOOTER_PLATFORM_CANCELLATION_TIME_MS + m_unloadTime && m_unloadTime > -1) {

	}
}

//Hey pal - This is how you throw the ball like a pro
void Shooter::Shoot() {
	if(BallLoaded() == true) {
		m_shotTime = m_timer->Get();
		m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
		m_rightMotorController->Set(SHOOTER_SHOOT_SPEED);
		m_armyLiftyThingy5064EXTREMEXD1337->Set(SHOOTER_PLATFORM_RAISE_SPEED);
	}
}

/**
* You clearly did something, and now you wants to undo's it
*/
void Shooter::Idle() {
	m_leftMotorController->Set(SHOOTER_IDLE_SPEED);
	m_rightMotorController->Set(SHOOTER_IDLE_SPEED);
}

//Tells whether the ball is loaded
bool Shooter::BallLoaded() {
	return m_ballLoaded->Get();
}

//Slowly rotates the gripper wheels to eject the ball.
//Should only be called when the sensor shows the ball is loaded.
void Shooter::Unload(){
	if(BallLoaded() == true) {
		m_unloadTime = m_timer->Get();
		m_leftMotorController->Set(SHOOTER_UNLOAD_SPEED);
		m_rightMotorController->Set(SHOOTER_UNLOAD_SPEED);
		m_armyLiftyThingy5064EXTREMEXD1337->Set(SHOOTER_PLATFORM_RAISE_SPEED);
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
