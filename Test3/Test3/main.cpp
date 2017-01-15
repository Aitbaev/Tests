#include "CheckingInputFile.h"
#include "FindMax.h"
#include <ctime>
#include <array>
using namespace std;

int main() {

	if (checkingInputFile())//если проверка входных файлов прошла удачно
	{
		array<float, stringsQuantityMustBeInInput> sumdDistToCashBoxesEachHalfHour = { { 0.f } };
		//массив сумм длинн очередей до касс в каждые пол часа
		//всего элементов в массиве 16 (колличество производимых замеров в течении всего рабочего дня)
		//для начала все 16 занчений инициаллизируем нулями

		for (int i = 0; i < inputFilesQuantity; i++)
			//в данном цикле подготавливаем каждый из 5-ти файлов на считывание
		{	//создаем строку, которая является именем каждого последующего файла 
			string filesName = "input" + to_string(i + 1) + ".txt";

			string buffer;  //Строка-буффер в которую записывается каждая строка из каждого входного файла для проверки
			ifstream fin(filesName);//объект для считывания каждого входного файла

			for (int j = 0; j < stringsQuantityMustBeInInput; j++)
			{
				fin >> buffer;//считываем по слову из файла
				sumdDistToCashBoxesEachHalfHour[j] += stof(buffer);//увеличиваем соответствующее значение в массиве на соответствующее значение из 
																   //соответствующего входного файла
			}
			fin.close();
			//отделяем ifstream объект от файла
		}

		//записываем в вектор результат возврата функции,которая находит интервалы максимальной нагрузки
		vector<rushHourPeriod> rushHourPeriods = FindMax(sumdDistToCashBoxesEachHalfHour);
		cout << "RushHour periods are:\n";//вывод на экран интервалов максимальной нагрузки
		for (unsigned int i = 0; i < rushHourPeriods.size(); i++)
		{
			cout << rushHourPeriods[i].begin << " - " << rushHourPeriods[i].end << endl;
		}


	}
	return 0;
}