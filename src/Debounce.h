/*
 * Debounce.h
 *
 *  Created on: Jan 30, 2016
 *      Author: spaet
 */

#ifndef SRC_DEBOUNCE_H_
#define SRC_DEBOUNCE_H_

class Debounce {
	private:
		Joystick *m_joy;
		int m_button;
		bool m_lastValue;
		int	m_counter;
		bool m_returnedTrue;
	public:
		Debounce(Joystick *joy1, int button);
		bool GetPressed();
	};
#endif /* SRC_DEBOUNCE_H_ */
