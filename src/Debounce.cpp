/*
 * Debounce.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: spaet
 */
#include "WPIlib.h"
#include "Debounce.h"
#include "config.h"

Debounce::Debounce(Joystick *joy1, int button){
	m_joy = joy1;
	m_button = button;
}
bool Debounce::getPressed(){
	bool currentReading = m_joy->GetRawButton(m_button);
	if(currentReading == m_lastValue){
		m_counter++;
	}
	else{
		m_lastValue = currentReading;
		m_counter = 0;
	}
	if(m_counter > 4){
		if(currentReading){
			if(m_returnedTrue){
				return false;
			}
			else{
				m_returnedTrue = true;
				return true;
			}
		}
	} else {
		return false;
	}
}
