#include <iostream>
#include <string>
#include <iostream>
#include <Windows.h> 
#include <vector> 
#include <fstream>

using namespace std;

string get_main_text(string name_file);
vector<string> separate_words(string main_text);
void write_result(string name_file, vector<string> words);

int main()
{
    setlocale(0, ""); // поддержка кириллицы в консоли (вывод)

    string name_file; //название исходного файла

    cout << "Введите номер файла: ";
    cin >> name_file;

    //функция получения текста
    string main_text = get_main_text(name_file);

    //функция разбивает текст на слова 
    vector <string> words = separate_words(main_text);
    
    //запись в файл result
    write_result(name_file, words);
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

vector<string> separate_words(string main_text)
{
    vector<string> words; //массив слов
    string s = "";

    main_text = '"' + main_text + '"'; //добавляем кавычки

    string hi_reg = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит русский
    string lo_reg = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    string separators = " 1234567890,.<>/?\|!@#$%^&*(){}[]:;'~`=qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM\n"; //разделители

    for (int i = 0; i < main_text.length() - 1; i++)
    {
        if (hi_reg.find(main_text[i]) != -1 || lo_reg.find(main_text[i]) != -1) //если символ строки буква из кириллицы

        {
            s += main_text[i]; //собираем слово 
            if ((hi_reg.find(main_text[i]) != -1 || //если символ буквы большого регистра
                lo_reg.find(main_text[i]) != -1) && //если символ буквы маленького регистра
                separators.find(main_text[i + 1]) != -1) //а следующий символ разделитель
            {
                words.push_back(s); //добавляем в массив строку
                s = ""; //обнуляем строку
            }
        }
        else
        {
            if (main_text[i] == '-' && (hi_reg.find(main_text[i + 1]) != -1 || lo_reg.find(main_text[i + 1]) != -1) && s != "")
            {
                s += '-';
            }
        }
    }
    return words;
}

void write_result(string name_file, vector <string> words)
{
    ofstream file_result;
    file_result.open("result_" + name_file + ".txt"); // открываем файл на запись в него

    //вывод слов
    for (int i = 0; i < words.size(); i++)
    {
        file_result << words[i] << endl;
    }
    file_result.close();
}