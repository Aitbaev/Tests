#pragma once
#include <ctime>

//���������� ������� ������� ������� � ���������� ������������ ����� � �����, 
class Interval
{
private:
	time_t _beginTime;//����� ������ ���������
	time_t _endTime;//����� ����� ���������
	unsigned int _clientsQuantity;//����������� ����� � ��������� (�� ����� ���� � ����)


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

