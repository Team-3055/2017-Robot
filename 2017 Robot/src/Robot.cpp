#include "WPILib.h"
#include <iostream>
#include "math.h"
#include <thread>
#include <CameraServer.h>
#include <IterativeRobot.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
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

	//Vision Code
	static void VisionThread() {
			// Get the USB camera from CameraServer
			cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
			// Set the resolution
			camera.SetResolution(640, 480);

			// Get a CvSink. This will capture Mats from the Camera
			cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
			// Setup a CvSource. This will send images back to the Dashboard
			cs::CvSource outputStream = CameraServer::GetInstance()->
					PutVideo("Rectangle", 640, 480);

			// Mats are very memory expensive. Lets reuse this Mat.
			cv::Mat mat;

			while (true) {
				// Tell the CvSink to grab a frame from the camera and put it
				// in the source mat.  If there is an error notify the output.
				if (cvSink.GrabFrame(mat) == 0) {
					// Send the output the error.
					outputStream.NotifyError(cvSink.GetError());
					// skip the rest of the current iteration
					continue;
				}
				// Put a rectangle on the image
				rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
						cv::Scalar(255, 255, 255), 5);
				// Give the output stream a new image to display
				outputStream.PutFrame(mat);
			}
		}
	void RobotInit()
	{

		// We need to run our vision program in a separate Thread.
				// If not, our robot program will not run
				std::thread visionThread(VisionThread);
				visionThread.detach();



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
		rDrive= joystick2->GetRawAxis(1);
		lDrive= joystick->GetRawAxis(1);

		robotDrive->TankDrive(-lDrive, -rDrive);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
