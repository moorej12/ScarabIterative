/*
 * Arms.cpp
 *
 *  Created on: Jan 19, 2016
 *      Author: Jonathan
 */
#include "WPIlib.h"
#include "Arms.h"
#include "config.h"

Arms::Arms() {
	m_leftArmsMotor = new VictorSP(LEFT_ARMS_MOTOR_CHANNEL);
	m_rightArmsMotor = new VictorSP(RIGHT_ARMS_MOTOR_CHANNEL);
	m_armAngle = 0;
}
Arms::~Arms() {
	delete m_leftArmsMotor;
	delete m_rightArmsMotor;
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
