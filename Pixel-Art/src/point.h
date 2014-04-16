#ifndef _POINT_H_
#define _POINT_H_


template<class T>
struct Point
{
	Point() : visible(true) {}
	Point(T x, T y) : visible(true), x(x), y(y) {}
	Point(T x, T y, bool smooth) : smooth(smooth), visible(true), x(x), y(y) {}

	Point operator+(const Point & p) const
	{
		return Point(x + p.x, y + p.y);
	}

	Point operator/(T val) const
	{
		return Point(x/val, y/val);
	}

	Point invisible() const
	{
		Point p = *this;
		p.visible = false;
		return p
	}

	bool smooth;

	bool visible;

	T x, y;
};

template<class T>
Point<T> midpoint(const Point<T> &a, const Point<T> &b)
{
	return Point<T>((a.x + b.x)/2, (a.y+b.y)/2);
}

template<class T>
bool operator==(const Point<T> &lhs, const Point<T> &rhs)
{
	return lhs.smooth==rhs.smooth && lhs.x==rhs.x && lhs.y==rhs.y;
}

// A weak equality function compared to the one above

template<class T>
bool equal(const Point<T> &lhs, const Point<T> &rhs)
{
	return lhs.x==rhs.x && lhs.y==rhs.y;
}

// A Function to convert a point of this struct to a geometric point to use in rendering svg *INCOMPLETE*

#endif
