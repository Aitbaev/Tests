#include "CheckingUsersPoint.h"


void checkingUsersPoint(Point point, vector<Point> &apex)
{   //для того чтоб не делать лишних операций в случае если рассматриваемая точка сама вляется вершиной четырехугольника
	//проверим этот факт до выподнения основного алгоритма
	if (apex[0] == point || apex[1] == point || apex[2] == point || apex[3] == point)//итак если точка совпадает с одно из вершин
	{
		cout << "The point is the quadrangles apex\n";//выводим на экран сообщение об этом
		return;										  //выходим из функции
	}
	//Все точки треугольника (и любого выпуклого многоугольника) должны лежать по одну сторону от прямой, проходящей через каждую его сторону.
	//Уравнение прямой, проходящей через точки A и B выглядит следующим образом
	//(x-xA)(yB-yA)-(y-yA)(xB-xA) = 0
	//Уравнение записанно в такой форме, чтобы не приходилось выполнять деление и выполнять условие для нуля в знаменателе.

	//Теперь для любой точки(x;y) можно вычислить левую часть приведенного равенства.
	//Для точек, лежащих на прямой мы должны получать ноль.
	//В тоже время прямая разобьёт плоскость на две полуплоскости.Точки лежащие в одной полуплоскости будут давать положительные значения.
	//А точки из другой полуплоскости — отрицательные.
	//Можно проверить первое условие — принадлежит ли точка D (xD, yD)  той же полуплоскости, что и точка C (xC, yC)  относительно прямой AB
	//Для этого подставим обе точки в левую часть приведенного выше уравнения прямой и убедимся, что полученые значения одного и того же знака.
	//А если одна из точек даст точно ноль, то это означает, что точка лежит на прямой.
	//По условию задачи это может быть только точка D.Тогда она принадлежит четырехугольнику независимо от знака выражения, вычисленного для точки C.

	//выполним данную проверку для каждой из сорон четырехугольника, для этого вызовем функцию определяющую положение точки
	//относительно стороны четерехугольника
	double firstSideChek = FindPointsLocationRelativelyToQuadranglesSide(apex[0], apex[1], apex[2], point);
	double secondSideCheck = FindPointsLocationRelativelyToQuadranglesSide(apex[1], apex[2], apex[3], point);
	double thirdSideCheck = FindPointsLocationRelativelyToQuadranglesSide(apex[2], apex[3], apex[0], point);
	double fourthSideCheck = FindPointsLocationRelativelyToQuadranglesSide(apex[3], apex[0], apex[1], point);
	//нельзя утверждать, что для любой точки на прямой наши приближённые вычисления обязаны дать точный ноль.
	//можно только утверждать, что если проведенные с доступной нам точностью вычисления дали ноль, то мы вынуждены считать данную точку 
	//лежащей на данной прямой.

	if (firstSideChek >= 0 && secondSideCheck >= 0 && thirdSideCheck >= 0 && fourthSideCheck >= 0)
		//если все 4 вышеуказанных значения больше либо равны нулю, то рассматриваемая точка точно делит в пределах четырехугольника
		//(либо внутри, либо на одной из сторон, случай с точкой являющейся вершиной мы рассмотрели в начале данной функции)
	{
		if (firstSideChek == 0 || secondSideCheck == 0 || thirdSideCheck == 0 || fourthSideCheck == 0)
			//если одно 4 вышеуказанных значений рано нулю, то точка лежит на стороне четырехугольника
			cout << "The point belongs to the side of quadrangle\n";
		else
			//в противном случае точка просто внутри четырехугольника
			cout << "The point belongs to quadrangle\n";
	}
	else
		//в противном случае точка лежит снаружи четырехугольника
		cout << "The point is outside the quadrangle\n";
}

double FindPointsLocationRelativelyToQuadranglesSide(Point linesFirstPoint, Point linesSecondPoint, Point quadranglesNotInLinePoint, Point checkedPoint)
//linesFirstPoint - первая точка отрезка 
//linesSecondPoint - вторая точка отрезка 
//quadranglesNotInLinePoint - точка четырехугольника не лежащая на прямой относительно которой мы рассматриваем ее положение в купе с checkedPoint
//checkedPoint - точка положение клторой мы непостредственно рассматриваем
{	//первая часть до знака умножения (того что как бы делит возвращаемое значение пополам)  - результат подстановки в правую часть
	//уравнения прямой (x-xA)(yB-yA)-(y-yA)(xB-xA) вместо x и y значений координат точки quadranglesNotInLinePoint
	//вместо xA и yA значений координат точки linesFirstPoint, вместо xB и yB значений координат точки linesSecondPoint

	//вторая часть после знака умножения (того что как бы делит возвращаемое значение пополам)  - результат подстановки в правую часть
	//уравнения прямой (x-xA)(yB-yA)-(y-yA)(xB-xA) вместо x и y значений координат точки checkedPoint
	//вместо xA и yA значений координат точки linesFirstPoint, вместо xB и yB значений координат точки linesSecondPoint

	//таким образом если умножение этих двух значениц дат значение больше нуля, значит оба множетеля были одного знака =>
	//обе точки лежат в одной полуплоскости, в случае отрицательног результата точки лежат в разных полуплоскостях, в случе если результат
	//равен нулю, точка checkedPoint - лежит на рассматриваемой  в данном вызове функции прямой, точка quadranglesNotInLinePoint - не может 
	//лежать на на рассматриваемой  в данном вызове функции прямой.
	return ((quadranglesNotInLinePoint.GetX() - linesFirstPoint.GetX())*(linesSecondPoint.GetY() - linesFirstPoint.GetY()) -
		(quadranglesNotInLinePoint.GetY() - linesFirstPoint.GetY())*(linesSecondPoint.GetX() - linesFirstPoint.GetX()))
		*
		((checkedPoint.GetX() - linesFirstPoint.GetX())*(linesSecondPoint.GetY() - linesFirstPoint.GetY()) -
		(checkedPoint.GetY() - linesFirstPoint.GetY())*(linesSecondPoint.GetX() - linesFirstPoint.GetX()));
}

