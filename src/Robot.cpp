#include "WPILib.h"
#include "config.h"
#include "Debounce.h"
#include "Arms.h"
#include "Drive.h"
#include "Shooter.h"
#include "Autonomous.h"
#include "SendableChooserInt.h"

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

	Encoder *m_encoder;

	SendableChooserInt *m_autoChooser;
	Timer *m_timer;

	int m_autoMode;

//	SendableChooser *chooser;
//	const std::string autoNameDefault = "Default";
//	const std::string autoNameCustom = "My Auto";
//	std::string autoSelected;


public:

	Robot() {
		m_joy1 = new Joystick(0);
		m_joy2 = new Joystick(1);
		m_xAxisGyro = new AnalogGyro(X_GYRO_CHANNEL);
		m_yAxisGyro = new AnalogGyro(Y_GYRO_CHANNEL);

		m_shooter = new Shooter(m_joy2);
		m_compressor = new Compressor(0);
		m_compressor->SetClosedLoopControl(true);
	    m_autoChooser = new SendableChooserInt();
		m_autoMode = -1;
		m_arms = new Arms();

		m_timer = new Timer();
		m_encoder = new Encoder(ENCODER_CHANNEL_A, ENCODER_CHANNEL_B, false, Encoder::EncodingType::k2X);
		m_arms = new Arms();
		m_drive = new Drive(m_joy1, m_xAxisGyro, m_yAxisGyro);
		m_autonomous = new Autonomous(m_drive, m_shooter, m_arms, m_xAxisGyro, m_yAxisGyro, m_encoder);

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
		delete m_encoder;
		delete m_autonomous;
		delete m_arms;
	}

	void RobotInit()
	{
	    m_autoChooser->AddDefault("Default", -1);
	    m_autoChooser->AddObject("Rough Terrain", ROUGH_TERRAIN);
	    m_autoChooser->AddObject("Portcullis", PORTCULLIS);
	    m_autoChooser->AddObject("Rock Wall", ROCK_WALL);
	    m_autoChooser->AddObject("Moat", MOAT);
	    m_autoChooser->AddObject("Teeter Totters", TEETER_TOTTERS);
	    m_autoChooser->AddObject("Ramparts", RAMPARTS);
	    m_autoChooser->AddObject("Low Bar", LOW_BAR);
	    SmartDashboard::PutData("Autonomous Selector", m_autoChooser);
	    m_autoMode = m_autoChooser->GetSelected();
	    SmartDashboard::PutNumber("Autonomous Mode: ", m_autoMode);

		m_compressor->Start();

		m_encoder->SetMaxPeriod(ENCODER_SET_MAX_PERIOD);
		m_encoder->SetMinRate(ENCODER_SET_MIN_RATE);
		m_encoder->SetDistancePerPulse(ENCODER_SET_DISTANCE_PER_PULSE);
		m_encoder->SetSamplesToAverage(ENCODER_SET_SAMPLES_PER_AVERAGE);

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
		m_autonomous->AutonomousInit(m_autoMode);
	}

	void AutonomousPeriodic()
	{
//		m_autonomous->BeginDrive();
		m_autonomous->Update();
	}

	void TeleopInit()
	{
		//put all teleop-relevant init functions here
		m_drive->DriveInit();

	}

	void TeleopPeriodic()
	{
		m_drive->EmergencyResponseDrive();
//		m_drive->ManualRobotDrive();
//		m_shooter->Update();
	}

	void TestPeriodic()
	{
		lw->Run();
	}


};
START_ROBOT_CLASS(Robot)

