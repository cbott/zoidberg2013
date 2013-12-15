#include "WPILib.h"
#include "Gamepad.h"
#include <cmath>

class ReboundRumbleRobot : public IterativeRobot
{
	static const int LEFT_DRIVE_PWM = 1;
	static const int RIGHT_DRIVE_PWM = 2;
	static const int RIGHT_SHOOTER_PWM = 3;
	static const int LEFT_SHOOTER_PWM = 4;
	static const int ELEVATION_PWM = 5;
	static const int PICK_UP_PWM = 6;
	
	Victor * left_drive;
	Victor * right_drive;
	Victor * elevation;
	Victor * left_shooter;
	Victor * right_shooter;
	Victor * pick_up;
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
		elevation = new Victor(ELEVATION_PWM);
		left_shooter = new Victor(LEFT_SHOOTER_PWM);
		right_shooter = new Victor(RIGHT_SHOOTER_PWM);
		pick_up = new Victor (PICK_UP_PWM);
		
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
		float left_value = (zero(pilot->GetLeftY(), 0.05f))/2;
		float right_value = (zero(pilot->GetRightX(), 0.05f))/2;
		
		drive->ArcadeDrive(left_value, right_value);
		
		bool elevating = pilot->GetNumberedButton(2);
		if (elevating){
			elevation->Set(.5);
		}else{
			elevation->Set(0);
		}
		
		bool shooting = pilot->GetNumberedButton(8);
		if (shooting){
			left_shooter->Set(-1);
			right_shooter->Set(-1);
		}else{
			left_shooter->Set(0.000001);
			right_shooter->Set(0.000001);
		}
		
		bool pickingup = pilot->GetNumberedButton(3);
		if (pickingup){
			pick_up->Set(1);
		}else{
			pick_up->Set(0.000001);
		}
		
		bool pushingdown = pilot->GetNumberedButton(7);
		if (pushingdown){
			elevation->Set(-1);
			left_shooter->Set(1);
			right_shooter->Set(1);
			pick_up->Set(1);
		}
	}



};

START_ROBOT_CLASS(ReboundRumbleRobot);
