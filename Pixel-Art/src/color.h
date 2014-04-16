#include "color.h"

//lelkpnub
class color
{
public:
	int y;
	int u;
	int v;
	color(int , int , int, bool);			//	bool is true for yuv and false for rgb
	~color();

	inline bool dissimilar(color , color);	//	returns true if the 2 colors are dissimilar
	
	inline bool similar(color , color);		//	opposite of dissimilar function	
	
	inline bool same(color , color);		//	returns true if both colors have same yuv values
	
	inline bool shading(color , color);		// returns true if both colors have a yuv distance of atmost 100
	
	inline bool contour(color , color); 	//	opposite of shading function
	
};