#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <string.h>
#include <array>
#include "CheckingInputFile.h"

using namespace std;

const time_t halfHour = 1800;//пол часа в секундах

struct rushHourPeriod
{
	string begin;
	string end;
};
vector<rushHourPeriod>  FindMax(array<float, stringsQuantityMustBeInInput>&);

