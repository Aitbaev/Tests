#include "FindMax.h"

vector<rushHourPeriod>  FindMax(array<float, stringsQuantityMustBeInInput> & sumdDistToCashBoxesEachHalfHour) {

	float max = sumdDistToCashBoxesEachHalfHour[0];
	//��� ������ ������� ������ ������� �� ������� ������������

	for (int i = 0; i < stringsQuantityMustBeInInput; i++)//� ����� ��������� 
		if (sumdDistToCashBoxesEachHalfHour[i] > max)// ���� ����������� ������� ������,
			max = sumdDistToCashBoxesEachHalfHour[i];//�� �������� ������������ ������� ��

	vector<int> maxLengthsTimes;
	//������ ������� �� ��������� ��������� ������������ �������� (� ������ ���� ����� ������ ������ ��� ����� �� ���� � ��� ��� ��������)
	for (int i = 0; i < stringsQuantityMustBeInInput; i++)
		if (max == sumdDistToCashBoxesEachHalfHour[i])
			maxLengthsTimes.push_back(i);

	//������ �������� ������������� �������� � ������������ ��������� ��������
	time_t now = time(NULL);

	struct tm nowInTm = *localtime(&now);

	//������� ��� ������� ����������� � 10:00 ����
	nowInTm.tm_hour = 10;
	nowInTm.tm_min = 0;
	nowInTm.tm_sec = 0;

	time_t openingTime = mktime(&nowInTm);//����� �������� ��������

	vector<rushHourPeriod> rushHourPeriods;//������ ����� ��� � ��������

										   //� ������ ����� ��������� ������ ���������� � ���������� ���� rushHourPeriod ������ ��� �������� � ����������� ���� ������
	for (unsigned int i = 0, consecutivePeriodsQuantity = 0; i < maxLengthsTimes.size(); i++)//consecutivePeriodsQuantity  - ����������� ���������������� 
	{																					//���������� ��� ���������� ����� � ��� ������ ���� ������������ 
																						//������ ������� ���� ������ 2 ��� ����� ���������� - ����� �� 
																						//���������� ���������
		while ((i != maxLengthsTimes.size() - 1) && (maxLengthsTimes[i + 1] - maxLengthsTimes[i] == 1))
		{//������ ������� �� ����� �� ���������� �������� � ������� ����� �������� � ����������� ���������� ����� 1
			consecutivePeriodsQuantity++; //�����������  ����������� ���������������� ����������
			i++;//� �������(�� ��� �� �������������� ��������� ��������)
		}

		time_t begin = openingTime + halfHour*maxLengthsTimes[i - consecutivePeriodsQuantity];//����� ������ ��������� (���������� ������
																							  //������ ��������� ���� consecutivePeriodsQuantity != 0)
		time_t end = begin + halfHour*(consecutivePeriodsQuantity + 1);//����� ����� ���������
		consecutivePeriodsQuantity = 0;//�������� ���������� ����������� ���������������� ����������

		struct tm begInInTm = *localtime(&begin);//��������� begin �� time_t � tm
		struct tm endInTm = *localtime(&end);//��������� end �� time_t � tm

		rushHourPeriod newOnePeriod;//������� ���������� ���� rushHourPeriod ��. FindMax.h

									//����� ��������� begInInTm � endInTm � ������, ������� ������ ���� � ������ 
		newOnePeriod.begin = to_string(begInInTm.tm_hour) + ":" + to_string(begInInTm.tm_min);
		newOnePeriod.end = to_string(endInTm.tm_hour) + ":" + to_string(endInTm.tm_min);
		//������ newOnePeriod � ������
		rushHourPeriods.push_back(newOnePeriod);
	}
	//������� ���������� ������
	return rushHourPeriods;
}