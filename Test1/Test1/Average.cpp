
#include "Average.h"

double Average(vector<int> &myVector) {

	double average = 0;

	for (int i = 0; i < myVector.size(); i++)
	{
		average += myVector[i];
	}
	average /= myVector.size();

	return average;
}