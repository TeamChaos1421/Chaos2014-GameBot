#include "WPILib.h"
#include "Chaos2014.h"

void TheBeast::Fire( float time )
{
	ShooterSolenoid1.Set( true );
	ShooterSolenoid2.Set( true );
	Wait( time );
	ShooterSolenoid1.Set( false );
	ShooterSolenoid2.Set( false );
}

void TheBeast::SetGetter( bool Value )
{
	if ( Value ) {
		RetractGetter.Set( false );
		DeployGetter.Set( true );
	} else {
		DeployGetter.Set( false );
		RetractGetter.Set( true );
	}
}

void TheBeast::SetWings( bool Value )
{
	if ( Value ) {
		RetractWings.Set( false );
		DeployWings.Set( true );
	} else {
		DeployWings.Set( false );
		RetractWings.Set( true );
	}
}

void TheBeast::SetGetterMotors( float speed )
{
	GetterMotor1.Set( speed );
	GetterMotor2.Set( speed );
}
