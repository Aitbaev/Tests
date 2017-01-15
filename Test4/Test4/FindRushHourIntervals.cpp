
#include "FindRushHourIntervals.h"

multiset<Interval> FindRushHourIntervals(vector<Interval>* intervalsVector)
{
	vector<Interval> &rIntervalsVeсtor = *intervalsVector;

	multiset<Interval>* intervalsSet = new multiset<Interval>;

	//=================================================================================================
	Interval nominal;//создаем номинальный интервал

	tm IntervalsCameTime;
	localtime_s(&IntervalsCameTime, &now);
	tm IntervalsGoneTime;
	localtime_s(&IntervalsGoneTime, &now);

	IntervalsCameTime.tm_hour = 8;//устанавливаем в начало интервала время открытия банка
	IntervalsCameTime.tm_min = 0;
	IntervalsGoneTime.tm_hour = 22;//устанавливаем в конец интервала время закрытия банка
	IntervalsGoneTime.tm_min = 0;

	nominal.setBeginTime(mktime(&IntervalsCameTime));
	nominal.setEndTime(mktime(&IntervalsGoneTime));
	nominal.setClientsQuantity(0);//устанавливаем колличество людей в интервале - нуль

	intervalsSet->insert(nominal);
	multiset<Interval> * willBeInsertedSet = new multiset<Interval>;//кладем интервал в множество (с повторениями на всякий случай) интервалов 
																	//для дальнейшего добавления в intervalsSet . Этот интервал используем из-за того, что мы работая с интервалом intervalsSet - через итераторы
																	// мы не можем изменять множества (удалять из него элементы или добавлять их). Посему в это множество добавляются интервалы которые после того как мы
																	//закончим работу в цикле (тот который вложен в нижестоящий) мы добавим в intervalsSet все элементы из  willBeInsertedSet, а сам  willBeInsertedSet - 
																	//очистим
																	//=================================================================================================



																	//представим временной интервал как отрезок прямой, где начало  - время открытия банка, конец время закрытия
																	//на этот отрезок мы будем умозрительно добавлять интервалы из вектора rIntervalsVeсtor
																	//Сначала добавим выше-объявленный интервал nominal, таким образом мы перекроем весь отрезок
																	//Получается у нас сначала будет интервал в который никто не приходил

																	//В нижестоящем цикле будем добавлять интервалы из rIntervalsVeсtor сначала в willBeInsertedSet
																	//при этом в старых интервалах которые стояли на месте куда нам нужно добавить новые мы будем их удалять
																	//добавлять же будем с учем того каким был старый интервал. Интервал nominal добавили для того чтоб у нас не было пустот на всем временом отрезке
																	//с момента открытия до закрытия банка
	for (unsigned int i = 0; i < rIntervalsVeсtor.size(); i++)
	{
		EraseIndexes eraseIndexesInstance;//создаем объект "класса индексов для удаления"(См. EraseIndexes.h)

		Interval temp = rIntervalsVeсtor[i];//интервал текущего индекса перезаписываем во временную переменную для дальнейшей работы

											//В данном цикле сравниваем добавляемый из rIntervalsVector интервал с ранее добавленными в intervalsSet интервалами
		for (auto j = intervalsSet->begin(); j != intervalsSet->end(); j++, eraseIndexesInstance.incrementEraseEndIndex())
		{

			//из интервалов множества intervalsSet рассматриваем тот который удовлетворяет следующему условию
			if (temp.getBeginTime() >= j->getBeginTime() && temp.getBeginTime() < j->getEndTime())
			{

				//в сосзданном ранее объекте "класса индексов для удаления" установим индекс начала удаления
				eraseIndexesInstance.setEraseBeginIndex(eraseIndexesInstance.getEraseEndIndex() - 1);

				//создадим 2 челочисленных значения показывающих разницу во времени: leftDifference - между началом temp интервала и
				//началом интервала под индексом j и rightDifference - между концом temp интервала и
				//концом интервала под индексом j
				int leftDifference = static_cast<int>(difftime(temp.getBeginTime(), j->getBeginTime()));
				int rightDifference = static_cast<int>(difftime(j->getEndTime(), temp.getEndTime()));

				//==========================================================================================================================================
				//далее до следующего (//==============) выполняется создание и подготока новых интервалов  для добавления в willBeInsertedSet, а затем 
				// в intervalsSet, а также подготовка индексок которые нужно удалить (подготовка индексов делается через объект класса EraseIndexes)
				if (leftDifference == 0) //рассмотрим отдельно этот случай
				{
					Interval prevInterval;//создаем переменную в которую будет записываться предыдущий (до того на который указывает итератор j)
										  //интервал
					if (j != intervalsSet->begin()) //если j не первый из множества 
					{
						j--;//то декрементируем j 
						prevInterval = *j;// записываем значение под указателем j в предыдущий интервал
						j++;//возвращаем j на то место куда он указывал
					}
					if ((j->getClientsQuantity() + 1) == prevInterval.getClientsQuantity())
						//если у нынешнего и предыдущего интервала колличесто клиентов вышло одинаковым
					{
						// в объекте "класса индексов для удаления" установим индекс начала удаления на 1 меньше чтоб удалить и предыдущий
						eraseIndexesInstance.setEraseBeginIndex(eraseIndexesInstance.getEraseBeginIndex() - 1);

						if (rightDifference > 0)
						{
							prevInterval.setEndTime(temp.getEndTime());

							Interval leftoverInterval = *j;
							leftoverInterval.setBeginTime(temp.getEndTime());

							willBeInsertedSet->insert(prevInterval);
							willBeInsertedSet->insert(leftoverInterval);

							break;
						}
						else
						{
							prevInterval.setEndTime(j->getEndTime());
							willBeInsertedSet->insert(prevInterval);
							if (rightDifference == 0)
								break;
							else
								temp.setBeginTime(j->getEndTime());
						}

					}
					else
					{
						if (rightDifference > 0)
						{
							Interval layeredInterval = temp;
							layeredInterval.setClientsQuantity(j->getClientsQuantity() + 1);

							Interval leftoverInterval = *j;
							leftoverInterval.setBeginTime(temp.getEndTime());

							willBeInsertedSet->insert(layeredInterval);
							willBeInsertedSet->insert(leftoverInterval);

							break;
						}
						else
						{
							Interval layeredInterval = *j;
							layeredInterval.setClientsQuantity(layeredInterval.getClientsQuantity() + 1);
							willBeInsertedSet->insert(layeredInterval);
							if (rightDifference == 0)
								break;
							else
								temp.setBeginTime(j->getEndTime());
						}

					}
				}

				if (leftDifference > 0 && rightDifference <= 0)
				{
					Interval layeredInterval = temp;
					layeredInterval.setClientsQuantity(j->getClientsQuantity() + 1);
					layeredInterval.setEndTime(j->getEndTime());

					Interval leftoverInterval = *j;
					leftoverInterval.setEndTime(temp.getBeginTime());

					willBeInsertedSet->insert(layeredInterval);
					willBeInsertedSet->insert(leftoverInterval);

					if (rightDifference == 0)
					{
						break;
					}
					else
					{
						temp.setBeginTime(j->getEndTime());
					}
				}

				if (leftDifference > 0 && rightDifference > 0)
				{
					Interval layeredInterval = temp;
					layeredInterval.setClientsQuantity(j->getClientsQuantity() + 1);

					Interval leftLeftoverInterval = *j;
					leftLeftoverInterval.setEndTime(temp.getBeginTime());

					Interval rightLeftoverInterval = *j;
					rightLeftoverInterval.setBeginTime(temp.getEndTime());


					willBeInsertedSet->insert(layeredInterval);
					willBeInsertedSet->insert(leftLeftoverInterval);
					willBeInsertedSet->insert(rightLeftoverInterval);

					break;
				}
				//==========================================================================================================================================
				//здесь заканчивается создание и подготока новых интервалов  для добавления в willBeInsertedSet, а затем 
				// в intervalsSet, а также подготовка индексок которые нужно удалить 
			}
		}

		multiset<Interval>::iterator beginIterator = intervalsSet->begin();
		advance(beginIterator, eraseIndexesInstance.getEraseBeginIndex()); //после выполнения этой функции
																		   //beginIterator начинает указывать на то меcто откуда нужно начинать удаление элементов из intervalsSet

		multiset<Interval>::iterator endIterator = intervalsSet->begin();
		advance(endIterator, eraseIndexesInstance.getEraseEndIndex());//после выполнения этой функции
																	  //endIterator начинает указывать на то меcто откуда нужно заканчивать удаление элементов из intervalsSet

		intervalsSet->erase(beginIterator, endIterator);//удаляем старые интервалы
		intervalsSet->insert(willBeInsertedSet->begin(), willBeInsertedSet->end());//добавляем новые
		willBeInsertedSet->erase(willBeInsertedSet->begin(), willBeInsertedSet->end());//очищаем множество интрервалов готовых на добавление
	}

	/*тут можно посмотреть в какие интервалы времени сколько людей было===========================================================================
	for (multiset<Interval>::iterator j = intervals->begin(); j != intervals->end(); j++)
	{
	struct tm a;
	const time_t IntervalsCameTime = j->getBeginTime();
	localtime_s(&a, &IntervalsCameTime);
	struct tm b;
	const time_t IntervalsGoneTime = j->getEndTime();
	localtime_s(&b, &IntervalsGoneTime);
	cout << a.tm_hour << ":" << a.tm_min << "-" << b.tm_hour << ":" << b.tm_min << "	" << j->getClientsQuantity() << endl;
	}
	//==============================================================================================================================================
	//*/

	//находим интервал с самым большим колличеством людей в нем
	//==========================================================================================
	int peopleQuantity = 0;

	for (auto i = intervalsSet->begin(); i != intervalsSet->end(); i++)
	{
		if (i->getClientsQuantity() > (unsigned)peopleQuantity)
			peopleQuantity = i->getClientsQuantity();
	}
	//==========================================================================================
	multiset<Interval> rushHourIntervalsSet;

	//все интервалы с наибольшим колличеством людей в нем записываем в возвращаемое функцией множество rushHourIntervalsSet
	//==========================================================================================
	for (auto i = intervalsSet->begin(); i != intervalsSet->end(); i++)
	{
		if (i->getClientsQuantity() == peopleQuantity)
			rushHourIntervalsSet.insert(*i);
	}
	//==========================================================================================

	//удаляем лишние указатели на объекты в динамической памяти
	//==========================================================================================
	delete intervalsSet;
	delete &rIntervalsVeсtor;
	delete willBeInsertedSet;
	//==========================================================================================

	return rushHourIntervalsSet;
}