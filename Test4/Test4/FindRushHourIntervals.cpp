
#include "FindRushHourIntervals.h"

multiset<Interval> FindRushHourIntervals(vector<Interval>* intervalsVector)
{
	vector<Interval> &rIntervalsVe�tor = *intervalsVector;

	multiset<Interval>* intervalsSet = new multiset<Interval>;

	//=================================================================================================
	Interval nominal;//������� ����������� ��������

	tm IntervalsCameTime;
	localtime_s(&IntervalsCameTime, &now);
	tm IntervalsGoneTime;
	localtime_s(&IntervalsGoneTime, &now);

	IntervalsCameTime.tm_hour = 8;//������������� � ������ ��������� ����� �������� �����
	IntervalsCameTime.tm_min = 0;
	IntervalsGoneTime.tm_hour = 22;//������������� � ����� ��������� ����� �������� �����
	IntervalsGoneTime.tm_min = 0;

	nominal.setBeginTime(mktime(&IntervalsCameTime));
	nominal.setEndTime(mktime(&IntervalsGoneTime));
	nominal.setClientsQuantity(0);//������������� ����������� ����� � ��������� - ����

	intervalsSet->insert(nominal);
	multiset<Interval> * willBeInsertedSet = new multiset<Interval>;//������ �������� � ��������� (� ������������ �� ������ ������) ���������� 
																	//��� ����������� ���������� � intervalsSet . ���� �������� ���������� ��-�� ����, ��� �� ������� � ���������� intervalsSet - ����� ���������
																	// �� �� ����� �������� ��������� (������� �� ���� �������� ��� ��������� ��). ������ � ��� ��������� ����������� ��������� ������� ����� ���� ��� ��
																	//�������� ������ � ����� (��� ������� ������ � �����������) �� ������� � intervalsSet ��� �������� ��  willBeInsertedSet, � ���  willBeInsertedSet - 
																	//�������
																	//=================================================================================================



																	//���������� ��������� �������� ��� ������� ������, ��� ������  - ����� �������� �����, ����� ����� ��������
																	//�� ���� ������� �� ����� ������������ ��������� ��������� �� ������� rIntervalsVe�tor
																	//������� ������� ����-����������� �������� nominal, ����� ������� �� ��������� ���� �������
																	//���������� � ��� ������� ����� �������� � ������� ����� �� ��������

																	//� ����������� ����� ����� ��������� ��������� �� rIntervalsVe�tor ������� � willBeInsertedSet
																	//��� ���� � ������ ���������� ������� ������ �� ����� ���� ��� ����� �������� ����� �� ����� �� �������
																	//��������� �� ����� � ���� ���� ����� ��� ������ ��������. �������� nominal �������� ��� ���� ���� � ��� �� ���� ������ �� ���� �������� �������
																	//� ������� �������� �� �������� �����
	for (unsigned int i = 0; i < rIntervalsVe�tor.size(); i++)
	{
		EraseIndexes eraseIndexesInstance;//������� ������ "������ �������� ��� ��������"(��. EraseIndexes.h)

		Interval temp = rIntervalsVe�tor[i];//�������� �������� ������� �������������� �� ��������� ���������� ��� ���������� ������

											//� ������ ����� ���������� ����������� �� rIntervalsVector �������� � ����� ������������ � intervalsSet �����������
		for (auto j = intervalsSet->begin(); j != intervalsSet->end(); j++, eraseIndexesInstance.incrementEraseEndIndex())
		{

			//�� ���������� ��������� intervalsSet ������������� ��� ������� ������������� ���������� �������
			if (temp.getBeginTime() >= j->getBeginTime() && temp.getBeginTime() < j->getEndTime())
			{

				//� ���������� ����� ������� "������ �������� ��� ��������" ��������� ������ ������ ��������
				eraseIndexesInstance.setEraseBeginIndex(eraseIndexesInstance.getEraseEndIndex() - 1);

				//�������� 2 ������������� �������� ������������ ������� �� �������: leftDifference - ����� ������� temp ��������� �
				//������� ��������� ��� �������� j � rightDifference - ����� ������ temp ��������� �
				//������ ��������� ��� �������� j
				int leftDifference = static_cast<int>(difftime(temp.getBeginTime(), j->getBeginTime()));
				int rightDifference = static_cast<int>(difftime(j->getEndTime(), temp.getEndTime()));

				//==========================================================================================================================================
				//����� �� ���������� (//==============) ����������� �������� � ��������� ����� ����������  ��� ���������� � willBeInsertedSet, � ����� 
				// � intervalsSet, � ����� ���������� �������� ������� ����� ������� (���������� �������� �������� ����� ������ ������ EraseIndexes)
				if (leftDifference == 0) //���������� �������� ���� ������
				{
					Interval prevInterval;//������� ���������� � ������� ����� ������������ ���������� (�� ���� �� ������� ��������� �������� j)
										  //��������
					if (j != intervalsSet->begin()) //���� j �� ������ �� ��������� 
					{
						j--;//�� �������������� j 
						prevInterval = *j;// ���������� �������� ��� ���������� j � ���������� ��������
						j++;//���������� j �� �� ����� ���� �� ��������
					}
					if ((j->getClientsQuantity() + 1) == prevInterval.getClientsQuantity())
						//���� � ��������� � ����������� ��������� ���������� �������� ����� ����������
					{
						// � ������� "������ �������� ��� ��������" ��������� ������ ������ �������� �� 1 ������ ���� ������� � ����������
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
				//����� ������������� �������� � ��������� ����� ����������  ��� ���������� � willBeInsertedSet, � ����� 
				// � intervalsSet, � ����� ���������� �������� ������� ����� ������� 
			}
		}

		multiset<Interval>::iterator beginIterator = intervalsSet->begin();
		advance(beginIterator, eraseIndexesInstance.getEraseBeginIndex()); //����� ���������� ���� �������
																		   //beginIterator �������� ��������� �� �� ��c�� ������ ����� �������� �������� ��������� �� intervalsSet

		multiset<Interval>::iterator endIterator = intervalsSet->begin();
		advance(endIterator, eraseIndexesInstance.getEraseEndIndex());//����� ���������� ���� �������
																	  //endIterator �������� ��������� �� �� ��c�� ������ ����� ����������� �������� ��������� �� intervalsSet

		intervalsSet->erase(beginIterator, endIterator);//������� ������ ���������
		intervalsSet->insert(willBeInsertedSet->begin(), willBeInsertedSet->end());//��������� �����
		willBeInsertedSet->erase(willBeInsertedSet->begin(), willBeInsertedSet->end());//������� ��������� ����������� ������� �� ����������
	}

	/*��� ����� ���������� � ����� ��������� ������� ������� ����� ����===========================================================================
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

	//������� �������� � ����� ������� ������������ ����� � ���
	//==========================================================================================
	int peopleQuantity = 0;

	for (auto i = intervalsSet->begin(); i != intervalsSet->end(); i++)
	{
		if (i->getClientsQuantity() > (unsigned)peopleQuantity)
			peopleQuantity = i->getClientsQuantity();
	}
	//==========================================================================================
	multiset<Interval> rushHourIntervalsSet;

	//��� ��������� � ���������� ������������ ����� � ��� ���������� � ������������ �������� ��������� rushHourIntervalsSet
	//==========================================================================================
	for (auto i = intervalsSet->begin(); i != intervalsSet->end(); i++)
	{
		if (i->getClientsQuantity() == peopleQuantity)
			rushHourIntervalsSet.insert(*i);
	}
	//==========================================================================================

	//������� ������ ��������� �� ������� � ������������ ������
	//==========================================================================================
	delete intervalsSet;
	delete &rIntervalsVe�tor;
	delete willBeInsertedSet;
	//==========================================================================================

	return rushHourIntervalsSet;
}