#ifndef Computer_Vision_Client_h
#define Computer_Vision_Client_h

#include <iostream>
#include <sstream>
#include <vector>

#include "TCP_Client.h"
#include "Line.h"

//! vision target class.
/*! class for storing information about detected targets. */
class Target {
	public:
		int x;
		int y;
		int w;
		int h;
		
		//! amount of time in seconds request took to serve.
		double time;

		//! center of mass of target.
		cvPoint center;
		
		//! top of target directly above the center.
		cvPoint top() {
			return( cvPoint( center.x, y ) );
		};
		
		//! top of target directly below the center.
		cvPoint bottom() {
			return( cvPoint ( center.x, y + h ) );
		};
};

typedef enum { Left, Right, Unknown } Side;

class Goal {
	public:
		std::vector <Target> RawTargets;
		std::vector <Target> StaticTargets;
		std::vector <Target> DynamicTargets;
		
		cvPoint Center;
		cvPoint Center_Top;
		cvPoint Center_Bottom;
		
		cvPoint Left_Center;
		cvPoint Right_Center;
		
		Side HotGoal;
		bool failed;
		
		void Dump();
};

std::string GetTargetData( int connection, std::string command );
std::vector<Target> GetTargets( std::string BufferString );
Goal CV_Client( const char* url, const char* port, const char* command );

#endif


/*
	* \	  /	* \	  /	*
	*	*	*	*	*
	* /	  \	* /	  \	*
*/
