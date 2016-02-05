#include "WPILib.h"
#include "config.h"
#include "Debounce.h"
#include "Arms.h"
#include "Drive.h"
#include "Shooter.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();

	//RobotDrive *m_drive;

	Joystick *m_joy1;
	Joystick *m_joy2;

	Drive *m_drive;

	Shooter *m_shooter;

	Compressor *m_compressor;

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
	}

	~Robot() {
		delete m_joy1;
		delete m_joy2;
		delete m_drive;
		delete m_shooter;
		delete m_compressor;
	}

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		m_compressor->Start();
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
		autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		m_drive->RobotMove(); // works
		m_shooter->Update();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
