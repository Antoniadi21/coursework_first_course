#pragma once
#include <fstream>
#include <filesystem>
#include "inputs.h"
#include "STUDENT.h"


using std::ios;

using std::ofstream;
using std::ifstream;
using std::fstream;

const int char_size = 256;

bool is_correct_file_name(char* file_name);
bool is_correct_extension(char* file_name, const char* extension);
bool is_file_exist(char* file_name);
void normalize_extension(char* file_name, const char* extension);

void open_file(fstream& file, char* file_name);
void create_file(fstream& file, char* file_name, int mode);
void print_file(fstream& file);

bool convert_binary_to_txt(fstream& file, char* file_name);
void copy_from_bin_to_bin(fstream& file, char* file_name);