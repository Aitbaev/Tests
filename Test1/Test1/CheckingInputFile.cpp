#include "CheckingInputFile.h"

bool checkingInputFile()
{
	string buffer; //Строка-буффер, в которую будет помещаться каждое слово из входного файла для проверки
	ifstream fin("input.txt");
	if (!fin.is_open()) // если файл не открыт
	{
		cout << "File can not be opened\n"; // сообщить об этом
		return false;
	}

	else
	{

		//проверка заполнен ли файл вообще чем либо================================================================
		fin >> buffer;
		if (buffer == "") {
			cout << "Input file is empty\n";
			return false;
		}
		fin.seekg(0, ios::beg);//возврат курсора в начало файла
							   //==========================================================================================================

		regex rx("(0|(-?[1-9][0-9]{0,8}))");//регулярное выражение, которым проверяется подходит ли слово, чтоб стать целочисленным значением,
											//Также введено ограничение по длинне числа (не более 9-ти разрядов,)
		while (true)
		{

			fin >> buffer; // считали первое слово из файла

			if (fin) // покуда существует ifstream объект
			{

				if (!regex_match(buffer, rx))//если считанное слово подходит под регулярное выражение rx

				{
					cout << "There is illegal value in input file\n";
					return false;
				}

			}

			else
				break;
		}
		fin.close();

	}
	return true;
}