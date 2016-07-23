#ifndef Chaos2014
#define Chaos2014

#include "WPILib.h"

#define PASS 0.080
#define TRUSS 0.15
#define LAUNCH 0.30

#define DEMO 0.10

class TheBeast : public SimpleRobot
{
	// Main Robot Objects
	RobotDrive myRobot;
	Joystick Driver;
	Joystick Copilot;
	Compressor compressor;
	Gyro gyro;
	
	// Shooter Objects
	Solenoid ShooterSolenoid1;
	Solenoid ShooterSolenoid2;
	Solenoid DeployWings;
	Solenoid RetractWings;
	Solenoid DeployGetter;
	Solenoid RetractGetter;
	Victor GetterMotor1;
	Victor GetterMotor2;
	
	// Autonomous Selection Inputs
	DigitalInput AutonomousSelection1; // Drive Forward
	DigitalInput AutonomousSelection2; // Shoot and Drive Forward
	DigitalInput AutonomousSelection3; // Shoot, Pick up, Shoot, Drive Forward
	
	// Flag Variables
	bool Fired;
	bool Arms;

public:
	TheBeast();
	
	// Main Robot Methods
	void OperatorControl();
	void Autonomous();
	
	// Shooter Methods
	void Fire( float time );
	void Launcher_Teleop();
	
	void SetGetter( bool Value );
	void SetGetterMotors( float speed );
	void Getter_Teleop();
	
	void SetWings( bool Value );
	void Wings_Teleop();
	
	void Collect();
	
	// Autonomous Methods
	void Auto_1_Ball();
	void Auto_2_Ball();
	void Forward( float Speed, float Time );
};

#endif
