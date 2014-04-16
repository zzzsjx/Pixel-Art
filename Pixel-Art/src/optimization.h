#ifndef _OPTIMIZATION_H_
#define _OPTIMIZATION_H_

#include "curvature.h"
#include "integral.h"
#include <cmath>
#include <limits>

using namespace std;

template<class T>
bool is_valid_border_m(T a)
{
	if(a<0)
		a*=-1;

	return a==numeric_limits<T>::infinity() || a==3 || a==1;
}

// Return true if the given four points are considered as a border
template<class T>
bool is_border(const Point<T> (&points)[4])
{
	T dy[2];
	T dx[2];
	T m[2];

	if ( points[1].y == points[2].y ) {
        dy[0] = points[1].y - points[0].y;
        dy[1] = points[3].y - points[2].y;

        dx[0] = points[1].x - points[0].x;
        dx[1] = points[3].x - points[2].x;

        m[0] = dy[0] / dx[0];
        m[1] = dy[1] / dx[1];
    } 
    else if ( points[1].x == points[2].x ) {
        dy[0] = points[1].x - points[0].x;
        dy[1] = points[3].x - points[2].x;

        dx[0] = points[1].y - points[0].y;
        dx[1] = points[3].y - points[2].y;

        m[0] = dy[0] / dx[0];
        m[1] = dy[1] / dx[1];
    } else {
        return false;
    }

    return m[0] == -m[1] && is_valid_border_m(m[0]);
}

template<class T>
vector<Point<T> >::iterator skip1visible(vector<Point<T> >::iterator it, vector<Point<T> >::iterator end)
{
	for(++it; it!=end; ++it)
	{
		if(it->visible)
			return it;
	}

	return end;
}

template<class T>
vector<Point<T> >::difference_type border_detection(vector<Point<T> >::iterator it, vector<Point<T> >::iterator end)
{
	vector<Point<T> >::iterator begin = it;

	if(end-it<4)
		return 0;

	Point<T> last[4];
	vector<Point<T> >::iterator prev = it;

	for(int i=0;i!=4;++i)
	{
		if(it==end)
			return 0;
		last[i] = *it;
		prev = it;
		it = skip1visible<T>(it, end);
	}

	if(!is_border<T>(last)) // DIFFERENCE
		return 0;

	if(it==end)
		return prev-begin;

	bool got_another = false;
	for(it = skip1visible<T>(it,end); it!=end; it = skip1visible<T>(it, end))
	{
		if(!got_another)
		{
			last[0] = last[2];
			last[1] = last[3];
			last[2] = *it;
			got_another = true;
			continue;
		}
		last[3] = *it;

		if(!is_border(last)) //DOUBT
		{
			return prev-begin;
		}
		prev = it;
	}

	return prev-begin;
}

template<class T>
T smoothness_energy(Point<T> c0, Point<T> c1, Point<T> c2)
{
	Point<T> p0 = midpoint(c0, c1);
	Point<T> p2 = midpoint(c1, c2);

	Curvature<T> cur(p1, c1, p2);
	return abs(integral<T>(cur, 0, 1, 16));
}

template<class T>
T positional_energy(Point<T> guess, Point<T> initial )
{
	return pow(pow(guess.x - initial.x, 2) + pow(guess.y - initial.y, 2), 2);
}

/* The relaxation procedure described in the paper */

template<class T>
Point<T> optimization_guess(Point<T> p)
{
	T radius = 0.125;
	T d[] = {
			(T(rand())/RAND_MAX)*radius*2 - radius,
			(T(rand())/RAND_MAX)*radius*2 - radius
			};

	return p + Point<T>(d[0], d[1]);
}

template<class T>
vector<Point<T> > optimize(const vector<Point<T> > &path)
{
	vector<Point<T> > Path;

	Path ret = path;

	/* The number of vertices not constrained by optimization */
    unsigned n = 0;

    // Values chosen randomly (through testing)
    const unsigned iterations = 4;
    const unsigned nguess_per_iteration = 4;

    for ( unsigned i = 0 ; i != iterations ; ++i ) {
        n = 0;

        /* This iteration bounds is not something to worry about, because the
         * smallest path has size 4. */
        for ( typename Path::size_type j = 0 ; j != ret.size() ; ++j ) {
            Point<T> prev = ( j == 0 ) ? ret.back() : ret[j-1];
            Point<T> next = ( j + 1 == ret.size() ) ? ret.front() : ret[j+1] ;

            if ( !ret[j].visible || !ret[j].smooth )
                continue;

            {
                typename Path::iterator it = ret.begin() + j;
                typename Path::difference_type skip
                    = border_detection<T>(it, ret.end());
                j += skip;
                if ( j == ret.size() )
                    break;
            }

            ++n;

            for ( unsigned k = 0 ; k != nguess_per_iteration ; ++k ) {
                Point<T> guess = optimization_guess(ret[j]);

                T s = smoothness_energy(prev, guess, next);
                T p = positional_energy(guess, path[j]);

                T e = s + p;

                T prev_e = smoothness_energy(prev, ret[j], next)
                    + positional_energy(ret[j], path[j]);

                if ( prev_e > e ) {
                    // We don't want to screw other metadata, then we manually
                    // assign the new coords
                    ret[j].x = guess.x;
                    ret[j].y = guess.y;
                }
            }
        }
    }

    return ret;
}



#endif