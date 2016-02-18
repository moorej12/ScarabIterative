/*
 * Arms.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: Jonathan
 */

#include "Arms.h"


Arms::Arms() {
	m_armAngle = 0;
	m_armsPotentiometer = new AnalogPotentiometer(SHOOTER_SLIDE_POTENTIOMETER, 60, 0);
	m_leftArmsPIDController = new PIDController(0.1, 0.01, 0, m_armsPotentiometer, m_leftArmsMotorController);
	m_rightArmsPIDController = new PIDController(0.1, 0.01, 0, m_armsPotentiometer, m_rightArmsMotorController);
	m_leftArmsMotorController = new VictorSP(LEFT_ARMS_MOTOR_CHANNEL);
	m_rightArmsMotorController = new VictorSP(RIGHT_ARMS_MOTOR_CHANNEL);
}
Arms::~Arms() {
	delete m_rightArmsMotorController;
	delete m_leftArmsMotorController;
}
//Sets arm position based on value in degrees
void Arms::SetPosition(float m_setArmAngle) {

}

//Allows driver to move arms manually
void Arms::Move() {

}

//Gets the angle of the arms from the potentiometer
float Arms::GetPosition() {
	return m_armAngle;
}

void Arms::Init() {
	//Resets all values to zero
	m_armAngle = 0;
}

	//may not even be useful     m_angleMotorController->Set(m_joy2->GetY());
