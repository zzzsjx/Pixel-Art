#include "color.h"
#include <cmath>

color::color(int a,int b,int c,bool T)
{
	if(T)
	{
		y = a;
		u = b;
		v = c;
	}
	else
	{
		// Y = 0.299R + 0.587G + 0.114B
  		// U = 0.492 (B-Y)
  		// V = 0.877 (R-Y)
		y = (0.299*a) + (0.587*b) + (0.114*c);
		u = 0.492*(c - y);
		v = 0.877*(a - y); 
	}

}

inline bool color::dissimilar(color A, color B)
{
	if(abs(A.y - B.y) > 48 || abs(A.u - B.u) > 7 || abs(A.v - B.v) > 6)
		return true;
	else
		return false;
}

inline bool color::similar(color A, color B)
{
	return !(dissimilar(A,B));	
}

inline bool color::same(color A, color B)
{
	if(A.y == B.y && A.u == B.u && A.v == B.v)
		return true;
	else
		return false;
}

inline bool color::shading(color A, color B)
{
	if(abs(A.y - B.y) <= 100 && abs(A.u - B.u) <= 100 && abs(A.v - B.v) <= 100)
		return true;
	else
		return false;
}

inline bool color::contour(color A, color B)
{
	return !(shading(color A, color B));
}