#include "WPILib.h"
#include "Chaos2014.h"

TheBeast::TheBeast():
	// Main Robot Objects
	myRobot( 1, 2, 3, 4 ),
	Driver( 1 ),
	Copilot( 2 ),
	compressor( 1, 1 ),
	gyro( 1 ),
	
	// Shooter Objects
	ShooterSolenoid1( 1 ),
	ShooterSolenoid2( 2 ),
	DeployWings( 4 ),
	RetractWings( 3 ),
	DeployGetter( 5 ),
	RetractGetter( 6 ),
	GetterMotor1( 5 ),
	GetterMotor2( 6 ),
	
	// Autonomous Selection Objects
	AutonomousSelection1( 11 ),
	AutonomousSelection2( 12 ),
	AutonomousSelection3( 13 )
{
	Arms = false;
	compressor.Start();
	myRobot.SetExpiration( 1 );
}

void TheBeast::OperatorControl()
{
	myRobot.SetSafetyEnabled(true);
	while ( IsOperatorControl() ) {
		Launcher_Teleop();
		Getter_Teleop();
		Wings_Teleop();
		
		myRobot.ArcadeDrive( -Driver.GetRawAxis( 2 ), -Driver.GetRawAxis( 4 ) );
		Wait(0.005);
	}
}

void TheBeast::Getter_Teleop() {
	// Getter Motors
	if ( Driver.GetRawButton( 1 ) ) {
		SetGetterMotors( 0.5 );
	} else if ( Driver.GetRawButton( 2 ) ) {
		SetGetterMotors( -0.5 );
	} else {
		SetGetterMotors( 0 );
	}
			
	// Getter Arms
	if ( Driver.GetRawButton( 5 ) ) {
		SetGetter( true );
		Arms = true;
	} else if ( Driver.GetRawButton( 6 ) ) {
		SetGetter( false );
		Arms = false;
	}
}

void TheBeast::Wings_Teleop() {
	// Wings
	if ( Copilot.GetRawButton( 5 ) ) {
		SetWings( true );
	} else if ( Copilot.GetRawButton( 6 ) ) {
		SetWings( false );
	}
}

void TheBeast::Launcher_Teleop() {
	if ( Fired ) {
		if ( !Copilot.GetRawButton( 4 ) && !Copilot.GetRawButton( 3 ) && !Copilot.GetRawButton( 2 )  ) {
			Fired = false;
		}
	} else {
		if ( Copilot.GetRawButton( 1 ) || Arms ) {
			if ( Copilot.GetRawButton( 4 ) ) {
				Fire( DEMO );
				Fired = true;
			} else if ( Copilot.GetRawButton( 3 ) ) {
				Fire( PASS );
				Fired = true;
			} else if ( Copilot.GetRawButton( 2 ) ) {
				//Fire( LAUNCH );
				Fired = true;
			}
		} else {
			if ( Copilot.GetRawButton( 4 ) ) {
				SetGetter( true );
				Wait( 0.5 );
				Fire( DEMO );
				Fired = true;
			} else if ( Copilot.GetRawButton( 3 ) ) {
				SetGetter( true );
				Wait( 0.5 );
				Fire( PASS );
				Fired = true;
			} else if ( Copilot.GetRawButton( 2 ) ) {
				SetGetter( true );
				Wait( 0.5 );
				//Fire( LAUNCH );
				Fired = true;
			}
		}
	}
}

START_ROBOT_CLASS(TheBeast);
