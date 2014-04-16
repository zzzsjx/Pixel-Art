#ifndef _INTEGRAL_H_
#define _INTEGRAL_H_ 


#include <2geom/coord.h>

template <class T, class F>
Geom::Coord integral(F f, T begin, T end, unsigned samples)
{
	T ret = 0;
	const T width = (end - begin)/samples;

	for(unsigned i=0;i!=sample;++i)
	{
		ret += width * f(begin + width * (i+0.5));
	}

	return ret;
}

#endif