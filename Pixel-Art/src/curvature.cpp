

#include "curvature.h"

using namespace std;

template<class T>
T Curvature<T>::operator()(T t) const
{
	T numerator = dx(t) * d2y(t) - dy(t) * d2x();
	T denominator = pow(dx(t) * dx(t) + dy(t) * dy(t), T(3)/2);
	return numerator/denominator;
}

template<class T>
T Curvature<T>::dx(T t) const
{
	return (1-t)*2*(c1.x-p0.x) + t*2*(p2.x-c1.x); // dx = 2(1-t)(x2-x1) + 2t(x3-x2)
}

template<class T>
T Curvature<T>::dy(T t) const
{
	return (1-t)*2*(c1.y-p0.y) + t*2*(p2.y-c1.y); // dy = 2(1-t)(y2-y1) + 2t(y3-y2)
}

template<class T>
T Curvature<T>::d2x() const
{
	return 2*(p2.x-2*c1.x+p0.x); // d2x = 2(x3-2*x2+x1)
}

template<class T>
T Curvature<T>::d2y() const
{
	return 2*(p2.y-2*c1.y+p0.y); // d2y = 2(y3-2*y2+y1)
}


