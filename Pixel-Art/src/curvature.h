#ifndef _CURVATURE_H_
#define _CURVATURE_H_

#include "point.h"
#include <cmath>

using namespace std;

template<class T>
struct Curvature
{
	Curvature(Point<T> p0, Point<T> c1, Point<T> p2) : 
		p0(p0), c1(c1), p2(p2)
	{}

	T operator()(T t) const;

	T dx(T t) const; //Derivative of x

	T dy(T t) const; //Derivative of y

	T d2x() const; //Double derivative of x

	T d2y() const; //Double derivative of y

	Point<T> p0, c1, p2;
};

#endif
