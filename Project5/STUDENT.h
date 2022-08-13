#pragma once

#include "EXAM.h"
#include "files.h"

struct STUDENT
{
	char FIO[40];
	int course, group;
	char education_form;
	EXAM exams[10][5];
};

void add_record(fstream& file);
void delete_record(fstream& file, char* file_name);
void change_record(fstream& file);

void read_student_from_console(STUDENT& student);
void print_student_to_console(STUDENT& student);

void convert_session(STUDENT& student, ofstream& file, int count_session);