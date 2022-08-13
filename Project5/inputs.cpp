#include "inputs.h"

int input_int()
{
	int a;
	cin >> a;
	while (!cin.good())
	{
		cout << "������ �����, ������� ����� ��� ���: ";
		cin.clear();
		cin.ignore(255, '\n');
		cin >> a;
	}
	return a;
}

int number_from_interval(int min, int max)
{
	int number;
	bool is_correct_input = false;
	do
	{
		cout << "������� ����� � ��������� �� " << min << " �� " << max << '\n';
		number = input_int();
		is_correct_input = number >= min && number <= max;
	} while (!is_correct_input);
	return number;
}