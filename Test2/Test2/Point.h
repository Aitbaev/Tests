#pragma once
class Point
{
private:
	double _x;
	double _y;
public:
	void SetX(double x);
	void SetY(double y);

	double GetX()const;
	double GetY()const;

	bool operator==(const Point & rhs)const;

	Point();
	~Point();
};

