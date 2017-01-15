#include "CheckingInputFile.h"

bool checkingInputFile()
{


	for (int i = 0; i < inputFilesQuantity; i++)//���� �������� ������� �������� �����
	{//5 ������� ������ - ��� 5 ��������, � ������ �� ��� ������ ������� � ������ ��� ���� ������������ � ������� �������� ���

		string filesName = "input" + to_string(i + 1) + ".txt";//������� ������, ������� �������� ������ ����� 

		string buffer; //������-������ � ������� ������������ ������ ������ �� ������� �������� ����� ��� ��������
		ifstream fin(filesName);//������ ��� ���������� ������� �������� �����

		if (!fin.is_open()) // ���� ���� �� ������
		{
			cout << "File can not be opened\n"; // �������� �� ����
			return false;
		}
		else
		{
			regex rxForStringInInput("(0|([1-9][0-9]{0,7}))(\\.[0-9]{0,6})?");//���������� ��������� ��� �������� ������� ����� � ����� ������� �����
			int numberOfCheckedStrings = 0; //����������� ����������� ���� (��� ������ ������� � ������ ������)

			while (true)
			{ //���� �������� ���� � �������� ������ �����

				fin >> buffer; // ������� ������ ����� �� �����

				if (fin) // ������ ���������� ifstream ������
				{
					if (regex_match(buffer, rxForStringInInput) && numberOfCheckedStrings < stringsQuantityMustBeInInput)
						//���� ����������� ���������� ��������� � ����� ����������� ����� ������ ��� ����������� ����� ������� ���� � ������ �����
						numberOfCheckedStrings++;//���� �������� ������ �������������� ���������� ������������ ����������� �������� �������� �����
					else
					{//� ��������� ������
					 //���� ������� "����� ����������� ����� ������ ��� ����������� ����� ������� ���� � ������ �����" - �����������,
					 //(������������� �� ������ �������� �����-�� ����� �� ���������� ���������)
						if (numberOfCheckedStrings < stringsQuantityMustBeInInput)
						{	//�� ������� ��������� �� ������
							cout << "There is some error in " << filesName << " in value number " << numberOfCheckedStrings + 1 << "\n";
							//� ������� �������� ���������� false
							return false;
						}
						else
						{//� ��������� ������ (���� ����� ����� ������ �����������) ������� ��������������� ��������� �� ������
							cout << "Values in " << filesName << " are more than " << stringsQuantityMustBeInInput << "\n";
							//� ������� �������� ���������� false
							return false;
						}
					}
				}
				else
				{//� ��������� ������ ���� ������ ifstream �������� ������������

				 //� ��� ���� ����� ����������� ����� ������ ��� ����������� ����� ������� ���� � ������ �����
					if (numberOfCheckedStrings < stringsQuantityMustBeInInput)
					{	//���� ����� ����������� ����� ������ ����� ����
						if (numberOfCheckedStrings == 0)
						{	//������� ��������������� ��������� �� ������
							cout << "Input file is empty\n";
							//� ������� �������� ���������� false
							return false;
						}
						//������� ��������������� ��������� �� ������
						cout << "Values in " << filesName << " are less than " << stringsQuantityMustBeInInput << "\n";
						//� ������� �������� ���������� false
						return false;
					}
					//� ��������� ������ (��� ��� ���� ��� �������� �� ������ ������ �������) ������ ��������� ���� �������� ����� (����) � �����
					else
						break;
				}
			}
			fin.close();
		}



	}
	return true;

}