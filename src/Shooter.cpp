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
	m_angleMotorController = new VictorSP(SHOOTER_RAISE_AND_LOWER_CHANNEL);
	m_shooterPotentiometer = new AnalogPotentiometer(SHOOTER_SLIDE_POTENTIOMETER, 70, 0);
	m_shooterPIDController = new PIDController(0.1, 0.01, 0, m_shooterPotentiometer, m_angleMotorController);

	m_targetAngle = 0;
	m_ballLoadedButton = new DigitalInput(SHOOTER_BALL_LOADED_SENSOR_CHANNEL);
	m_maxAngleButton = new DigitalInput(SHOOTER_MAX_ANGLE_SENSOR_CHANNEL);
	m_minAngleButton = new DigitalInput(SHOOTER_MIN_ANGLE_SENSOR_CHANNEL);

	m_ballLoaded = false;
	m_status = kShooterUNINITIALIZED;

	m_shootButton = new Debounce(m_joy2, SHOOTER_SHOOT_BUTTON);
	m_loadButton = new Debounce(m_joy2, SHOOTER_LOAD_BUTTON);
	m_unloadButton = new Debounce(m_joy2, SHOOTER_UNLOAD_BUTTON);
	m_idleButton = new Debounce(m_joy2, SHOOTER_IDLE_BUTTON);
	m_loadedButton = new Debounce(m_joy2, SHOOTER_LOADED_BUTTON);
	m_shootAngleButton = new Debounce(m_joy2, SHOOTER_SHOOT_ANGLE_BUTTON);
	m_shooterLowAngleButton = new Debounce(m_joy2, SHOOTER_LOW_ANGLE_BUTTON);
	m_shooterHighAngleButton = new Debounce(m_joy2, SHOOTER_HIGH_ANGLE_BUTTON);
	m_shooterLittleLowAngleButton = new Debounce(m_joy2, SHOOTER_LITTLELOW_ANGLE_BUTTON);
	m_shooterLittleHighAngleButton = new Debounce(m_joy2, SHOOTER_LITTLEHIGH_ANGLE_BUTTON);

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
	delete m_angleMotorController;
	delete m_ballyLaunchyThingy5064EXTREMEXD1337;
	delete m_shooterPotentiometer;
	delete m_maxAngleButton;
	delete m_minAngleButton;
	delete m_shooterPIDController;
	delete m_loadedButton;
	delete m_idleButton;
	delete m_shootAngleButton;
	delete m_shooterLowAngleButton;
	delete m_shooterHighAngleButton;
	delete m_shooterLittleLowAngleButton;
	delete m_shooterLittleHighAngleButton;
}

//This runs every 20 ms
//Put all stuff here
void Shooter::Update() {
	//High Quality 4k 144 FPS Thigns and st0ff
	StateMachine();
//	ShooterAngle();

	SmartDashboard::PutBoolean("Ball Button: ",m_ballLoadedButton->Get());
	SmartDashboard::PutBoolean("Ball Loaded: ",m_ballLoaded);
	SmartDashboard::PutNumber("State: ", m_status);
	SmartDashboard::PutNumber("Setpoint: ", m_shooterPIDController->GetSetpoint());
	SmartDashboard::PutNumber("Potentiometer: ", m_shooterPotentiometer->Get());

	//Test Code:
	if(!m_maxAngleButton->Get() && m_joy2->GetY() > 0) {
		m_angleMotorController->Set(m_joy2->GetY() * 0);
	}
	else {
		m_angleMotorController->Set(m_joy2->GetY() * SHOOTER_ANGLE_MOTOR_SENSITIVITY_UP);
	}

//	if(m_loadedButton->GetPressed()) {
//		m_ballLoaded = true;
//	}

//Replaced by state machine
//	//Stops all other functions
//	if(m_idleButton->GetPressed()) {
//		m_shooting = false;
//		m_loading = false;
//		m_unloading = false;
//		Idle();
//	}
//
//	if(m_shootButton->GetPressed() && BallLoaded()) {
//		m_shooting = true;
//	}
//	if(m_shooting) {
//		Shoot();
//	}
//	if(m_loadButton->GetPressed() && (!BallLoaded())) {
//		m_loading = true;
//	}
//	if(m_loading) {
//		Load();
//	}
//	if(m_unloadButton->GetPressed() && BallLoaded()) {
//		m_unloading = true;
//	}
//	if(m_unloading) {
//		Unload();
//	}

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


void Shooter::StateMachine() {
	switch(m_status) {

			case kShooterUNINITIALIZED:
				if(BallLoaded()) {
					m_status = kShooterLOADED;
				}
				else {
					m_status = kShooterIDLE;
				}
			break;


			case kShooterIDLE:
				Idle();
				if(m_loadButton->GetPressed()) {
					m_status = kShooterLOADING;
				}
				else if(m_loadedButton->GetPressed()) {
					m_status = kShooterLOADED;
				}
			break;


			case kShooterLOADING:
				m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);//calls the function Set which sets the solenoid output to false
				m_leftMotorController->Set(SHOOTER_LOAD_SPEED);//calls the function Set which sets the PWM value
				m_rightMotorController->Set(SHOOTER_LOAD_SPEED);//calls the function Set which sets the PWM value

				if(m_loadButton->GetPressed()) {
					m_status = kShooterIDLE;
				}
				else if(m_idleButton->GetPressed()) {
					m_status = kShooterIDLE;
				}
				else if(!m_ballLoadedButton->Get()) { //if m_ballLoadedButton is pressed then do what's in between the squiggly brackets
					m_status = kShooterLOADED;
				}
			break;


			case kShooterLOADED:
				Idle(); //calls function to set the motors to idle speed
				m_ballLoaded = true;//sets m_ballLoaded to true because there is a ball in the robot
				if(m_unloadButton->GetPressed()) {
					m_timer->Reset();
					m_timer->Start();
					m_status = kShooterUNLOADING;
				}
				else if(m_shootButton->GetPressed()) {
					m_timer->Reset();
					m_timer->Start();
					m_status = kShooterSHOOTING;
				}
			break;


			case kShooterUNLOADING:
				m_leftMotorController->Set(SHOOTER_UNLOAD_SPEED);
				m_rightMotorController->Set(SHOOTER_UNLOAD_SPEED);
				/*Allows operator to press unloadButton again after 0.5
				seconds to activate pneumatic and go to UNLOAD */
				if(m_timer->Get() >= SHOOTER_UNLOAD_SPOOL_TIME) {
					if(m_unloadButton->GetPressed()) {
						m_timer->Stop();
						m_timer->Reset();
						m_timer->Start();
						m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyShoot);
						m_status = kShooterUNLOAD;
					}
				} else if (m_idleButton->GetPressed()) {
					m_timer->Stop();
					m_timer->Reset();
					m_timer->Start();
					m_status = kShooterLOADED;
				}
			break;


			case kShooterSHOOTING:
				m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
				m_rightMotorController->Set(SHOOTER_SHOOT_SPEED);
				/*Allows operator to press shootButton again after 2.5
				seconds to activate pneumatic and go to SHOOT */
				if(m_timer->Get() >= SHOOTER_SHOOT_SPOOL_TIME) {
					if(m_shootButton->GetPressed()) {
						m_timer->Stop();
						m_timer->Reset();
						m_timer->Start();
						m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyShoot);
						m_status = kShooterSHOOT;
					}
				} else if (m_idleButton->GetPressed()) {
					m_timer->Stop();
					m_timer->Reset();
					m_timer->Start();
					m_status = kShooterLOADED;
				}
			break;


			case kShooterUNLOAD:
				if(m_timer->Get() >= SHOOTER_PNEUMATIC_SPOOL_TIME) {
					m_ballLoaded = false;
					Idle();
					m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);
					m_timer->Start();
					m_timer->Reset();
					m_timer->Stop();
					m_status = kShooterIDLE;
				}
			break;


			case kShooterSHOOT:
				if(m_timer->Get() >= SHOOTER_PNEUMATIC_SPOOL_TIME) {
					m_ballLoaded = false;
					Idle();
					m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);
					m_timer->Start();
					m_timer->Reset();
					m_timer->Stop();
					m_status = kShooterIDLE;
				}
			break;
		}
}

void Shooter::ShooterAngle(/*float targetAngle*/) {
//	m_targetAngle = targetAngle;
//	m_shooterPIDController->SetSetpoint((m_joy2->GetY() + 1) * 30);
	m_shooterPIDController->Enable();
	m_shooterPIDController->SetOutputRange(SHOOTER_ANGLE_MOTOR_SENSITIVITY_DOWN, SHOOTER_ANGLE_MOTOR_SENSITIVITY_UP);
	if(m_shootAngleButton->GetPressed()) {
		m_shooterPIDController->SetSetpoint(45);
	}
	if(m_shooterLowAngleButton->GetPressed()) {
		m_shooterPIDController->SetSetpoint(5);
	}
	if(m_shooterHighAngleButton->GetPressed()) {
		m_shooterPIDController->SetSetpoint(65);
	}
	if(m_shooterLittleLowAngleButton->GetPressed()) {
		m_shooterPIDController->SetSetpoint(15);
	}
	if(m_shooterLittleHighAngleButton->GetPressed()) {
		m_shooterPIDController->SetSetpoint(55);
	}

	if(!m_maxAngleButton->Get()) {
		m_shooterPIDController->SetSetpoint(60);
		m_shooterPIDController->SetOutputRange(SHOOTER_ANGLE_MOTOR_SENSITIVITY_DOWN, 0);
	}

	if(!m_minAngleButton->Get()) {
		m_shooterPIDController->SetSetpoint(10);
		m_shooterPIDController->SetOutputRange(0, SHOOTER_ANGLE_MOTOR_SENSITIVITY_UP);
	}

	if(m_minAngleButton && m_maxAngleButton) {
		m_shooterPIDController->SetOutputRange(SHOOTER_ANGLE_MOTOR_SENSITIVITY_DOWN, SHOOTER_ANGLE_MOTOR_SENSITIVITY_UP);
	}

	//may not even be useful     m_angleMotorController->Set(m_joy2->GetY());
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

bool Shooter::MaxHeightSensor(){
		return m_maxAngleButton->Get();
}
//Old Code
//void Shooter::Shoot() {
//	if(BallLoaded()) {
//		m_timer->Start();
//		m_leftMotorController->Set(SHOOTER_SHOOT_SPEED);
//		m_rightMotorController->Set(SHOOTER_SHOOT_SPEED);
//		//Activates pneumatic after 3 seconds of startup for the wheels
//		if(m_timer->Get() >= 2.5) {
//			m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyShoot);
//			//Turns everything off
//			if(m_timer->Get() >= 3) {
//				m_ballLoaded = false;
//				Idle();
//				m_timer->Stop();
//				m_timer->Reset();
//				m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);
//			}
//		}
//	}
//}

//Old Code
//void Shooter::Load() {
//	if(!BallLoaded()){ // if there is no ball in the robot do all the below
//		m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);//calls the function Set which sets the solenoid output to false
//		m_leftMotorController->Set(SHOOTER_LOAD_SPEED);//calls the function Set which sets the PWM value
//		m_rightMotorController->Set(SHOOTER_LOAD_SPEED);//calls the function Set which sets the PWM value
//		if(!m_ballLoadedButton->Get()) { //if m_ballLoadedButton is pressed then do what's in between the squiggly brackets
//			m_leftMotorController->Set(SHOOTER_IDLE_SPEED);//turns motor off
//			m_rightMotorController->Set(SHOOTER_IDLE_SPEED);//turns motor off
//			m_ballLoaded = true;//sets m_ballLoaded to true because there is a ball in the robot
//		}
//	}
//}

//Slowly rotates the gripper wheels to eject the ball.
//Should only be called when the sensor shows the ball is loaded.
//Old Code
//void Shooter::Unload(){
//	if(BallLoaded()) {
//		m_timer->Start();
//		m_leftMotorController->Set(SHOOTER_UNLOAD_SPEED);
//		m_rightMotorController->Set(SHOOTER_UNLOAD_SPEED);
//		//Activates pneumatic after 3 seconds of startup for the wheels
//		if(m_timer->Get() >= 1) {
//			m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyShoot);
//			//Turns everything off
//			if(m_timer->Get() >= 1.5) {
//				m_ballLoaded = false;
//				Idle();
//				m_timer->Stop();
//				m_timer->Reset();
//				m_ballyLaunchyThingy5064EXTREMEXD1337->Set(ballyLaunchyRetract);
//			}
//		}
//	}
//}

//returns a bool representing whether or not the shooter is able to load,
//based on if the piston is retracted and the ball is loaded.
//bool Shooter::CanLoad(/*not implemented*/){
//	//To return true:
//	//-Piston Extended == False
//	//-Touch Sensor == False
//	return false;
//}

//Returns a bool representing whether or not the shooter is able to shoot,
//based on whether the ball is loaded.
//bool Shooter::CanShoot(/*not implemented*/){
////To return true:
////Touch Sensor == True
//	return false;
//}

//void Shooter::Debug() {
//	//An example of how to use the SmartDashboard...
//	SmartDashboard::PutNumber("Timer Value", m_timer->Get());
//}

//void Shooter::PneumaticTest(bool status) { //Test Code
//	m_ballyLaunchyThingy5064EXTREMEXD1337->Set(status);
//}

//void Shooter::Init(){
////resets all values to zero
//	m_targetAngle = 0;
//	m_ballLoaded = false;
//	m_lastPressed = false;
//
//}
