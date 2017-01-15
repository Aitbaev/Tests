#include "CheckingInputFile.h"

bool checkingInputFile(vector<Interval>* intervalsVector)
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


		regex rxForStringInInput("((((0[8-9])|(1[0-9])|(2[0-1])):[0-5][0-9]))-((((0[8-9])|(1[0-9])|(2[0-1])):[0-5][0-9])|(22:00))");
		//регулярное выражение, которым проверяется подходит ли слово, чтоб стать временем прихода и ухода клиента
		regex rxForParsing("[0-9][0-9]"); //регулярное выражение для парсинга строки из входного файла
		smatch result;
		int numberOfCheckedStrings = 0;//число проверенных строк

		while (true)
		{

			fin >> buffer; // считали первое слово из файла

			if (fin) // покуда существует ifstream объект
			{
				Interval newInterval;//создаем новый интервал
				if (regex_match(buffer, rxForStringInInput))//если считанное слово подходит под регулярное выражение rxForStringInInput
				{
					numberOfCheckedStrings++;//инкрементируем счетчик проверенных строк

											 //создаем время прихода и ухода в формате tm структуры
											 //и инициаллизируем даным моментом
					tm IntervalsCameTime;
					localtime_s(&IntervalsCameTime, &now);
					tm IntervalsGoneTime;
					localtime_s(&IntervalsGoneTime, &now);


					for (int i = 0; i < 4; i++)//цикл в котором переводим строку из входного файла в время прихода и ухода
					{//цикл выполняется 4 раза (час прихода:минута прихода-час ухода:минута ухода)

						regex_search(buffer, result, rxForParsing);//функция записывает первое значение удовлетворяющее регулярному выражению 
																   //в result[0] 

						switch (i)
						{
						case 0: {
							IntervalsCameTime.tm_hour = stoi(result[0]);
							break;
						}
						case 1: {
							IntervalsCameTime.tm_min = stoi(result[0]);
							break;
						}
						case 2: {
							IntervalsGoneTime.tm_hour = stoi(result[0]);
							break;
						}
						case 3: {
							IntervalsGoneTime.tm_min = stoi(result[0]);
							break;
						}
						default:
							break;
						}

						buffer = result.suffix().str();//от строки buffer как бы отрезается все что идет до части совпадающей с result[0]
													   //включительно result[0]
					}


					newInterval.setBeginTime(mktime(&IntervalsCameTime));//устанавливаем в новом интервале время начала
					newInterval.setEndTime(mktime(&IntervalsGoneTime));//и время конца

																	   //проверка того что время ухода клиента не раньше времени прихода
					if (static_cast<int>(difftime(newInterval.getEndTime(), newInterval.getBeginTime())) < oneMinute)
					{//в случае не выполнения данного условия выводится соответствующее сообщение об ошибке
						cout << "Error in value " << numberOfCheckedStrings << ". Each  client's gone time musn't be less than clients came \n";
						return false;
					}
					//проверка упорядоченности входного файла (для удобства было решено чтобы время прихода кажого последующего клиента банка было
					//не раньше предыдущего)
					if ((intervalsVector->size() > 0) && (intervalsVector->back().getBeginTime() > newInterval.getBeginTime()))
					{//в случае не выполнения данного условия выводится соответствующее сообщение об ошибке
						cout << "Error in value " << numberOfCheckedStrings
							<< ". Each subsequent Interval's coming time musn't be less than coming time of the previous one\n";
						return false;
					}
					else //в случае удачных предыдущих проверок записываем в вектор новый интервал
						intervalsVector->push_back(newInterval);

				}

				else//в противом случае если слово не подходит под регулярное выраение 
				{//выводим соответствующее сообщение об ошибке
					cout << "There is some error in input file in value number " << numberOfCheckedStrings + 1 << "\n";
					return false;
				}
			}


			else//в противном случае (когда файл завершен)
				break;//завершаем выполнение цикла

		}
		fin.close();//отделяем файл от ifstream объекта

	}
	//если все проверки выполненны, то функция возвращает true
	return true;
}