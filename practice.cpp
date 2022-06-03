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
void sort(vector <string>& words, int left, int right);
void write_analysis(string name_file, string main_text, int word_count, vector<int> number_words_array, int sort_time);
vector<int> get_array_count_words(vector<string> words);

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
    
    //сортировка слиянием
    int start_time = clock();
    sort(words, 0, words.size() - 1);
    int end_time = clock();
    int sort_time = end_time - start_time; //время сортировки

    //запись в файл result
    write_result(name_file, words);

    //подсчет количества слов на каждую букву
    vector<int> number_words_array = get_array_count_words(words);

    int words_count = words.size(); //количество слов

    //запись в файл analysis 
    write_analysis(name_file, main_text, words_count, number_words_array, sort_time);

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

void sort(vector <string>& words, int left, int right)
{
    //взято отсюда https://evileg.com/ru/post/466/ и после модифицировано

    string lo_reg = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    string hi_reg = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит русский

    if (left >= right)
        return;

    int mid = (left + right) / 2; //находим индекс середины последовательности 

    sort(words, left, mid);
    sort(words, mid + 1, right);

    int len_1 = mid - left + 1;
    int len_2 = right - mid;

    //создается два массива с длинами len_1 и len_2
    vector <string> L(len_1), M(len_2);

    //записываем в массвы элементы из основного массива
    for (int i = 0; i < len_1; i++)
        L[i] = words[left + i];
    for (int j = 0; j < len_2; j++)
        M[j] = words[mid + 1 + j];

    int i = 0, j = 0, k = left;

    int number1, number2;
    // Пока мы не достигнем конца L или M, выбираем большее из элементов L и M и помещаем их в правильное положение в точке A [p..r]
    while (i < len_1 && j < len_2)
    {
        if (lo_reg.find(L[i][0]) == -1) //если первая буква не из нижнего алфавита 
            number1 = hi_reg.find(L[i][0]); //то номер равен номеру буквы в верхнем алфавите
        else
            number1 = lo_reg.find(L[i][0]); //иначе, номер равен номеру буквы в нижнем алфавите

        //аналогично
        if (lo_reg.find(M[j][0]) == -1)
            number2 = hi_reg.find(M[j][0]);
        else
            number2 = lo_reg.find(M[j][0]);

        if (number1 <= number2) //сравниваем номера букв 
        {
            words[k] = L[i];
            i++;
        }
        else
        {
            words[k] = M[j];
            j++;
        }
        k++;
    }

    // Когда у нас кончаются элементы в L или M, возьмите оставшиеся элементы и поместите в A [p..r]
    while (i < len_1)
    {
        words[k] = L[i];
        i++;
        k++;
    }

    while (j < len_2)
    {
        words[k] = M[j];
        j++;
        k++;
    }
}

vector<int> get_array_count_words(vector<string> words)
{
    vector<int> count_words_array(33);
    //Каждый элемент массив - это количество слов на букву

    string hi_reg = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит русский
    string lo_reg = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    for (int i = 0; i < words.size(); i++) //идем по всему массиву строк
    {
        if (hi_reg.find(words[i][0]) != -1) // если нашли в верхнем регистре 
            count_words_array[hi_reg.find(words[i][0])]++; //то увеличиваем элемент с индексом равным номеру большой буквы в верхнем регистре
        else
            count_words_array[lo_reg.find(words[i][0])]++;// увеличиваем элемент с индексом равным номеру маленькой буквы в нижнем регистре
    }
    return count_words_array;
}

void write_analysis(string name_file, string main_text, int word_count, vector<int> number_words_array, int sort_time)
{
    ofstream file_analysis;

    string analysis_str = "analysis_" + name_file + ".txt";
    file_analysis.open(analysis_str); // открываем файл на запись в него

    file_analysis
        << "Исходный текст: " << endl
        << "<<" << main_text << ">>" << endl
        << "Параметры выбранного варианта (12): кириллица, по алфавиту, по возрастанию, игнорировать числа, сортировка слиянием" << endl
        << "Количество слов: " << word_count << endl
        << "Время сортировки: " << static_cast<double>(sort_time) / 1000 << " с" << endl
        << "Статистика (количество слов на каждую букву алфавита): " << endl;

    cout
        << "Исходный текст: " << endl
        << "<<" << main_text << ">>" << endl
        << "Параметры выбранного варианта (12): кириллица, по алфавиту, по возрастанию, игнорировать числа, сортировка слиянием" << endl
        << "Количество слов: " << word_count << endl
        << "Время сортировки: " << static_cast<double>(sort_time) / 1000 << " с" << endl
        << "Статистика (количество слов на каждую букву алфавита): " << endl;

    string lo_reg = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    //вывод количества слов на каждую букву
    for (int i = 0; i < number_words_array.size(); i++)
    {
        file_analysis << lo_reg[i] << ": " << number_words_array[i] << endl;
        cout << lo_reg[i] << ": " << number_words_array[i] << endl;
    }
    file_analysis.close();
}