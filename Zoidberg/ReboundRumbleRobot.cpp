#include "WPILib.h"
#include "Gamepad.h"

class ReboundRumbleRobot : public IterativeRobot
{
	static const int LEFT_DRIVE_PWM = 1; //TODO: officially figure this out
	static const int RIGHT_DRIVE_PWM = 2; //TODO: officially figure this out
				
	Victor * left_drive;
	Victor * right_drive;
	RobotDrive * drive;
	
	Gamepad * pilot;
	
public:

	ReboundRumbleRobot(void)	{
		
	}
	
	
	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		left_drive = new Victor(LEFT_DRIVE_PWM);
		right_drive = new Victor(RIGHT_DRIVE_PWM);
		drive = new RobotDrive(left_drive,right_drive);
		
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
		float left_value = pilot->GetLeftY();
		float right_value = pilot->GetRightY();
		
		drive->TankDrive(left_value, right_value);
				
	}



};

START_ROBOT_CLASS(ReboundRumbleRobot);
