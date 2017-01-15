#include "Percentile.h"
#include "Average.h"
#include "CheckingInputFile.h"

using namespace std;

int main() {

	if (checkingInputFile())
	{
		vector<int> myVector;
		string buffer; //������-������, � ������� ����� ���������� ������ ����� �� �������� ����� ���  ������ � ������ MyVector
		ifstream fin("input.txt");

		while (true)
		{
			fin >> buffer; // ������� ������ ����� �� �����
			if (fin) // ������ ���������� ifstream ������
			{
				myVector.push_back(stoi(buffer));//��������� ����� � ����� �������
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