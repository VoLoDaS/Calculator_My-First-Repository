В этом репозитории находится проект калькулятора созданный по заданию в университете.
Это мой первый проект в программировании.
Данный проект выполнен на языке C, используемый компилятор: MinGW-W64 gcc 11.2.0.
Для импорта программы скопируйте репозиторий в среду разработки. 
Калькутор получает данные из файлов.
В папке с проектом находятся файлы Example.txt(RPNexample.txt) и outExample.txt(RPNexampleout.txt) с примером ввода данных 

Инструкция по использованию:

Предварительно, в папке с Calculator надо создать файл формата '.txt' с входными данными.
Входные данные могут быть написаны в префиксной или в обратной польской нотации (для сложных выражений)
Для работы с обратной польской нотацией при выводе программой запроса на выбор режима следует напечать "r", для префиксной можно напечатать любой другой символ
Для префиксной нотации:
  1. Пример для работы с векторами: "+ v 2 1 0 4 3" где
     
     '+' это символ действия
     
     'v' это режим работы с векторами
     
     '2' это размер векторов (только целое)
     
     '1 0' это координаты первого вектора
     
     '4 3' это координаты второго вектора
     
  2. Пример для работы с переменными: "+ s 3 2" где
     
     '+' это символ действия
     
     's' это режим работы с векторами
     
     '3' это первая переменная
     
     '2' это вторая переменная
   
   Примечание:
   
   Значения координат и переменные могут быть вещественными
   
Для обратной польской нотации:
   Для этой нотации поддерживается только режим работы с переменными
   Пример:
  
   '2 5 - 6.2 * 6 + 2 3 / -' - это выражение можно записать как (2 - 5) * 6.2 + 6 - 2 / 3
  
  
   Результат будет записан в файл записи, указанный вами (если он уже существует, то все данные из него будут удалены)
   
   В файле с входными данными могут содержаться несколько строк с действиями, например:
   '+ s 3 2'
   '+ v 2 1 0 4 3' 
   результат будет также записан в файл записи построчно


ВАЖНО: Введение недопустимых входных данных вызовет запрос в консоль на повторное выполнение
НЕСОБЛЮДЕНИЕ ПОРЯДКА ВВОДА НА ВАШ СТРАХ И РИСК

Доступные операции:

Действия с переменными("s"):

Сложение '+'

Вычитание'-'

Умножение '*'

Деление '/'

Возведение в степень '^'

Факториал '!'

Действия с векторами("v"):

Сложение '+'

Вычитание '-'

Скалярное произведение '*'


В обратной польской нотации поддержимаются только действия Сложения, Вычитания, Умножения и Деления

Для начала работы запустите Prop.c по адресу: Calculator/src/Prop.c
