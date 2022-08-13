#include "menus.h"

bool second_menu(fstream& file, char* file_name)
{
	cout << "0) �����" << '\n';
	cout << "1) ������� ���� �� �����" << '\n';
	cout << "2) �������� ������" << '\n';
	cout << "3) ������� ������" << '\n';
	cout << "4) �������� ������" << '\n';
	cout << "5) �������������� � ��������� ����" << '\n';
	cout << "6) ������� ������ � ����� ���� � �������� �������� � ����� ���������" << '\n';
	int choice = number_from_interval(0, 6);
	switch (choice)
	{
	case 1:
		print_file(file);
		break;
	case 2:
		add_record(file);
		break;
	case 3:
		print_file(file);
		delete_record(file, file_name);
		break;
	case 4:
		print_file(file);
		change_record(file);
		break;
	case 5:
		convert_binary_to_txt(file, file_name);
		break;
	case 6:
		copy_from_bin_to_bin(file, file_name);
		break;

	}
	return !choice;
}

bool first_menu(fstream& file, char* file_name)
{
	cout << "0) ����� �� ���������" << '\n';
	cout << "1) ������� ������������ ����" << '\n';
	cout << "2) ������� ����� ����" << '\n';
	int choice = number_from_interval(0, 2);
	switch (choice)
	{
	case 1:
		open_file(file, file_name);
		break;
	case 2:
		create_file(file, file_name, 1);
		break;
	}
	return !choice;
}