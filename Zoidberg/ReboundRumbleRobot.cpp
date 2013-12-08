#include "WPILib.h"
#include "Gamepad.h"
#include <cmath>

class ReboundRumbleRobot : public IterativeRobot
{
	static const int LEFT_DRIVE_PWM = 1;
	static const int RIGHT_DRIVE_PWM = 2;
				
	Victor * left_drive;
	Victor * right_drive;
	RobotDrive * drive;
	
	Gamepad * pilot;
	
	float zero(float input, float min) {
		if (abs(input) < min){
			return 0.0f;
		} else {
			return input;
		}
	}
	
	
public:

	ReboundRumbleRobot(void)	{
		
	}
	
	
	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		left_drive = new Victor(LEFT_DRIVE_PWM);
		right_drive = new Victor(RIGHT_DRIVE_PWM);
		drive = new RobotDrive(left_drive,right_drive);
		//the right side of the drive train is reversed
		drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		
		pilot = new Gamepad(1); //we're using the logitech gamepad for this
	}
	
	void DisabledInit(void) {

	}

	void AutonomousInit(void) {

	}

	void TeleopInit(void) {

	}

	/********************************** Periodic Routines *************************************/
	
	void DisabledPeriodic(void)  {

	}

	void AutonomousPeriodic(void) {

	}

	
	void TeleopPeriodic(void) {
		float left_value = zero(pilot->GetLeftY(), 0.05f);
		float right_value = zero(pilot->GetRightY(), 0.05f);
		
		drive->TankDrive(left_value, right_value);
				
	}



};

START_ROBOT_CLASS(ReboundRumbleRobot);
