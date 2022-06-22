#ifndef STRUCTS_H_
#define STRUCTS_H_
typedef struct iElement
//Структура элемента очереди(действие)
//Одинаковая для списка и очереди
{
	char operation, mode;
	double *av, *bv, *resv;
	int size;
	double a, b, res;
	char *str;
	/*
	 *operation - переменная отвечающая за символ действия
	 *mode - переменная отвечающая за режим работы с действием, векторный или обычный
	 *av, bv - переменные для хранения значений векторов
	 *resv - переменная для хранения результата действия между векторами
	 *size - переменная отвечающая за размерность векторов
	 *a, b - переменные отвечающие за хранение значений в обычном режиме
	 *res - переменная для хранения результата действия между переменными
	 *str - переменная для хранения строки для работы с ОПН
	 */
	struct iElement *nextElement;
} iElement;
typedef struct list
//Структура Список, имеет указатели на первый и текущий элемент
{
	iElement *head;
	iElement *current;
} list;
typedef struct queue
//Структура Очереди, имеет указатели на первый и текущий элемент
{
	iElement *head;
	//Указатель на на начало очереди (голову)
	iElement *last;
	//Указатель на конец очереди (хвост)
} queue;
typedef struct stackElement
//Структура элемента Стека
{
	double iData;
	//Переменная для хранения чисел из файла и ответа
	struct stackElement *next;
} stackElement;
typedef struct stack
//Структура Стек с указателем на вершину стека (голову)
{
	stackElement *head;
} stack;
#endif
