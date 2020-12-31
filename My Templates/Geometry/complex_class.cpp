typedef complex<ll> P;
#define X real()
#define Y imag()

int main()
{
	P p = {4,2};
	cout<<p.X<<" "<<p.Y<<"\n"; // 4 2

	P v = {3,1};
	P u = {2,2};
	P s = v+u;
	cout<<s.X<<" "<<s.Y<<"\n"; // 5 3

	P a = {4,2};
	P b = {3,-1};
	cout<<abs(b-a)<<"\n"; // 3.16228

	// The function arg(v) calculates the angle of a vector v (x, y) with respect to the x axis
	// The function polar(s,a) constructs a vector whose length is s and that points to an angle a.
	// A vector can be rotated by an angle a by multiplying it by a vector with length 1 and angle a.
	
	// The following code calculates the angle of the vector (4,2), rotates it 1/2 radians counterclockwise, 
	// and then calculates the angle again:
	P v = {4,2};
	cout<<arg(v)<<"\n"; // 0.463648
	v *= polar(1.0,0.5);
	cout<<arg(v)<<"\n"; // 0.963648

	// The following code calculates the cross product using the class complex:
	// the function conj negates the y coordinate of a vector
	P a = {4,2};
	P b = {1,2};
	C p = (conj(a) * b).Y; // 6

	// The cross product (p-s1)*(p-s2) tells us the location of the point p. If the cross product is positive, p is located on 
	// the left side, and if the cross product is negative, p is located on the right side. Finally, if the cross product is zero, points
	// s1, s2 and p are on the same line.

	// Another feature of cross products is that the area of a triangle can be calculated using the formula |(a - c)*(b - c)|/2

}