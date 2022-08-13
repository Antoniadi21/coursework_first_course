#include "STUDENT.h"


void add_record(fstream& file)
{
	STUDENT new_student;
	read_student_from_console(new_student);
	file.seekp(0, ios::end);
	file.clear();
	file.write((char*)&new_student, sizeof(STUDENT));
	cout << "������ ���������" << '\n';
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
		cout << "������ ������� ������" << '\n';
		read_student_from_console(student);
		file.clear();
		file.seekp(record_number * sizeof(STUDENT), ios::beg);
		file.write((char*)&student, sizeof(STUDENT));
		cout << "������ ��������" << '\n';
	}
}

void read_session_from_console(STUDENT& student, int count_session)
{
	for (int i = 0; i < 5; i++)
	{
		cout << "������� �������� �������� � ������ ";
		cin >> student.exams[count_session][i].subject_name;
		student.exams[count_session][i].mark = input_int();
	}
}

void read_student_from_console(STUDENT& student)
{
	cout << "������� ��� ��������" << '\n';
	cin.ignore().getline(student.FIO, 100);
	cout << "������� ���� ��������" << '\n';
	student.course = input_int();
	cout << "������� ������ ��������" << '\n';
	student.group = input_int();
	cout << "������� ����� �������� ��������" << '\n';
	cin >> student.education_form;
	for (int i = 0; i < student.course * 2; i++)
	{
		if (i != 2)
			cout << "������� ���������� " << i + 1 << "-�� " << "������" << '\n';
		else
			cout << "������� ���������� " << i + 1 << "-�� " << "������" << '\n';
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
	cout << "���: " << student.FIO << '\n';
	cout << "����: " << student.course << '\n';
	cout << "������: " << student.group << '\n';
	cout << "����� ��������: " << student.education_form << '\n';
	cout << "���������� ���������:" << '\n';
	for (int i = 0; i < student.course * 2; i++)
	{
		cout << i + 1 << " ������:\n";
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
		cout << "������ �������" << '\n';
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