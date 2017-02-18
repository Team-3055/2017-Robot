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



	//Control System of wheels
	Joystick *l_joystick = new Joystick(0);
	Joystick *r_joystick = new Joystick(1);


	//Motor Controller Declarations
	Talon *lFMotor = new Talon(0);
	Talon *rFMotor = new Talon(1);
	Talon *lRMotor = new Talon(2);
	Talon *rRMotor = new Talon(3);
	Spark *lShooter = new Spark(4);
	Spark *rShooter = new Spark(5);
	Spark *ropeClimb = new Spark(6);




	//sound control
	//Xbox x button = Make "Caw-Caw" sound

	//Motor declarations
	double xDrive, yDrive, zDrive;
	RobotDrive *robotDrive = new RobotDrive(lFMotor,lRMotor,rFMotor,rRMotor);

	//Ultrasonic Code
	AnalogInput *ai = new AnalogInput(7);
	int raw = ai->GetValue();
	double volts = ai->GetVoltage();
	//ai->SetAccumulatorInitialValue(0);
	//ai->SetAccumulatorCenter(0);
	//ai->SetAccumulatorDeadband(10);


	//Vision Code
	static void VisionThread()
	{
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
				rectangle(mat, cv::Point(240, 160), cv::Point(400, 320),
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


		if( l_joystick->GetRawAxis(0)<.2|| l_joystick->GetRawAxis(0)>-.2){
			xDrive= l_joystick->GetRawAxis(0);
		}


		if( r_joystick->GetRawAxis(0)<.2|| r_joystick->GetRawAxis(0)>-.2){
			yDrive= r_joystick->GetRawAxis(0);
		}

		if( r_joystick->GetRawAxis(1)<.2|| r_joystick->GetRawAxis(1)>-.2){
			zDrive= r_joystick->GetRawAxis(1);
		}



		 //Shooter
		 if(r_joystick->GetRawButton(1)){
		  	lShooter->Set(.75);
		 	rShooter->Set(.75);

		 }
		 else{
		 	lShooter->Set(0);
		 	rShooter->Set(0);
		 	 }

		 if(r_joystick->GetRawButton(3)){
			  	ropeClimb->Set(1);
		 }

		 if(r_joystick->GetRawButton(4)){
			    ropeClimb->Set(-1);

		 		 }
		 else{
		 		 	ropeClimb->Set(0);
		 	 }



		//Mechanum Drive
		//xDrive= l_joystick->GetRawAxis(0);
		//yDrive= r_joystick->GetRawAxis(0);
		//zDrive= r_joystick->GetRawAxis(1);

		robotDrive->MecanumDrive_Cartesian(.75*xDrive, -.75*yDrive, -.75*zDrive);

		  }



	 void TestPeriodic()
		 {

			 lw->Run();
		 }
	};

	START_ROBOT_CLASS(Robot)
