#include "EraseIndexes.h"


void EraseIndexes::incrementEraseEndIndex()
{
	_eraseEndIndex++;
}

void EraseIndexes::setEraseBeginIndex(int eraseBeginIndex)
{

	if (!_eraseBeginIndexIsSet)
	{
		_eraseBeginIndexIsSet = true;
		_eraseBeginIndex = eraseBeginIndex;
	}

}
void EraseIndexes::setEraseEndIndex(int eraseEndIndex)
{
	_eraseEndIndex = eraseEndIndex;
}
int EraseIndexes::getEraseBeginIndex()
{
	return _eraseBeginIndex;
}
int EraseIndexes::getEraseEndIndex()
{
	return _eraseEndIndex;
}


EraseIndexes::EraseIndexes()
{
	_eraseBeginIndexIsSet = false;
	_eraseEndIndex = 1;
	_eraseBeginIndex = 0;
}


EraseIndexes::~EraseIndexes()
{
}
