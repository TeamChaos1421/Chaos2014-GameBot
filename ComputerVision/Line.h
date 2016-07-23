#ifndef Line_h
#define Line_h

class cvPoint {
	public:
		double x;
		double y;
		
		cvPoint( double X, double Y ) {
			x = X;
			y = Y;
		}
		
		cvPoint() {}
};

class cvLine {
	public:
		cvPoint p1;
		cvPoint p2;
		
		cvLine( cvPoint P1, cvPoint P2 ) {
			p1 = P1;
			p2 = P2;
		}
		
		cvLine() {}
		
		double slope() {
			return( ( p2.y - p1.y ) / ( p2.x - p1.x ) );
		}
		
		double intersect() {
			return( p1.y - ( slope() * p1.x ) );
		}
		
		double solve( double x ) {
			return( slope() * x + intersect() );
		}
};

cvPoint Intersection( cvLine line1, cvLine line2 );

#endif
