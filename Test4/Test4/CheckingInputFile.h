#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <ctime>
#include "Interval.h"

using namespace std;

const time_t now = time(NULL);

const int oneMinute = 60;//минута (60 секунд)

bool checkingInputFile(vector<Interval>* Intervals);