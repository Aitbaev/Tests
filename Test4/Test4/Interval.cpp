#include "Interval.h"





Interval& Interval::operator=(const Interval& rhs) {

	if (this == &rhs)
	{
		return *this;
	}
	_beginTime = rhs._beginTime;
	_endTime = rhs._endTime;
	_clientsQuantity = rhs._clientsQuantity;
	return *this;
}


bool Interval::operator< (const Interval & rhs)const
{
	return (_beginTime < rhs._beginTime);
}



void Interval::setClientsQuantity(unsigned int IntervalsQuantity)
{
	_clientsQuantity = IntervalsQuantity;
}


unsigned int Interval::getClientsQuantity()const
{
	return _clientsQuantity;
}

void Interval::setEndTime(time_t gone)
{
	_endTime = gone;
}

void Interval::setBeginTime(time_t came)
{
	_beginTime = came;
}
void setEndTime(time_t);

time_t Interval::getBeginTime()const
{
	return _beginTime;
}
time_t Interval::getEndTime()const
{
	return _endTime;
}


Interval::Interval()
{
	_beginTime = 0;
	_endTime = 0;
	_clientsQuantity = 1;
}


Interval::~Interval()
{
}
