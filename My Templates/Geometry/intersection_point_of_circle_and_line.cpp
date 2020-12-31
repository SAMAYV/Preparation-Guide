// As indicated at the outset, we assume that the circle is centered at the origin, and therefore the input to the program is the 
// radius r of the circle and the parameters A, B and C of the equation of the line.

// Let's start by find the point on the line which is closest to the origin (x0,y0). 
// First, it has to be at a distance d0 = |c|/sqrt(a*a + b*b)

ll no_of_points_of_intersection(ld r,ld a,ld b,ld c)
{
	ld x0 = -(a*c)/(a*a + b*b); 
	ld y0 = -(b*c)/(a*a + b*b);
	if(c*c > r*r*(a*a+b*b) + EPS){
	    return 0;
	}
	else if(abs(c*c - r*r*(a*a+b*b)) < EPS){
	    cout<<x0<<' '<<y0<<'\n';
	    return 1;
	}
	else {
	    ld d_square = r*r - (c*c)/(a*a + b*b);
	    ld mult = sqrt(d_square/(a*a+b*b));
	    ld ax, ay, bx, by;
	    ax = x0 + b * mult;
	    bx = x0 - b * mult;
	    ay = y0 - a * mult;
	    by = y0 + a * mult;
	    cout<<ax<<' '<<ay<<'\n'<<bx<<' '<<by<<'\n';
		return 2;
	}
}