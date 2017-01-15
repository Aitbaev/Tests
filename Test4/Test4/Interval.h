#pragma once
#include <ctime>

//Интервалом считаем отрезок времени с постоянным колличеством людей в банке, 
class Interval
{
private:
	time_t _beginTime;//время начала интервала
	time_t _endTime;//время конца интервала
	unsigned int _clientsQuantity;//колличество людей в интервале (их может быть и нуль)


public:
	bool operator<(const Interval & rhs)const;
	Interval& operator=(const Interval& rhs);

	void setClientsQuantity(unsigned int);
	void setBeginTime(time_t);
	void setEndTime(time_t);

	unsigned int getClientsQuantity()const;
	time_t getBeginTime()const;
	time_t getEndTime()const;



	Interval();
	~Interval();
};

