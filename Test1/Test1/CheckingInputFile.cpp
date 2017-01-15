#include "CheckingInputFile.h"

bool checkingInputFile()
{
	string buffer; //������-������, � ������� ����� ���������� ������ ����� �� �������� ����� ��� ��������
	ifstream fin("input.txt");
	if (!fin.is_open()) // ���� ���� �� ������
	{
		cout << "File can not be opened\n"; // �������� �� ����
		return false;
	}

	else
	{

		//�������� �������� �� ���� ������ ��� ����================================================================
		fin >> buffer;
		if (buffer == "") {
			cout << "Input file is empty\n";
			return false;
		}
		fin.seekg(0, ios::beg);//������� ������� � ������ �����
							   //==========================================================================================================

		regex rx("(0|(-?[1-9][0-9]{0,8}))");//���������� ���������, ������� ����������� �������� �� �����, ���� ����� ������������� ���������,
											//����� ������� ����������� �� ������ ����� (�� ����� 9-�� ��������,)
		while (true)
		{

			fin >> buffer; // ������� ������ ����� �� �����

			if (fin) // ������ ���������� ifstream ������
			{

				if (!regex_match(buffer, rx))//���� ��������� ����� �������� ��� ���������� ��������� rx

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