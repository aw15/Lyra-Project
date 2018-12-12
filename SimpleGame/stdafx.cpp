#include "stdafx.h"


float magnitude(float x, float y) {
	return sqrt(x*x + y * y);
}

bool isCollide(Rect & standard, Rect & compare)
{
	//cout <<"standard: "<< standard[0].x <<" "<<standard.maxx <<"compare: " <<compare[0].x<<" "<<compare.maxx << endl;
	bool isX = ((standard.minx <= compare.minx&&standard.maxx >= compare.minx) || (standard.minx <= compare.maxx&&standard.maxx >= compare.maxx));
	bool isY = ((standard.miny <= compare.miny&&standard.maxy >= compare.miny) || (standard.miny <= compare.maxy&&standard.maxy >= compare.maxy));


	return (isX&&isY);
}
