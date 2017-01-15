#include "Percentile.h"

using namespace std;


int compare(const void * x1, const void * x2)   // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}

double Percentile(double percNum, vector<int> &myVector) {

	if (percNum < 0 || percNum>100) {
		cout << "Percentiles value is out of boundary\n";
		exit(0);
	}

	qsort(&myVector[0], myVector.size(), sizeof(int), compare);

	//���������� ������������� ������ ��� ������� ������ �������� ������ 1 �������, �������� ����� ������� ����� ��������������� 
	//���� �� ����� ������� �� ���� ������, ��� ������� ����� ����� - ��� ������ �������, � ������� ������ - ���������.
	//����� ������� ���� �������� ��� ������������� ������ ������ �������� ����� ����� {-2, 7, 11, 11} - �� ������������ ������� 
	//�������� ������ 1 ����� �������� [-2;14] ������������ ��� , �� ��� ���� �������� �� ��� ���� ��� ���� ���������� ����� ������� -2 � 7 
	//����� ������ ���������� ����� ������� 7 � 11, � ��� ����� 11 � 11 ����� ����������� ��� 2 �������, ������ �� ������� ������ �� ������ 
	//����� �� ����������. ����� ������� ��� ����� ������ ������ �������� ���������������.

	//�������� ��� ��������������� ������ �� �������������� ��������� � ������� ����� ���������� ������� ����������

	if (myVector.size() == 1) {
		return myVector[0];//� ������ ���� � ������� ����� ��������� ����� 1, ����� ���� ������� � ����� �������� ����� �����������
	}


	double 	interval = 1.0 / (myVector.size() - 1); //���� �� � ������� ����� ��������� ������ 1, ������������� ������������ ������ 1 
													//����������� �� n-1 �������������� �������, ��� n - ����� ��������� �������
	int leftBoundInd = static_cast<int>((percNum / 100.0) / interval);//������� ������ ����� ������ ��������� � ������� ����� ������ ����������, ���� 
																	  //������������  � ������ �-��� ����� ���������� �� 100 (����� ������� �� ������ 
																	  //�� ������ ���������� ����� ������� �������������� ������������ ������� 1) � ��
																	  // �������� ��������������� ��������� � ����� ����� �����.

	int rightBoundInd;
	if (leftBoundInd == myVector.size() - 1)//���� ����� ������� ��������� - ��� �������� ����� �������
		rightBoundInd = leftBoundInd;			//������ ������ ������� ����� ����� ������ �����
	else							   //� ��������� �� ������
		rightBoundInd = leftBoundInd + 1;   //������ ������ ������� ����� ����� ������ �����+1



	double percentile = ((((percNum / 100.0) - interval*leftBoundInd) / interval))*(myVector[rightBoundInd] - myVector[leftBoundInd]) + myVector[leftBoundInd];
	//�� ���������� ����������� � ����� ������� �������������� ������������ ������ 1 (percNum / 100.0) ������� �������� ��������� ����������� �� ������ 
	//����� ������� ��������� interval*leftBoundInd � ������� �� ���� ������� ���������� - ��� ������� ������� �� ������� ����� ���������� �������
	//����� ������� �� �������� ��������� ��� ���������������, ����� ��� �������� ���������� ���������� �������� �� ��������
	// ����� ��������� �� ������� ������ ������� ��������� �� �������� �� ������� �� ����� ������� ���������, ����� ������� �� 
	//�������� ����� ������� ���������, �� ������� � ��������� ������ ��������. �������� � ����� �������� ��������� �������� �� ������� �� ����� 
	//������� ���������.

	return percentile;
}