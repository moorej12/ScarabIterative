/*
 * Debounce.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: Seth1
 */
#include "WPIlib.h"
#include "Debounce.h"
#include "config.h"

Debounce::Debounce(Joystick *joy1, int button){
	m_joy = joy1;
	m_button = button;
	m_counter = 0;
	m_lastValue = false;
	m_returnedTrue = false;

}

Debounce::~Debounce() {

}

void Debounce::Init() {
	m_counter = 0;
	m_lastValue = false;
	m_returnedTrue = false;

}

bool Debounce::GetPressed() {
	bool currentReading = m_joy->GetRawButton(m_button);
	SmartDashboard::PutBoolean("Button Value", currentReading );


	//checks if there has been no change
	if(currentReading == m_lastValue) {
		if(m_counter <= 4) {
			m_counter++;
		}
	}

	//if there is no change...
	else {
		m_lastValue = currentReading;
		m_counter = 0;
	}

	//Prints various values to the console
		printf("\n m_counter: %d  currentReading: %d  m_lastValue:  %d", m_counter, currentReading, m_lastValue);

	//there has been a change so let roughly 80 ms pass... prevents sparking and false mini-reads
	if(m_counter > 4) {
		if(currentReading) { //if we have button input
			if(m_returnedTrue) { //make sure that true is only returned once
				return false;
			}
			else {
				m_returnedTrue = true;
				printf("True!");
				return true;
			}
		}
		else {
			m_returnedTrue = false;
			return false;
		}
	} else {
		m_returnedTrue = false;
		return false;
	}
}
