#pragma once

//класс дл€ определени€ того от куда и до куда по итератору нужно удал€ть элементы из множества intervalsSet
//отдельный класс дл€ вы€снени€ индексов был выделен лишь за тем , что если индекс начала удалени€ в программе был установлен, то его уже 
//нельз€ было помен€ть. делаетс€ это с помощью переменной члена _eraseBeginIndexIsSet (см. setEraseBeginIndex(int) в файле EraseIndex.cpp)

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

