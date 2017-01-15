#include<iostream>
#include<set>
#include <typeinfo>

#include <map>
#include <iterator>
#include "CheckingInputFIle.h"
#include "Interval.h"

#include "FindRushHourIntervals.h"

#include "EraseIndexes.h"
using namespace std;

int main()
{
	vector<Interval>* intervalsVector = new vector<Interval>;

	if (checkingInputFile(intervalsVector))
	{	// FindRushHourIntervals(Intervals) - функция поиска нагруженных интервалов, получает указатель на вектор интервалов 
		//возвращает множество интервалов
		multiset<Interval> rushHourIntervals = FindRushHourIntervals(intervalsVector);


		//выводим на экрам часы с самым нагруженным колличеством клиентов в банке

		cout << "RushHour intervals are:\n";
		for (multiset<Interval>::iterator j = rushHourIntervals.begin(); j != rushHourIntervals.end(); j++)
		{
			struct tm a;
			const time_t IntervalsCameTime = j->getBeginTime();
			localtime_s(&a, &IntervalsCameTime);
			struct tm b;
			const time_t IntervalsGoneTime = j->getEndTime();
			localtime_s(&b, &IntervalsGoneTime);
			cout << a.tm_hour << ":" << a.tm_min << "-" << b.tm_hour << ":" << b.tm_min << endl;// << "	" << j->getClientsQuantity() << endl;
		}

	}


	return 0;
}

