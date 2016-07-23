/**
	Computer_Vision_Client.cpp
	Purpose: Library functions for connecting to the vision server.
	
	@author Luc Lagarde
	@version 
	
*/

#include "Computer_Vision_Client.h"

std::string GetTargetData( int connection, std::string command ) {
	// Variables
	std::string BufferString( command );
	std::stringstream BufferStream;
	
	// Write Thresholding Parameters
	if ( write( connection, &BufferString[0], BufferString.length() ) < 0 ) {
		std::cout << "ERROR writing to socket\n";
		return "ERROR";
	}
	BufferString.clear();
	
	// Get Data String
	BufferString.resize( 1024, 0 );
	if( read( connection, &BufferString[0], 1023 ) < 0 ) {
		std::cout << "ERROR reading from socket\n";
		return "ERROR";
	}
	
	return BufferString;
}





std::vector<Target> GetTargets( std::string BufferString ) {
	std::stringstream BufferStream( BufferString );
	
	// Get the number of targets
	int TargetCount;
	BufferStream >> TargetCount;
		
	// Targets Vector
	std::vector<Target> targets;
	
	// Get Targets
	for ( int count = 0; count < TargetCount; count++ ) {
		targets.push_back( Target() );
		
		BufferStream >> targets[ count ].x;
		BufferStream >> targets[ count ].y;
		BufferStream >> targets[ count ].w;
		BufferStream >> targets[ count ].h;
		BufferStream >> targets[ count ].center.x;
		BufferStream >> targets[ count ].center.y;
	}
	
	// Add in time
	double time;
	BufferStream >> time;
	
	for ( int count = 0; count < TargetCount; count++ ) {
		targets[ count ].time = time;
	}
	
	return targets;
}



Goal CV_Client( const char* url, const char* port, const char* command ) {
	Goal CV_Goal;
	
	//std::vector<Target> RawTargets;
	//std::vector<Target> DynamicTargets;
	//std::vector<Target> StaticTargets;
	//int HotGoal;
	//cvPoint intersection;

	/******************************************************************************************
	* Get static and dynamic targets from the server ****************************************** 
	******************************************************************************************/
	
	// Connect to socket
	int sockfd = TCP_Client( url, port );
	if ( sockfd < 0 ) {
		CV_Goal.failed = true;
		return CV_Goal;
	}
	
	// Get data from server
	std::string BufferString = GetTargetData( sockfd, command );
	//std::string BufferString = "3\n21\n218\n86\n13\n63\n223\n508\n169\n9\n79\n511\n210\n146\n167\n10\n81\n150\n206\n1\n";
	if ( BufferString == "ERROR" ) {
		CV_Goal.failed = true;
		return CV_Goal;
	}
	
	// Close socket
	close( sockfd );
	
	// Get vector of all targets
	CV_Goal.RawTargets = GetTargets( BufferString );
		
	// Sort targets into static and dynamic vectors
	for ( unsigned int count = 0; count < CV_Goal.RawTargets.size(); count++ ) {	
		if ( double( CV_Goal.RawTargets[ count ].w ) / double( CV_Goal.RawTargets[ count ].h ) > 1 )
			CV_Goal.DynamicTargets.push_back( CV_Goal.RawTargets[ count ] );
		else
			CV_Goal.StaticTargets.push_back( CV_Goal.RawTargets[ count ] );
	}

	/******************************************************************************************
	* Derive information ********************************************************************** 
	******************************************************************************************/
	
	// Find Hot Goal, if possible
	if ( CV_Goal.StaticTargets.size() >= 1 && CV_Goal.DynamicTargets.size() >= 1 ) {
		if ( CV_Goal.DynamicTargets[0].x < CV_Goal.StaticTargets[0].x ) {
			CV_Goal.HotGoal = Left;
		} else {
			CV_Goal.HotGoal = Right;
		}
	} else {
		CV_Goal.HotGoal = Unknown;
	}
	
	// Intersect Lines
	//intersection = Intersection(
	//	cvLine(
	//		StaticTargets[0].top(),
	//		StaticTargets[1].bottom()
	//	),
	//	cvLine(
	//		StaticTargets[0].bottom(),
	//		StaticTargets[1].top()
	//	)
	//);


	
	CV_Goal.failed = false;
	return CV_Goal;
}




void Goal::Dump() {
	std::cout << RawTargets.size() << " targets found:\n";
	
	std::cout << "\tFound " << StaticTargets.size() << " static targets:\n";
	for ( unsigned int count = 0; count < StaticTargets.size(); count++ ) {	
		std::cout << "\t\tStatic Target " << count << ":\n";
		std::cout << "\t\t\tx:\t" << StaticTargets[ count ].x << "\n";
		std::cout << "\t\t\ty:\t" << StaticTargets[ count ].y << "\n";
		std::cout << "\t\t\tw:\t" << StaticTargets[ count ].w << "\n";
		std::cout << "\t\t\th:\t" << StaticTargets[ count ].h << "\n";
		std::cout << "\t\t\ttop:\t( " << StaticTargets[ count ].top().x << ", " << StaticTargets[ count ].top().y << ")\n";
		std::cout << "\t\t\tcenter:\t( " << StaticTargets[ count ].center.x << ", " << StaticTargets[ count ].center.y << ")\n";
		std::cout << "\t\t\tbottom:\t( " << StaticTargets[ count ].bottom().x << ", " << StaticTargets[ count ].bottom().y << ")\n";
		std::cout << "\t\t\ttime:\t" << StaticTargets[ count ].time << "\n";
		std::cout << "\t\t\n";
	}
	
	std::cout << "\tFound " << DynamicTargets.size() << " dynamic targets:\n";
	for ( unsigned int count = 0; count < DynamicTargets.size(); count++ ) {	
		std::cout << "\t\tDynamic Target " << count << ":\n";
		std::cout << "\t\t\tx:\t" << DynamicTargets[ count ].x << "\n";
		std::cout << "\t\t\ty:\t" << DynamicTargets[ count ].y << "\n";
		std::cout << "\t\t\tw:\t" << DynamicTargets[ count ].w << "\n";
		std::cout << "\t\t\th:\t" << DynamicTargets[ count ].h << "\n";
		std::cout << "\t\t\ttop:\t( " << DynamicTargets[ count ].top().x << ", " << DynamicTargets[ count ].top().y << ")\n";
		std::cout << "\t\t\tcenter:\t( " << DynamicTargets[ count ].center.x << ", " << DynamicTargets[ count ].center.y << ")\n";
		std::cout << "\t\t\tbottom:\t( " << DynamicTargets[ count ].bottom().x << ", " << DynamicTargets[ count ].bottom().y << ")\n";
		std::cout << "\t\t\ttime:\t" << DynamicTargets[ count ].time << "\n";
		std::cout << "\t\t\n";
	}
	
	std::cout << "Intersection: ( " << Center.x << ", " << Center.y << " )\n";
	
	std::cout << "Hot Goal: ";
	switch( HotGoal ) {
		case Unknown:
			std::cout << "Unknown\n";
			break;
		case Left:
			std::cout << "Left\n";
			break;
		case Right:
			std::cout << "Right\n";
	break;
	}
}
