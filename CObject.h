#pragma once
#include "Point.h"


class CObject
{
public:
	virtual void reset() {};
	virtual Point getXY() {};
	virtual void setXY(Point) {};
	CObject();
	~CObject();
};

