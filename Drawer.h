#pragma once
#include "afxwin.h"
#include <gdiplus.h>
#include <vector>
#include <iostream>
using namespace Gdiplus;
using namespace std;

class Drawer : public CStatic
{

public:
	float xmin, xmax, ymin, ymax, step_x, step_y;
	bool isHasNegative;
	bool isHasNegativeX;
	vector<PointF> *_points;
	Drawer();
	~Drawer();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
private:
	REAL X(LPDRAWITEMSTRUCT RECT, float x);
	REAL Y(LPDRAWITEMSTRUCT RECT, float y);
	REAL Width(LPDRAWITEMSTRUCT RECT, float width);
	REAL Height(LPDRAWITEMSTRUCT RECT, float height);

};