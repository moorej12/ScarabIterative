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
	m_idleButton = new Debounce(m_joy2, 4);
	m_loadedButton = new Debounce(m_joy2, 5);

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
	if(!BallLoaded()){ // if there is no ball in the robot do all the below
		m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);//calls the function Set which sets the solenoid output to false
		m_leftMotorController->Set(SHOOTER_LOAD_SPEED);//calls the function Set which sets the PWM value
		m_rightMotorController->Set(SHOOTER_LOAD_SPEED);//calls the function Set which sets the PWM value
		if(!m_ballLoadedButton->Get()) { //if m_ballLoadedButton is pressed then do what's in between the squiggly brackets
			m_leftMotorController->Set(SHOOTER_IDLE_SPEED);//turns motor off
			m_rightMotorController->Set(SHOOTER_IDLE_SPEED);//turns motor off
			m_ballLoaded = true;//sets m_ballLoaded to true because there is a ball in the robot
			m_loading = false;//sets m_loading to false because we are done loading
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
	//Stops all other functions
	if(/*m_idleButton->GetPressed()*/ m_joy2->GetRawButton(4)) {
		m_shooting = false;
		m_loading = false;
		m_unloading = false;
		Idle();
	}
	if(/*m_loadedButton->GetPressed()*/ m_joy2->GetRawButton(5)) {
		m_ballLoaded = true;
	}
	if(/*m_shootButton->GetPressed()*/ BallLoaded() && m_joy2->GetTrigger()) {
		m_shooting = true;
	}
	if(m_shooting) {
		Shoot();
	}
	if(/*m_loadButton->GetPressed()*/ (!BallLoaded()) && m_joy2->GetRawButton(2)) {
		m_loading = true;
	}
	if(m_loading) {
		Load();
	}
	if(/*m_unloadButton->GetPressed()*/ BallLoaded() && m_joy2->GetRawButton(3)) {
		m_unloading = true;
	}
	if(m_unloading) {
		Unload();
	}
	SmartDashboard::PutBoolean("Ball Button: ",m_ballLoadedButton->Get());
	SmartDashboard::PutBoolean("Ball Loaded: ",m_ballLoaded);
	SmartDashboard::PutBoolean("Loading: ",m_loading);
	SmartDashboard::PutBoolean("Shooting: ",m_shooting);
	SmartDashboard::PutBoolean("Unloading: ",m_unloading);


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
		if(m_timer->Get() >= 2.5) {
			m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyShoot);
			//Turns everything off
			if(m_timer->Get() >= 3) {
				m_ballLoaded = false;
				Idle();
				m_timer->Stop();
				m_timer->Reset();
				m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);
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
		if(m_timer->Get() >= 1) {
			m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyShoot);
			//Turns everything off
			if(m_timer->Get() >= 1.5) {
				m_ballLoaded = false;
				Idle();
				m_timer->Stop();
				m_timer->Reset();
				m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);
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

void Shooter::Init(){
//resets all values to zero
	m_targetAngle = 0;
	m_armSpeed = 0;
	m_ballLoaded = false;
	m_shotTime = 0;
	m_loadTime = 0;
	m_unloadTime = 0;
	m_shooting = false;
	m_loading = false;
	m_unloading = false;
	m_lastPressed = false;

}
