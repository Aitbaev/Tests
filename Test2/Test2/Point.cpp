#include "Point.h"

bool Point::operator==(const Point & rhs)const
{
	if (_y == rhs._y && _x == rhs._x)
		return true;
	else
		return false;
}

void  Point::SetX(double x) {
	_x = x;
}
void Point::SetY(double y) {
	_y = y;
}



double Point::GetX()const
{
	return _x;
}
double Point::GetY()const
{
	return _y;
}




Point::Point()
{
}


Point::~Point()
{
}
