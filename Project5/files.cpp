#include "files.h"
#include "STUDENT.h"

void print_file(fstream& file)
{
	file.clear();
	file.seekg(0, ios::beg);
	STUDENT student;
	int i = 0;
	bool is_file_empty = true;
	while (file.read((char*)&student, sizeof(STUDENT)))
	{
		cout << i << ": ";
		print_student_to_console(student);
		cout << '\n';
		i++;
		is_file_empty = false;
	}
	if (is_file_empty)
		cout << "Файл пуст" << '\n';
}

void open_file(fstream& file, char* file_name)
{
	normalize_extension(file_name, ".bin");
	if (is_file_exist(file_name))
	{
		file.open(file_name, ios::out | ios::in | ios::binary);
		cout << "Файл открыт" << '\n';
	}
	else
	{
		cout << "Такого файла не существует" << '\n';
		cout << "0) Вернуться в меню" << '\n';
		cout << "1) Создать его" << '\n';
		int choice = number_from_interval(0, 1);
		if (choice)
		{
			ofstream temp(file_name);
			temp.close();
			file.open(file_name, ios::out | ios::in | ios::binary);
			cout << "Файл создан" << '\n';
		}
	}
}

void create_file(fstream& file, char* file_name, int mode)
{
	normalize_extension(file_name, ".bin");
	if (!is_file_exist(file_name))
	{
		ofstream temp(file_name);
		temp.close();
		file.open(file_name, ios::in | ios::out | ios::binary);
		cout << "Файл создан" << '\n';
	}
	else
	{
		if (mode == 0)
		{
			cout << "Такой файл уже существует" << '\n';
			cout << "0) Вернуться в меню" << '\n';
			cout << "1) Открыть его" << '\n';
			int choice = number_from_interval(0, 1);
			if (choice)
			{
				file.open(file_name, ios::in | ios::out | ios::binary);
				cout << "Файл открыт" << '\n';
			}
		}
		else
			cout << "Такой файл уже существует\n";
	}
}

bool is_correct_file_name(char* file_name)
{
	char invalid_chars[] = "/\\:?*<>,|\"";
	int name_length = strlen(file_name), array_size = sizeof(invalid_chars) / sizeof(char);
	if (!name_length)
		return false;
	for (int i = 0; i < name_length; i++)
	{
		for (int j = 0; j < array_size; j++)
		{
			if (file_name[i] == invalid_chars[j])
				return false;
		}
	}
	return true;
}

bool is_correct_extension(char* file_name, const char* extension)
{
	int name_length = strlen(file_name), extension_length = strlen(extension);
	int difference_in_length = name_length - extension_length;
	if (difference_in_length <= 1)
		return false;
	for (int i = difference_in_length; i < name_length; i++)
	{
		if (file_name[i] != extension[i - difference_in_length])
			return false;
	}
	return true;
}

bool is_file_exist(char* file_name)
{
	ifstream file(file_name);
	bool result = file.is_open();
	file.close();
	return result;
}

void normalize_extension(char* file_name, const char* extension)
{
	cout << "Введите имя файла" << '\n';
	cin >> file_name;
	while (!is_correct_file_name(file_name))
	{
		cout << "Введено некорректное имя файла, повторите попытку" << '\n';
		cin >> file_name;
	}
	if (!is_correct_extension(file_name, extension))
		strcat_s(file_name, char_size, extension);
}

void copy_from_bin_to_bin(fstream& file, char* file_name)
{
	char new_file_name[char_size];
	fstream new_file;
	do
	{
		create_file(new_file, new_file_name, 1);
	} while (!new_file.is_open());
	STUDENT student;
	while (file.read((char*)&student, sizeof(STUDENT)))
		new_file.write((char*)&student, sizeof(STUDENT));
	cout << "0) Вернуться в меню" << '\n';
	cout << "1) Добавить студента" << '\n';
	int choice = number_from_interval(0, 1);
	while (choice)
	{
		add_record(new_file);
		cout << "0) Вернуться в меню" << '\n';
		cout << "1) Добавить студента" << '\n';
		choice = number_from_interval(0, 1);
	}
}

bool convert_binary_to_txt(fstream& file, char* file_name)
{
	file.clear();
	file.seekg(0, ios::beg);
	bool result = true;
	normalize_extension(file_name, ".txt");
	if (!file.is_open())
	{
		result = false;
	}
	else
	{
		std::ofstream ofile(file_name);
		if (!ofile.is_open())
			result = false;
		else
		{
			int i = 0;
			STUDENT student;
			while (file.read((char*)&student, sizeof(STUDENT)))
			{
				ofile << student.FIO << '\n';
				ofile << student.education_form << '\n';
				ofile << student.course << '\n';
				ofile << student.group << '\n';
				for (int i = 0; i < 2 * student.course; i++)
					convert_session(student, ofile, i);
			}
			ofile.close();
		}
		file.close();
	}
	return result;
}