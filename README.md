# **Учебная практика**
## Описание программы
_____
Программа выполняет анализ текста на русском языке(кириллица), игнорируя при этом числа. 
* Первый шаг - получение текста из предварительно созданного текстового файла. Здесь происходит считывание символов из файла в строку.
* Второй шаг - использование функции, разбивающий данный текст на слова.
* Третий шаг - выполнение сортировки слиянием по возрастанию. Далее результат сортировки записывается в файл "result".
* После чего происходит подсчет количества слов на каждую букву, количества слов в целом, времени выполнения сортировки. Полученные данные записываются в файл "analysis".

### Сортировка слиянием 
Основная часть программы посвещена выполнению сортировки *Метдом слияния* или *Merge sort*.       
Алгоритм работает по принципу: разбивает массив на две части, отсортировывает каждую из них, а затем сливает обе части в одну отсортированную. Процесс объединения: подмассивы объединяются в рабочий массив, а затем копируются в исходный массив.
![merge sort](https://linuxhint.com/wp-content/uploads/2021/12/Merge-Sort-Algorithm-Using-Python-1.png, "merge sort")
____
                 Работу выполнила Киселева Софья 5137

