#pragma once
#include <vector>
#include <iostream>
#include "Point.h"
using namespace std;

double FindPointsLocationRelativelyToQuadranglesSide(Point linesFirstPoint, Point linesSecondPoint, Point quadranglesNotInLinePoint, Point checkedPoint);
void checkingUsersPoint(Point usersPoint, vector<Point> &myVector);