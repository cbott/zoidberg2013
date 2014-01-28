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
	
	//buttons
	static const int SHOOT_BUTTON = 8;
	static const int ELEVATE_BUTTON = 6;
	static const int STORE_BUTTON = 7;
	static const int PUT_DOWN_BUTTON = 5;
	
	static const float MAX_ACCEL_TIME = 0.5f;	//how many seconds we want it to take to get to max speed
	float max_delta_speed;
	//max_delta_speed = 1 / (time-to-get-to-maximum-speed * cycles-in-one-second)
	DriverStationLCD * lcd;
	Victor * left_drive;
	Victor * right_drive;
	Victor * elevation;
	Victor * left_shooter;
	Victor * right_shooter;
	Victor * pick_up;
	RobotDrive * drive;
	
	Gamepad * pilot;
	float old_left_value, old_right_value;
	
	float abs_float(float input){
		return (input < 0.0f) ? -input : input;
	}
	
	float zero(float input, float min) {
		if (abs_float(input) < min){
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
		lcd = DriverStationLCD::GetInstance(); 
		
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
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "disabled");
		lcd->UpdateLCD();
	}

	
	void TeleopPeriodic(void) {
		//drive
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "teleop");
		
		max_delta_speed = this->GetPeriod() / MAX_ACCEL_TIME;
		
		float left_value = -zero(pilot->GetLeftY(), 0.05f);
		float right_value = zero(pilot->GetRightX(), 0.05f);
		
		float delta_left = left_value - old_left_value;
		float delta_right = right_value - old_right_value;
		if (delta_left > max_delta_speed && delta_left > 0.0f){
			left_value = old_left_value + max_delta_speed;
		} else if (delta_left < -max_delta_speed && delta_left < 0.0f){
			left_value = old_left_value - max_delta_speed;
		} 
		//if neither of these is the case, |delta_left| is less than the max 
		//and we can just use the left_value without modification.
		
		if (delta_right > max_delta_speed && delta_right > 0.0f){
			right_value = old_right_value + max_delta_speed;
		} else if (delta_right < -max_delta_speed && delta_right < 0.0f){
			right_value = old_right_value - max_delta_speed;
		}
		
		lcd->PrintfLine(DriverStationLCD::kUser_Line2, "%f %f", left_value, right_value);
		
		drive->ArcadeDrive(left_value, right_value);
		old_left_value = left_value;
		old_right_value = right_value;
		
		/*
		float left_value = -(zero(pilot->GetLeftY(), 0.05f))/1.5;
		float right_value = -(zero(pilot->GetRightY(), 0.05f))/1.5;
		drive->TankDrive(left_value, right_value);
		*/
		//pickup and elevate
		bool elevating = pilot->GetNumberedButton(ELEVATE_BUTTON);
		if (elevating){
			elevation->Set(.5);
			pick_up->Set(1.0);
		}else{
			elevation->Set(0);
			pick_up->Set(0);
		}
		
		//shooting
		bool shooting = pilot->GetNumberedButton(SHOOT_BUTTON);
		if (shooting){
			left_shooter->Set(-1);
			right_shooter->Set(-1);
		}else{
			left_shooter->Set(0.000001);
			right_shooter->Set(0.000001);
		}
		//Storing
		bool pushingdown = pilot->GetNumberedButton(STORE_BUTTON);
		if (pushingdown){
			elevation->Set(-1);
			left_shooter->Set(0.5);
			right_shooter->Set(0.5);
			pick_up->Set(1);
		}
		
		//reversing the pickup motor
		bool reversing = pilot->GetNumberedButton(PUT_DOWN_BUTTON);
		if (reversing){
			pick_up->Set(-0.5);
		}
		
		lcd->UpdateLCD();
	}



};

START_ROBOT_CLASS(ReboundRumbleRobot);
