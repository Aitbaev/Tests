#pragma once

//класс для определения того от куда и до куда по итератору нужно удалять элементы из множества intervalsSet
//отдельный класс для выяснения индексов был выделен лишь за тем , что если индекс начала удаления в программе был установлен, то его уже 
//нельзя было поменять. делается это с помощью переменной члена _eraseBeginIndexIsSet (см. setEraseBeginIndex(int) в файле EraseIndex.cpp)

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

