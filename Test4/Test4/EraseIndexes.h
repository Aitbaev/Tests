#pragma once

//����� ��� ����������� ���� �� ���� � �� ���� �� ��������� ����� ������� �������� �� ��������� intervalsSet
//��������� ����� ��� ��������� �������� ��� ������� ���� �� ��� , ��� ���� ������ ������ �������� � ��������� ��� ����������, �� ��� ��� 
//������ ���� ��������. �������� ��� � ������� ���������� ����� _eraseBeginIndexIsSet (��. setEraseBeginIndex(int) � ����� EraseIndex.cpp)

class EraseIndexes
{
private:
	int _eraseBeginIndex;
	int	_eraseEndIndex;
	bool _eraseBeginIndexIsSet;
public:

	void incrementEraseEndIndex();
	void setEraseBeginIndex(int);
	void setEraseEndIndex(int);
	int getEraseBeginIndex();
	int getEraseEndIndex();
	EraseIndexes();
	~EraseIndexes();
};

