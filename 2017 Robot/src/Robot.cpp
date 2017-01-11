#include "WPILib.h"
#include <iostream>
#include "math.h"
using namespace std;

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	//SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	//Control System
	Joystick *joystick = new Joystick(0);
	Joystick *joystick2 = new Joystick(1);

	//Motor Controller Declarations
	Talon *rDMotor = new Talon(0);
	Spark *lDMotor = new Spark(1);

	//Joystick Key Declarations
	//

	//Ultrasonic Add



	//Motor declarations
	double lDrive, rDrive;
	RobotDrive *robotDrive = new RobotDrive(lDMotor,rDMotor);

	void RobotInit()
	{
		//chooser = new SendableChooser();
		//chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		//chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		//SmartDashboard::PutData("Auto Modes", chooser);
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
		//autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		//std::cout << "Auto selected: " << autoSelected << std::endl;

		//if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		//} else {
			//Default Auto goes here
		//}
	}

	void AutonomousPeriodic()
	{
		//if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		//} else {
			//Default Auto goes here
		//}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		 //Tank Drive
		lDrive= joystick->GetRawAxis(1);
		rDrive= joystick2->GetRawAxis(1);
		robotDrive->TankDrive(-lDrive, -rDrive);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
