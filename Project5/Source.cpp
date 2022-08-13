#include <Windows.h>
#include <string>

#include "STUDENT.h"
#include "inputs.h"
#include "menus.h"
#include "files.h"

const int char_size = 255;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char file_name[char_size];
	fstream file;
	bool is_exit = false;
	while (!is_exit)
	{
		is_exit = file.is_open() ? second_menu(file, file_name) : first_menu(file, file_name);
		if (!is_exit)
		{
			cout << "ֽאזלטעו <ENTER>" << '\n';
			cin.ignore().get();
		}
	}
	file.close();
	return 0;
}