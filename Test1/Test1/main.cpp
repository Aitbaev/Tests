#include "Percentile.h"
#include "Average.h"
#include "CheckingInputFile.h"

using namespace std;

int main() {

	if (checkingInputFile())
	{
		vector<int> myVector;
		string buffer; //Строка-буффер, в которую будет помещаться каждое слово из входного файла для  записи в вектор MyVector
		ifstream fin("input.txt");

		while (true)
		{
			fin >> buffer; // считали первое слово из файла
			if (fin) // покуда существует ifstream объект
			{
				myVector.push_back(stoi(buffer));//добавляем слово в конец вектора
			}
			else
				break;
		}
		fin.close();

		cout << "90 percentile \t<" << Percentile(90, myVector) << ">" << endl;
		cout << "median \t\t<" << Percentile(50, myVector) << ">" << endl;
		cout << "average \t<" << Average(myVector) << ">" << endl;
		cout << "max \t\t<" << Percentile(100, myVector) << ">" << endl;
		cout << "min \t\t<" << Percentile(0, myVector) << ">" << endl;
	}

	return 0;
}