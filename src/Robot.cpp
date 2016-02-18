#include "WPILib.h"
#include "config.h"
#include "Debounce.h"
#include "Arms.h"
#include "Drive.h"
#include "Shooter.h"
#include "Autonomous.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();

	//RobotDrive *m_drive;

	Joystick *m_joy1;
	Joystick *m_joy2;

	Drive *m_drive;

	Shooter *m_shooter;
	Autonomous *m_autonomous;
	Arms *m_arms;

	Compressor *m_compressor;
	Ultrasonic *m_ultrasonicSensor;

	AnalogGyro *m_xAxisGyro;
	AnalogGyro *m_yAxisGyro;

	Encoder *m_rightSideEncoder;
	Encoder *m_leftSideEncoder;

	Timer *m_timer;


	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;


public:

	Robot() {
		m_joy1 = new Joystick(0);
		m_joy2 = new Joystick(1);
		m_drive = new Drive(m_joy1);

		m_shooter = new Shooter(m_joy2);
		m_compressor = new Compressor(0);
		m_compressor->SetClosedLoopControl(true);

		m_ultrasonicSensor = new Ultrasonic(3);

		m_xAxisGyro = new AnalogGyro(X_GYRO_CHANNEL);
//		m_yAxisGyro = new AnalogGyro(Y_GYRO_CHANNEL);
		m_yAxisGyro = NULL;
		m_timer = new Timer();
		m_rightSideEncoder = new Encoder(ENCODER_RIGHT_SIDE_CHANNEL_A, ENCODER_RIGHT_SIDE_CHANNEL_B);
		m_leftSideEncoder = new Encoder(ENCODER_LEFT_SIDE_CHANNEL_A, ENCODER_LEFT_SIDE_CHANNEL_B);
		m_arms = new Arms();
		m_autonomous = new Autonomous(m_drive, m_shooter, m_arms, m_xAxisGyro, m_yAxisGyro, m_rightSideEncoder, m_leftSideEncoder, m_ultrasonicSensor);


	}

	~Robot() {
		delete m_joy1;
		delete m_joy2;
		delete m_drive;
		delete m_shooter;
		delete m_compressor;
		delete m_ultrasonicSensor;
		delete m_xAxisGyro;
		delete m_yAxisGyro;
		delete m_rightSideEncoder;
		delete m_leftSideEncoder;
		delete m_autonomous;
		delete m_arms;
	}

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);

		m_compressor->Start();

		m_rightSideEncoder->SetMaxPeriod(ENCODER_SET_MAX_PERIOD);
		m_rightSideEncoder->SetMinRate(ENCODER_SET_MIN_RATE);
		m_rightSideEncoder->SetDistancePerPulse(ENCODER_SET_DISTANCE_PER_PULSE);
		m_rightSideEncoder->SetSamplesToAverage(ENCODER_SET_SAMPLES_PER_AVERAGE);

		m_leftSideEncoder->SetMaxPeriod(ENCODER_SET_MAX_PERIOD);
		m_leftSideEncoder->SetMinRate(ENCODER_SET_MIN_RATE);
		m_leftSideEncoder->SetDistancePerPulse(ENCODER_SET_DISTANCE_PER_PULSE);
		m_leftSideEncoder->SetSamplesToAverage(ENCODER_SET_SAMPLES_PER_AVERAGE);
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		m_autonomous->AutonomousInit();
	}

	void AutonomousPeriodic()
	{
		m_autonomous->BeginDrive();


	}

	void TeleopInit()
	{
		//put all init functions here
	}

	void TeleopPeriodic()
	{
//		m_drive->ManualRobotDrive();
//		m_shooter->Update();
	}

	void TestPeriodic()
	{
		lw->Run();
	}


};
START_ROBOT_CLASS(Robot)

