#pragma once
#include <set>
#include <vector>
#include "Interval.h"
#include "EraseIndexes.h"
#include "CheckingInputFile.h"

using namespace std;
multiset<Interval> FindRushHourIntervals(vector<Interval>* Intervals);