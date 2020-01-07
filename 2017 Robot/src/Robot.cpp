#include "WPILib.h"
#include <iostream>
#include "math.h"
#include <thread>
#include <CameraServer.h>
#include <IterativeRobot.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Joystick.h>
#include <RobotDrive.h>
#include <SampleRobot.h>
#include <Timer.h>
using namespace std;



class Robot: public IterativeRobot
{
//public:
	//Robot() {
		//robotDrive.SetExpiration(0.1);

		// Invert the left side motors
		//robotDrive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);

		// You may need to change or remove this to match your robot
		//robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	//}

	/**
	 * Runs the motors with Mecanum drive.
	 */
	//void OperatorControl() override {
		//robotDrive.SetSafetyEnabled(false);
		//while (IsOperatorControl() && IsEnabled()) {
			/* Use the joystick X axis for lateral movement, Y axis for forward
			 * movement, and Z axis for rotation. This sample does not use
			 * field-oriented drive, so the gyro input is set to zero.
			 */
			//robotDrive.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(),
			//		stick.GetZ());

			//frc::Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		//}
	//}
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "No Auto";
	const std::string autoNameCustom = "Left";
	const std::string autoNameCustom1 = "Right";
	const std::string autoNameCustom2 = "Center";
	std::string autoSelected;

	int n = 0;
	int u = 0;
	int t = 0;
	int e = 0;
	int p = 0;

	//Control System of wheels
	Joystick *l_joystick = new Joystick(1);
	Joystick *r_joystick = new Joystick(0);
	//Joystick *xbox = new Joystick(0);


	//Motor Controller Declarations
	Talon *lFMotor = new Talon(0);
	Talon *rFMotor = new Talon(1);
	Talon *lRMotor = new Talon(2);
	Talon *rRMotor = new Talon(3);
	Spark *lShooter = new Spark(4);
	Spark *rShooter = new Spark(5);
	Spark *ropeClimb = new Spark(6);




	//sound control
	//Xbox A button = Make "Caw-Caw" sound
	//Xbox Y button = Shout "but how does the robot feel"

	//Motor declarations
	double xDrive, yDrive, zDrive;
	RobotDrive *robotDrive = new RobotDrive(lFMotor,lRMotor,rFMotor,rRMotor);

	// Invert the left side motors
			//robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);

			// You may need to change or remove this to match your robot
			//robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);

	//Ultrasonic Code
	//AnalogInput *ai = new AnalogInput(7);
	//int raw = ai->GetValue();
	//double volts = ai->GetVoltage();


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


				chooser.AddDefault(autoNameDefault, autoNameDefault);
						chooser.AddObject(autoNameCustom, autoNameCustom);
						chooser.AddObject(autoNameCustom1, autoNameCustom1);
						chooser.AddObject(autoNameCustom2, autoNameCustom2);
						frc::SmartDashboard::PutData("Auto Modes", &chooser);
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
	void AutonomousInit() override {
			autoSelected = chooser.GetSelected();
			std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
			std::cout << "Auto selected: " << autoSelected << std::endl;

			if (autoSelected == autoNameCustom) {
				// Custom Auto goes here
			} else {
				// Default Auto goes here
			}
		}

	void AutonomousPeriodic()
	{

		if (n<155){
			yDrive=(-.3);
			robotDrive->MecanumDrive_Cartesian(.75*xDrive, -.75*yDrive, -.75*zDrive);
			n++;
			//Drives Robot Forward initially on auto
		}

		//if (p<15 && n>=155){p++;
			//pause
		//}

		//if (t<10 && n>=155 && p>=15){
			//zDrive=(-.3);
			//robotDrive->MecanumDrive_Cartesian(.75*xDrive, -.75*yDrive, -.75*zDrive);
			//t++;
			//Turns Robot to left
		//}

		//if (n<100){
			//pause
		//}

		//if (e<20 && t>=10 && n>=155){
			//yDrive=(-.3);
			//robotDrive->MecanumDrive_Cartesian(.75*xDrive, -.75*yDrive, -.75*zDrive);
			//e++;
			//Drives forward after turn
		//}




		//if (u<5 && e>=20 && t>=15 && n>=50){
		//	yDrive=(.5);
		//	robotDrive->MecanumDrive_Cartesian(.75*xDrive, -.75*yDrive, -.75*zDrive);
		//	u++;
			//Puts Robot in reverse shortly
		//}


		//if (n<250 && autoSelected == autoNameCustom1){
		//			yDrive=(-.5);
		//			robotDrive->MecanumDrive_Cartesian(.75*xDrive, -.75*yDrive, -.75*zDrive);
		//			n++;
		//		}

		//if (n<250 && autoSelected == autoNameCustom2){
			//		yDrive=(-.5);
			//		robotDrive->MecanumDrive_Cartesian(.75*xDrive, -.75*yDrive, -.75*zDrive);
			//		n++;
		//		}
				else {robotDrive->TankDrive(0,0,0,0);
				}

		//if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		//} else {
			//Default Auto goes here
		//}


		//pls fly
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
			zDrive= r_joystick->GetRawAxis(0);
		}

		//if( r_joystick->GetRawAxis(1)<.2|| r_joystick->GetRawAxis(1)>-.2){
			yDrive= r_joystick->GetRawAxis(1);
		}


		//xbox controls
		//xDrive= xbox->GetRawAxis(4);
		//zDrive= xbox->GetRawAxis(0);
		//yDrive= xbox->GetRawAxis(1);





		 //Shooter
		 if(r_joystick->GetRawButton(1)){
		//if(xbox->GetRawButton(1)){
		  	lShooter->Set(.75);
		 	rShooter->Set(.75);

		 }

		 else{
		 	lShooter->Set(0);
		 	rShooter->Set(0);
		 	 }

		 if(r_joystick->GetRawButton(3)){
		//if(xbox->GetRawButton(4)){

			  	ropeClimb->Set(1);
		 }

		 if(r_joystick->GetRawButton(4)){
		//if(xbox->GetRawButton(2)){
			    ropeClimb->Set(-1);

		 		 }
		 else{
		 		 	ropeClimb->Set(0);
		 	 }



		//Mechanum Drive
		//xDrive= l_joystick->GetRawAxis(0);
		//yDrive= r_joystick->GetRawAxis(0);
		//zDrive= r_joystick->GetRawAxis(1);

		robotDrive->MecanumDrive_Cartesian(xDrive*0, yDrive*.15, zDrive*0);

		  }



	 void TestPeriodic()
		 {

			 lw->Run();
		 }
	};

	START_ROBOT_CLASS(Robot)
