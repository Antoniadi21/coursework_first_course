#include "STUDENT.h"


void add_record(fstream& file)
{
	STUDENT new_student;
	read_student_from_console(new_student);
	file.seekp(0, ios::end);
	file.clear();
	file.write((char*)&new_student, sizeof(STUDENT));
	cout << "Запись добавлена" << '\n';
}

void change_record(fstream& file)
{
	file.clear();
	file.seekg(0, ios::end);
	int file_size = file.tellg();
	if (file_size)
	{
		int record_number = number_from_interval(0, file_size / sizeof(STUDENT) - 1);
		STUDENT student;
		cout << "Заново введите запись" << '\n';
		read_student_from_console(student);
		file.clear();
		file.seekp(record_number * sizeof(STUDENT), ios::beg);
		file.write((char*)&student, sizeof(STUDENT));
		cout << "Запись изменена" << '\n';
	}
}

void read_session_from_console(STUDENT& student, int count_session)
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Введите название предмета и оценку ";
		cin >> student.exams[count_session][i].subject_name;
		student.exams[count_session][i].mark = input_int();
	}
}

void read_student_from_console(STUDENT& student)
{
	cout << "Введите ФИО студента" << '\n';
	cin.ignore().getline(student.FIO, 100);
	cout << "Введите курс студента" << '\n';
	student.course = input_int();
	cout << "Введите группу студента" << '\n';
	student.group = input_int();
	cout << "Введите форму обучения студента" << '\n';
	cin >> student.education_form;
	for (int i = 0; i < student.course * 2; i++)
	{
		if (i != 2)
			cout << "Введите результаты " << i + 1 << "-ой " << "сессии" << '\n';
		else
			cout << "Введите результаты " << i + 1 << "-ей " << "сессии" << '\n';
		read_session_from_console(student, i);
	}
}

void print_session_to_console(STUDENT& student, int count_session)
{
	for (int i = 0; i < 5; i++)
		cout << student.exams[count_session][i].subject_name << ' ' << student.exams[count_session][i].mark << '\n';
}

void print_student_to_console(STUDENT& student)
{
	cout << "ФИО: " << student.FIO << '\n';
	cout << "Курс: " << student.course << '\n';
	cout << "Группа: " << student.group << '\n';
	cout << "Форма обучения: " << student.education_form << '\n';
	cout << "Результаты экзаменов:" << '\n';
	for (int i = 0; i < student.course * 2; i++)
	{
		cout << i + 1 << " сессия:\n";
		print_session_to_console(student, i);
	}
}

void delete_record(fstream& file, char* file_name)
{
	file.clear();
	file.seekg(0, ios::end);
	int file_size = file.tellg(), amount_of_structs = file_size / sizeof(STUDENT);
	if (file_size)
	{
		int record_number = number_from_interval(0, amount_of_structs - 1);
		if (record_number != file_size / sizeof(STUDENT) - 1)
		{
			file.clear();
			file.seekg(file_size - sizeof(STUDENT), ios::beg);
			STUDENT last_student;
			file.read((char*)&last_student, sizeof(STUDENT));
			file.seekp(record_number * sizeof(STUDENT), ios::beg);
			file.write((char*)&last_student, sizeof(STUDENT));
		}
		std::filesystem::resize_file(file_name, file_size - sizeof(STUDENT));
		cout << "Запись удалена" << '\n';
	}
}

void convert_session(STUDENT& student, ofstream& file, int count_session)
{
	for (int i = 0; i < 5; i++)
	{
		file << student.exams[count_session][i].subject_name << ' ';
		file << student.exams[count_session][i].mark << ' ' << '\n';
	}
}