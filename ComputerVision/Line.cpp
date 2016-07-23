#include "Line.h"

cvPoint Intersection( cvLine line1, cvLine line2 ) {
	cvPoint intersection;
	
	intersection.x = ( line2.intersect() - line1.intersect() ) / ( line1.slope() - line2.slope() );
	intersection.y = line1.solve( intersection.x );
	
	return( intersection );
}
