#include <iostream>
#include <string>
#include <iostream>
#include <Windows.h> 
#include <vector> 
#include <fstream>

using namespace std;

string get_main_text(string name_file);

int main()
{
    setlocale(0, ""); // поддержка кириллицы в консоли (вывод)

    string name_file; //название исходного файла

    cout << "Введите номер файла: ";
    cin >> name_file;

    //функция получения текста
    string main_text = get_main_text(name_file);

    return 0;
}

string get_main_text(string name_file)
{
    string main_text = ""; //исходная строка
    ifstream file_original; //создаем переменную файла
    file_original.open("original_" + name_file + ".txt"); // открываем файл

    if (file_original.is_open()) //если файл открылся 
    {
        char ch;
        while (file_original.get(ch)) //пока можем считать символ из файла
        {
            main_text += ch;; //прибавляем символ к строке 
        }
        file_original.close(); // Закрытие файла
    }
    else
    {
        cout << "Файл original не открылся";
        exit(0);
    }
    return main_text;
}
