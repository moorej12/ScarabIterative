/*
 * Shooter.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Seth
 */

#include "WPIlib.h"
#include "Shooter.h"
#include "config.h"
#include "Debounce.h"

#define ballyLaunchyShoot true
#define ballyLaunchyRetract !ballyLaunchyShoot

//Makes a shooter
Shooter::Shooter(Joystick *joy1) {
	m_joy2 = joy1;
	m_leftMotorController = new VictorSP(SHOOTER_LEFT_LAUNCH_MOTOR_CHANNEL);
	m_rightMotorController = new VictorSP(SHOOTER_RIGHT_LAUNCH_MOTOR_CHANNEL);
	m_targetAngle = 0;
	m_armSpeed = 0;
	m_ballLoadedButton = new DigitalInput(SHOOTER_BALL_LOADED_SENSOR_CHANNEL);
	m_ballLoaded = false;

	m_shootButton = new Debounce(m_joy2, 1);
	m_loadButton = new Debounce(m_joy2, 2);
	m_unloadButton = new Debounce(m_joy2, 3);

	m_shotTime = 0;
	m_loadTime = 0;
	m_unloadTime = 0;

	m_shooting = false;
	m_loading = false;
	m_unloading = false;

	m_timer = new Timer();
	m_timer->Reset();
	m_timer->Start();

	m_leftMotorController->SetInverted(true);

	m_ballyLaunchyThingy5064EXTREMEXD1337 = new Solenoid(BALLY_LAUNCHY_THINGY_5064_EXTREME_XD_1337_CHANNEL); //Needs stuff
	m_lastPressed = false;
}

Shooter::~Shooter() {
	delete m_shootButton;
	delete m_loadButton;
	delete m_unloadButton;
	delete m_ballLoadedButton;
	delete m_timer;
	delete m_leftMotorController;
	delete m_rightMotorController;
	delete m_ballyLaunchyThingy5064EXTREMEXD1337;
}

//Yo holmes - This is how you slurp up the dodgeballs
void Shooter::Load() {
	if(!BallLoaded()){
		m_ballyLaunchyThingy5064EXTREMEXD1337->Set(false);
		m_leftMotorController->Set(SHOOTER_LOAD_SPEED);
		m_rightMotorController->Set(SHOOTER_LOAD_SPEED);
		if(m_ballLoadedButton->Get()) {
			m_leftMotorController->Set(SHOOTER_IDLE_SPEED);
			m_rightMotorController->Set(SHOOTER_IDLE_SPEED);
			m_ballLoaded = true;
			m_loading = false;
		}
	}
}

void Shooter::SetAngle(float targetAngle) {
	m_targetAngle = targetAngle;
}

void Shooter::AdjustPosition(float armSpeed) {
	m_armSpeed = armSpeed;

}

//This runs every 20 ms
//Put all stuff here
void Shooter::Update() {
	if(/*m_shootButton->GetPressed()*/ m_joy2->GetTrigger()) {
		m_shooting = true;
	}
	if(m_shooting) {
		Shoot();
	}
	if(/*m_loadButton->GetPressed()*/ m_joy2->GetRawButton(2)) {
		m_loading = true;
	}
	if(m_loading) {
		Load();
	}
	if(/*m_unloadButton->GetPressed()*/ m_joy2->GetRawButton(3)) {
		m_unloading = true;
	}
	if(m_unloading) {
		Unload();
	}
	SmartDashboard::PutBoolean("Loaded: ",m_ballLoadedButton->Get());

////Test Code
//	if(m_joy2->GetTrigger()) {
//		m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
//		m_rightMotorController->Set(SHOOTER_SHOOT_SPEED);
//	} else {
//		Idle();
//	}
//
//	if(m_joy2->GetRawButton(2)) {
//		m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyShoot);
//	} else {
//		m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);
//	}

//	Debug();
}

//Hey pal - This is how you throw the ball like a pro
void Shooter::Shoot() {
	if(BallLoaded()) {
		m_timer->Start();
		m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
		m_rightMotorController->Set(SHOOTER_SHOOT_SPEED);
		//Activates pneumatic after 3 seconds of startup for the wheels
		if(m_timer->Get() >= 3) {
			m_ballyLaunchyThingy5064EXTREMEXD1337->Set(true);
			//Turns everything off
			if(m_timer->Get() >= 3.5) {
				m_ballLoaded = false;
				Idle();
				m_timer->Stop();
				m_timer->Reset();
				m_ballyLaunchyThingy5064EXTREMEXD1337->Set(false);
				m_shooting = false;
			}
		}
	}
}

//Turns off the launch motors
void Shooter::Idle() {
	m_leftMotorController->Set(SHOOTER_IDLE_SPEED);
	m_rightMotorController->Set(SHOOTER_IDLE_SPEED);
}

//Tells whether the ball is loaded
//m_ballLoadedButton is true when button is not pressed
bool Shooter::BallLoaded() {
	return m_ballLoaded;
}

//Slowly rotates the gripper wheels to eject the ball.
//Should only be called when the sensor shows the ball is loaded.
void Shooter::Unload(){
	if(BallLoaded()) {
		m_timer->Start();
		m_leftMotorController->Set(SHOOTER_UNLOAD_SPEED);
		m_rightMotorController->Set(SHOOTER_UNLOAD_SPEED);
		//Activates pneumatic after 3 seconds of startup for the wheels
		if(m_timer->Get() >= 3) {
			m_ballyLaunchyThingy5064EXTREMEXD1337->Set(true);
			//Turns everything off
			if(m_timer->Get() >= 3.5) {
				m_ballLoaded = false;
				Idle();
				m_timer->Stop();
				m_timer->Reset();
				m_ballyLaunchyThingy5064EXTREMEXD1337->Set(false);
				m_unloading = false;
			}
		}
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

void Shooter::PneumaticTest(bool status) { //Test Code
	m_ballyLaunchyThingy5064EXTREMEXD1337->Set(status);
}
