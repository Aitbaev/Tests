#include "FindMax.h"

vector<rushHourPeriod>  FindMax(array<float, stringsQuantityMustBeInInput> & sumdDistToCashBoxesEachHalfHour) {

	float max = sumdDistToCashBoxesEachHalfHour[0];
	//для начала считаем первый элемент из массива максимальным

	for (int i = 0; i < stringsQuantityMustBeInInput; i++)//в цикле проверяем 
		if (sumdDistToCashBoxesEachHalfHour[i] > max)// если последующий элемент больше,
			max = sumdDistToCashBoxesEachHalfHour[i];//то заменяем максимальный элемент им

	vector<int> maxLengthsTimes;
	//вектор который мы заполняем индексами максимальных значений (в случае если таких больше одного нам нужно не одно а все эти значения)
	for (int i = 0; i < stringsQuantityMustBeInInput; i++)
		if (max == sumdDistToCashBoxesEachHalfHour[i])
			maxLengthsTimes.push_back(i);

	//ставим индексам максимального значения в соответствие временной интервал
	time_t now = time(NULL);

	struct tm nowInTm = *localtime(&now);

	//считаем что магазин открывается в 10:00 утра
	nowInTm.tm_hour = 10;
	nowInTm.tm_min = 0;
	nowInTm.tm_sec = 0;

	time_t openingTime = mktime(&nowInTm);//время открытия магазина

	vector<rushHourPeriod> rushHourPeriods;//вектор часов пик в магазине

										   //в данном цикле переводим номера интервалов в переменные типа rushHourPeriod кладем эти значения в объявленный выше вектор
	for (unsigned int i = 0, consecutivePeriodsQuantity = 0; i < maxLengthsTimes.size(); i++)//consecutivePeriodsQuantity  - колличество последовательных 
	{																					//интервалов эта переменная нужна в том случае если максимальная 
																						//длинна очереди была подряд 2 или более интервалов - тогда мы 
																						//объединяем интервалы
		while ((i != maxLengthsTimes.size() - 1) && (maxLengthsTimes[i + 1] - maxLengthsTimes[i] == 1))
		{//покуда счетчик не дошел до последнего элемента и разница между нынешним и последующим значениями равна 1
			consecutivePeriodsQuantity++; //увеличиваем  колличество последовательных интервалов
			i++;//и счетчик(мы как бы перескакиеваем следующую итерацию)
		}

		time_t begin = openingTime + halfHour*maxLengthsTimes[i - consecutivePeriodsQuantity];//время начала интервала (объединяем подряд
																							  //идущие интервалы если consecutivePeriodsQuantity != 0)
		time_t end = begin + halfHour*(consecutivePeriodsQuantity + 1);//время конца интервала
		consecutivePeriodsQuantity = 0;//обнуляем переменную колличества последовательных интервалов

		struct tm begInInTm = *localtime(&begin);//переводим begin из time_t в tm
		struct tm endInTm = *localtime(&end);//переводим end из time_t в tm

		rushHourPeriod newOnePeriod;//создаем переменную типа rushHourPeriod см. FindMax.h

									//далее переводим begInInTm и endInTm в строки, выделяя только часы и минуты 
		newOnePeriod.begin = to_string(begInInTm.tm_hour) + ":" + to_string(begInInTm.tm_min);
		newOnePeriod.end = to_string(endInTm.tm_hour) + ":" + to_string(endInTm.tm_min);
		//кладем newOnePeriod в вектор
		rushHourPeriods.push_back(newOnePeriod);
	}
	//функция возвращает вектор
	return rushHourPeriods;
}