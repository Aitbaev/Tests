#include "CheckingInputFile.h"
#include "FindMax.h"
#include <ctime>
#include <array>
using namespace std;

int main() {

	if (checkingInputFile())//���� �������� ������� ������ ������ ������
	{
		array<float, stringsQuantityMustBeInInput> sumdDistToCashBoxesEachHalfHour = { { 0.f } };
		//������ ���� ����� �������� �� ���� � ������ ��� ����
		//����� ��������� � ������� 16 (����������� ������������ ������� � ������� ����� �������� ���)
		//��� ������ ��� 16 �������� ��������������� ������

		for (int i = 0; i < inputFilesQuantity; i++)
			//� ������ ����� �������������� ������ �� 5-�� ������ �� ����������
		{	//������� ������, ������� �������� ������ ������� ������������ ����� 
			string filesName = "input" + to_string(i + 1) + ".txt";

			string buffer;  //������-������ � ������� ������������ ������ ������ �� ������� �������� ����� ��� ��������
			ifstream fin(filesName);//������ ��� ���������� ������� �������� �����

			for (int j = 0; j < stringsQuantityMustBeInInput; j++)
			{
				fin >> buffer;//��������� �� ����� �� �����
				sumdDistToCashBoxesEachHalfHour[j] += stof(buffer);//����������� ��������������� �������� � ������� �� ��������������� �������� �� 
																   //���������������� �������� �����
			}
			fin.close();
			//�������� ifstream ������ �� �����
		}

		//���������� � ������ ��������� �������� �������,������� ������� ��������� ������������ ��������
		vector<rushHourPeriod> rushHourPeriods = FindMax(sumdDistToCashBoxesEachHalfHour);
		cout << "RushHour periods are:\n";//����� �� ����� ���������� ������������ ��������
		for (unsigned int i = 0; i < rushHourPeriods.size(); i++)
		{
			cout << rushHourPeriods[i].begin << " - " << rushHourPeriods[i].end << endl;
		}


	}
	return 0;
}