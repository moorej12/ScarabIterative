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
Shooter::Shooter(Joystick *joy1) {
	m_joy2 = joy1;
	m_leftMotorController = new VictorSP(SHOOTER_LEFT_LAUNCH_MOTOR_CHANNEL);
	m_rightMotorController = new VictorSP(SHOOTER_RIGHT_LAUNCH_MOTOR_CHANNEL);
	m_targetAngle = 0;
	m_armSpeed = 0;
	m_ballLoaded = new DigitalInput(SHOOTER_BALL_LOADED_SENSOR_CHANNEL);

	m_shotTime = -1;
	m_loadTime = -1;
	m_unloadTime = -1;

	m_timer = new Timer();
	m_timer->Reset();
	m_timer->Start();

	m_leftMotorController->SetInverted(true);

	m_ballyLaunchyThingy5064EXTREMEXD1337 = new Solenoid(BALLY_LAUNCHY_THINGY_5064_EXTREME_XD_1337_CHANNEL); //Needs stuff
	m_lastPressed = false;
}


Shooter::~Shooter() {
	delete m_ballLoaded;
	delete m_timer;
	delete m_ballyLaunchyThingy5064EXTREMEXD1337;
}

//Yo holmes - This is how you slurp up the dodgeballs
void Shooter::Load() {

	m_loadTime = m_timer->Get();
	if(BallLoaded() == false){
		m_ballyLaunchyThingy5064EXTREMEXD1337->Set(false);
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

//	if(m_timer->Get() > SHOOTER_SHOOT_CANCELLATION_TIME_MS + m_shotTime && m_shotTime > -1) {
//		Idle();
//		if(m_shotTime > -1) {
//			m_shotTime = -2;
//		}
//	}
//
//	if(m_loadTime > -1 && BallLoaded()) {
//		Idle();
//		m_loadTime = -1;
//	}
//
//	if(m_timer->Get() > SHOOTER_PLATFORM_CANCELLATION_TIME_MS + m_shotTime && m_shotTime > -1) {
//
//	}
//
//	if(m_timer->Get() > SHOOTER_PLATFORM_CANCELLATION_TIME_MS + m_unloadTime && m_unloadTime > -1) {
//		Idle();
//		m_unloadTime = -1;
//	}

	Debug();
}

//Hey pal - This is how you throw the ball like a pro
void Shooter::Shoot() {
	if(BallLoaded() == true) {
		m_shotTime = m_timer->Get();
		m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
		m_rightMotorController->Set(SHOOTER_SHOOT_SPEED);
		//m_ballyLaunchyThingy5064EXTREMEXD1337->Set(true); //Needs timers
	}
}

//You clearly did something, and now you wants to undo's it
void Shooter::Idle() {
	m_leftMotorController->Set(SHOOTER_IDLE_SPEED);
	m_rightMotorController->Set(SHOOTER_IDLE_SPEED);
}

//Tells whether the ball is loaded
bool Shooter::BallLoaded() {
	//return m_ballLoaded->Get();
	return true;
}

//Slowly rotates the gripper wheels to eject the ball.
//Should only be called when the sensor shows the ball is loaded.
void Shooter::Unload(){
	if(BallLoaded() == true) {
		m_unloadTime = m_timer->Get();
		m_leftMotorController->Set(SHOOTER_UNLOAD_SPEED);
		m_rightMotorController->Set(SHOOTER_UNLOAD_SPEED);
		//m_ballyLaunchyThingy5064EXTREMEXD1337->Set(true); //Needs timers
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

void Shooter::Debug() {
	//An example of how to use the SmartDashboard...
	SmartDashboard::PutNumber("Timer Value", m_timer->Get());

}

bool Shooter::DeBounce() {

	bool pseudoLastPressed = m_lastPressed;
	//	m_lastPressed = m_joy1->

	if((pseudoLastPressed) == false && m_joy2->GetTrigger()){
		return true;
	}
}


void Shooter::PneumaticTest(bool status) { //Test Code
	m_ballyLaunchyThingy5064EXTREMEXD1337->Set(status);
}
