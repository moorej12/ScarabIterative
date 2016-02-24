/*
 * config.h
 *
 *  Created on: Jan 20, 2016
 *      Author: Jonathan
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

//Constants:

//Motor Speeds 1 = 100% 0 = 0% etc
#define SHOOTER_IDLE_SPEED 0
#define SHOOTER_SHOOT_SPEED 1
#define SHOOTER_UNLOAD_SPEED 0.4
#define SHOOTER_LOAD_SPEED -0.35
#define DRIVE_MAX_SPEED 0.8
#define DRIVE_TURNING_SENSITIVITY 0.8
#define SHOOTER_ANGLE_MOTOR_SENSITIVITY_UP 0.32
#define SHOOTER_ANGLE_MOTOR_SENSITIVITY_DOWN -0.1

//Encoder constants
#define ENCODER_SET_MAX_PERIOD .1		//The maximum period (in seconds) where the device is still considered moving
#define ENCODER_SET_MIN_RATE 10			//Sets the minimum rate before the device is considered stopped
#define ENCODER_SET_DISTANCE_PER_PULSE 0.098175		//Sets the scale factor between pulses and distance
#define ENCODER_SET_SAMPLES_PER_AVERAGE 7		//Sets the number of samples to average when determining the period


//Shooter Timing in seconds  ***NOTE: play with times to make as short and efficient as possible!***
#define SHOOTER_UNLOAD_SPOOL_TIME 0.5
#define SHOOTER_SHOOT_SPOOL_TIME 2.5
#define SHOOTER_PNEUMATIC_SPOOL_TIME 0.5

//Autonomous constants
#define AUTO_CORRECTION_SPEED 0.7
#define AUTO_ERROR_MARGIN 0.3
#define GYRO_DEADBAND 0.001
#define RAMP_ANGLE 0 //Needs to be set
#define STRETCH_CONSTANT 2000

//Shooter Emergency Stop Angles
#define BACK_TIP_ANGLE 75


//Channels:

//PWM:
#define LEFT_ARMS_MOTOR_CHANNEL 0
#define RIGHT_ARMS_MOTOR_CHANNEL 1
#define SHOOTER_RIGHT_LAUNCH_MOTOR_CHANNEL 2
#define SHOOTER_LEFT_LAUNCH_MOTOR_CHANNEL 3
#define SHOOTER_RAISE_AND_LOWER_CHANNEL 4
#define DRIVE_MOTOR_RIGHT_REAR_CHANNEL 5
#define DRIVE_MOTOR_RIGHT_FRONT_CHANNEL 6
#define DRIVE_MOTOR_LEFT_REAR_CHANNEL 7
#define DRIVE_MOTOR_LEFT_FRONT_CHANNEL 8

//Analog Channels
#define X_GYRO_CHANNEL 0
#define Y_GYRO_CHANNEL 1
#define SHOOTER_SLIDE_POTENTIOMETER 2

//Digital I/O Channels
#define ENCODER_CHANNEL_A 6
#define ENCODER_CHANNEL_B 7

#define SHOOTER_BALL_LOADED_SENSOR_CHANNEL 0
#define SHOOTER_MAX_ANGLE_SENSOR_CHANNEL 1
#define SHOOTER_MIN_ANGLE_SENSOR_CHANNEL 2
#define ULTRASONIC_SENSOR_PING_CHANNEL 3
#define ULTRASONIC_SENSOR_ECHO_CHANNEL 4
//#define ARMS_ENCODER_CHANNEL_A 3
//#define ARMS_ENCODER_CHANNEL_B 4
#define ARMS_ENCODER_INDEX_CHANNEL 5

//CAN Channels
#define BALLY_LAUNCHY_THINGY_5064_EXTREME_XD_1337_CHANNEL 0



//Buttons:
//Shooter
#define SHOOTER_SHOOT_BUTTON 1
#define SHOOTER_LOAD_BUTTON 3
#define SHOOTER_UNLOAD_BUTTON 5
#define SHOOTER_IDLE_BUTTON 4
#define SHOOTER_LOADED_BUTTON 8  //NOW ITS IN USE SUCKAS XDDD//not in use (backup for state-machine error)

#define SHOOTER_SHOOT_ANGLE_BUTTON 2
#define SHOOTER_LOW_ANGLE_BUTTON 7
#define SHOOTER_HIGH_ANGLE_BUTTON 6
#define SHOOTER_LITTLELOW_ANGLE_BUTTON 10
#define SHOOTER_LITTLEHIGH_ANGLE_BUTTON 11


//Arms


#endif /* SRC_CONFIG_H_ */
