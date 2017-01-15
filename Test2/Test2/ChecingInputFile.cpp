#include "CheckingInputFile.h"

bool checkingInputFile()
{

	string buffer; //Строка-буффер
	ifstream fin("input.txt");

	if (!fin.is_open()) // если файл не открыт
	{
		cout << "File can not be opened\n"; // сообщить об этом
		return false;
	}
	else
	{
		regex rxForStringInInput("(<(((0|(-?[1-9][0-9]{0,7}))(\\.[0-9]{0,8})?)|(-0\\.[0-9]{0,8}))>){2}");
		//регулярное выражение для проверки строк из входного файла
		int numberOfCheckedStrings = 0;//число проверенных строк

		while (true) {

			fin >> buffer; // считали первое слово из файла
			if (fin) // покуда существует ifstream объект
			{
				if (regex_match(buffer, rxForStringInInput) && numberOfCheckedStrings < stringsQuantityMustBeInInput)//
					numberOfCheckedStrings++;
				else
				{
					if (numberOfCheckedStrings < stringsQuantityMustBeInInput)
					{
						cout << "There is some error in input file in value number " << numberOfCheckedStrings + 1 << "\n";
						return false;
					}
					else
					{
						cout << "Values in input file are more than " << stringsQuantityMustBeInInput << "\n";
						return false;
					}
				}
			}
			else
			{

				if (numberOfCheckedStrings < stringsQuantityMustBeInInput)
				{
					if (numberOfCheckedStrings == 0)
					{
						cout << "Input file is empty\n";
						return false;
					}
					cout << "Values in input file are less than " << stringsQuantityMustBeInInput << "\n";
					return false;
				}
				else
					break;
			}
		}
		fin.close();
	}
	return true;
}