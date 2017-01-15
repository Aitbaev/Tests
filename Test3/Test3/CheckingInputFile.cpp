#include "CheckingInputFile.h"

bool checkingInputFile()
{


	for (int i = 0; i < inputFilesQuantity; i++)//цикл проверки каждого входного файла
	{//5 входных файлов - это 5 очередей, в каждом из них длинна очереди в каждые пол часа записываемые в течении рабочего дня

		string filesName = "input" + to_string(i + 1) + ".txt";//создаем строку, которая является именем файла 

		string buffer; //Строка-буффер в которую записывается каждая строка из каждого входного файла для проверки
		ifstream fin(filesName);//объект для считывания каждого входного файла

		if (!fin.is_open()) // если файл не открыт
		{
			cout << "File can not be opened\n"; // сообщить об этом
			return false;
		}
		else
		{
			regex rxForStringInInput("(0|([1-9][0-9]{0,7}))(\\.[0-9]{0,6})?");//регулярное выражение для проверки каждого слова в кажом входном файле
			int numberOfCheckedStrings = 0; //колличество проверенных слов (для ссылки наслово в случае ошибки)

			while (true)
			{ //цикл проверки слов в отдельно взятом файле

				fin >> buffer; // считали первое слово из файла

				if (fin) // покуда существует ifstream объект
				{
					if (regex_match(buffer, rxForStringInInput) && numberOfCheckedStrings < stringsQuantityMustBeInInput)
						//если выполняется регулярное выражение и число проверенных строк меньше чем колличество строк должных быть в каждом файле
						numberOfCheckedStrings++;//если проверка прошла инкрементируем переменную показывающую колличество прошедши проверку строк
					else
					{//в противном случае
					 //если условие "число проверенных строк меньше чем колличество строк должных быть в каждом файле" - выполняется,
					 //(соответствено не прошло проверку какое-то слово на регулярное выражение)
						if (numberOfCheckedStrings < stringsQuantityMustBeInInput)
						{	//то выводим сообщение об ошибке
							cout << "There is some error in " << filesName << " in value number " << numberOfCheckedStrings + 1 << "\n";
							//и функция проверки возвращает false
							return false;
						}
						else
						{//в противном случае (если число строк больше положенного) выводим соответствующее сообщение об ошибке
							cout << "Values in " << filesName << " are more than " << stringsQuantityMustBeInInput << "\n";
							//и функция проверки возвращает false
							return false;
						}
					}
				}
				else
				{//в противном случае если объект ifstream перестал существовать

				 //и при этом число проверенных строк меньше чем колличество строк должных быть в каждом файле
					if (numberOfCheckedStrings < stringsQuantityMustBeInInput)
					{	//если число проверенных строк вообще равно нулю
						if (numberOfCheckedStrings == 0)
						{	//выводим соответствующее сообщение об ошибке
							cout << "Input file is empty\n";
							//и функция проверки возвращает false
							return false;
						}
						//выводим соответствующее сообщение об ошибке
						cout << "Values in " << filesName << " are less than " << stringsQuantityMustBeInInput << "\n";
						//и функция проверки возвращает false
						return false;
					}
					//в противном случае (тут уже если все проверки на ошибки прошли успешно) просто завершаем цикл проверки строк (слов) в файле
					else
						break;
				}
			}
			fin.close();
		}



	}
	return true;

}