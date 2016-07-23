#include "WPILib.h"
#include "Chaos2014.h"
#include "iostream"

void TheBeast::Autonomous()
{
	myRobot.SetSafetyEnabled(false);
	
	if ( AutonomousSelection1.Get() == 0 ) {
		Auto_1_Ball();
	} else if ( AutonomousSelection2.Get() == 0 ) {
		Auto_2_Ball();
	} else if ( AutonomousSelection3.Get() == 0 ) {
		Forward( 0.5, 3 );
	}
}

void TheBeast::Collect() {
	SetGetterMotors( 0.5 );
	SetGetter( true );
	Wait( 2 );
	SetGetter( false );
	Wait( 1 );
	SetGetterMotors( 0.0 );
}

void TheBeast::Auto_1_Ball() {
	// Start
	SetGetter( true );
	SetWings( true );
	Wait( 0.5 );
	
	// First Ball
	Fire( LAUNCH );
	Wait( 0.5 );

	// Drive Forward
	Forward( 0.5, 3 );
}

void TheBeast::Auto_2_Ball() {
	// Start
	SetGetter( true );
	SetWings( true );
	Wait( 0.5 );
	
	// First Ball
	Fire( LAUNCH );
	
	// Get Second Ball
	Collect();
	SetGetter( true );
	Wait( 0.5 );
	
	// Second Ball
	Fire( LAUNCH );
	
	// Drive Forward
	Forward( 0.5, 3 );
}

void TheBeast::Forward( float Speed, float Time ) {
	// Reset the gyro to 0 degrees
	gyro.Reset();
	
	// Timer Stuff
	Timer timer;
	timer.Reset();
	timer.Start();

	while ( timer.Get() <= Time ) {
		float angle = gyro.GetAngle();
		cout << "\t" << timer.Get() << "\n";
		myRobot.Drive( Speed, -angle * 0.03 );
		Wait( 0.005 );
	}
	myRobot.Drive( 0, 0 );

	timer.Stop();
}

// Team 1986 - 2014 video
