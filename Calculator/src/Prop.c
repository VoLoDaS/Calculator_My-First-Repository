/*
 ============================================================================
 Name/Имя              : Calculator/Калькулятор
 Author/Автор          : Vladimir_Kreshchenko/Владимир_Крещенко
 Copyright/Лицензия    : Your copyright notice/Все права защищены
 Description/Описание  : The program performs 6 mathematical actions
                         with two variables: addition, subtraction,
                         multiplication, division, raising a number to an integer
                         positive degree, factorial of the number, and also 3
                         actions with vectors: addition and subtraction of vectors,
                         scalar product of vectors
                         Interface language: Russian/
                         Программа выполняет 6 математических действий
                         с двумя переменными : сложение, вычитание,
                         умножение, деление,возведение числа в целую
                         положительную степень, факториал числа, а также 3
                         действия с векторами: сложение и вычитание вектором,
                         скалярное произведение векторов
                         Язык интерфейса: Русский
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct listElement
//Структура элемента списка(действие)
{
	char operation, mode;
	double *av, *bv, *resv;
	int size;
	double a, b, res;
	struct listElement *nextElement;
} iElement;
typedef struct list
{
	iElement *head;
	iElement *current;
} list;
iElement *nextElement(list *inList)
{
	iElement *next = inList->current->nextElement;
	inList->current =  next;
	return next;
}
int listAppend(list *inList, iElement *newElement)
{
	if(inList->head == NULL)
	{
		inList->head = newElement;
		inList->current = newElement;
		return 0;
	}
	inList->current->nextElement = newElement;
	inList->current = newElement;
	return 0;
}
int goHeadElement(list *inList)
{
	inList->current =  inList->head;
	return 0;
}
int deleteElement(list *inList)
{
	iElement *delete = inList->current;
	if(delete == inList->head)
	{
		inList->head = delete->nextElement;
		nextElement(inList);
	}
	else
	{
		goHeadElement(inList);
		while(inList->current->nextElement != delete) nextElement(inList);
		inList->current->nextElement = delete->nextElement;
		if(delete->nextElement != NULL) inList->current = delete->nextElement;
	}
	free(delete);
	return 0;
}
int main(int argc,char *argv[])
//Функция калькулятора
{
	char reply;
	//reply - глобальная переменная, используемая циклом while после функции
	do
	{
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);
		printf("Здравствуйте, я Калькулятор (^-^)\n");
		printf("Прежде чем приступить к работе, советую прочитать README с инструкцией по использованию\n");
		char input_name[259], output_name[259];
		//Переменные для записи имени файлов
		printf("Введите название файла формата '.txt', из которого я буду брать данные:");
		scanf("%s", input_name);
		printf("Введите название файла формата '.txt', в который я запишу результаты:");
		scanf("%s", output_name);
		//Ввод имени файлов для чтения и записи
		FILE *input = fopen (input_name,"r");
		//Открытие файлов для чтение и записи
		list *actions = calloc(1, sizeof(list));
		char operation, mode;
		while(fscanf(input, " %c %c", &operation, &mode) != EOF)
	    //Этот while считывает строчки с данными(то есть несколько действий) до тех пор пока они не закончатся
		{
			iElement *newAction = calloc(1, sizeof(iElement));
			newAction->operation = operation;
			newAction->mode = mode;
			if(mode == 'v')
			//Проверяем символ введенный пользователем для выбора режима
			{
				//Эта переменная отвечает за размеры выделяемой памяти для векторов и соответсвенно за размеры векторов
				//Переменные, которым будем присваивать значения векторов
				fscanf(input, "%i", &newAction->size);
				newAction->av = malloc(newAction->size*sizeof(double));
				newAction->bv = malloc(newAction->size*sizeof(double));
				//Выделение памяти под координаты векторов
				for(int i = 0; i<newAction->size; i++) fscanf(input, "%lf", &newAction->av[i]);
				for(int i = 0; i<newAction->size; i++) fscanf(input, "%lf", &newAction->bv[i]);
				//Циклы, отвечающие за ввод коодинат векторов
			}
			else if (mode == 's')
			{
				fscanf(input, "%lf", &newAction->a);
				if(operation != '!') fscanf(input, "%lf", &newAction->b);
			}
			listAppend(actions, newAction);
		}
		fclose(input);
		goHeadElement(actions);
		while(actions->current != NULL)
		{
			iElement *thisAction = actions->current;
			if(actions->current->mode == 'v')
			{
				thisAction->resv = malloc(thisAction->size*sizeof(double));
				switch(actions->current->operation)
				//switch для выполнения действия выбранного пользователем
				{
					case '+':
					//Блок отвечающий за сложение векторов
						for(int i = 0; i<thisAction->size; i++) thisAction->resv[i] = thisAction->av[i]+thisAction->bv[i];
						//Циклы, выполняющие действие и выводящие результат в правильном виде
						break;
					case '-':
					//Блок отвечающий за вычитание векторов
						for(int i = 0; i<thisAction->size; i++) thisAction->resv[i] = thisAction->av[i]-thisAction->bv[i];
						//Циклы, выполняющие действие и выводящие результат в правильном виде
						break;
					case '*':
					//Блок отвечающий за скалярное произведение векторов
						for(int i = 0; i<thisAction->size; i++) thisAction->res += thisAction->av[i]*thisAction->bv[i];
						//Циклы, выполняющие действие и выводящие результат в правильном виде
						break;
					default:
						break;
				}

			}
			else if (actions->current->mode == 's')
			{
				switch(actions->current->operation)
				//Разбиваем на действия в зависимости от выбора пользователя
				{
					case '+':
					//Этот блок отвечает за выполнение операции сложения
						thisAction->res = thisAction->a+thisAction->b;
						//Пользователь вводит вторую переменную, после чего выводится ответ
						break;
					case '-':
					//Этот блок отвечает за выполнение операции вычитания
						thisAction->res = thisAction->a-thisAction->b;
						break;
					case '*':
					//Этот блок отвечает за выполнение операции умножения
						thisAction->res = thisAction->a*thisAction->b;
						break;
					case '/':
					//Этот блок отвечает за выполнение операции деления
						thisAction->res = thisAction->a/thisAction->b;
						break;
					case '^':
					//Этот блок отвечает за выполнение операции возведения в степень
					//может рассчитать только положительную целую степень
						if(thisAction->b>0)
						{
							thisAction->res = thisAction->a;
							for(int i = 1;i<thisAction->b;i++) thisAction->res = thisAction->res*thisAction->a;
							//Этот цикл рассчитывает результат
							break;
						}
						else if(thisAction->b == 0)
						{
						//Если степень равна нулю, то ответ равен 1
							thisAction->res = 1;
							break;
						}
						else
						{
							break;
						}
					case '!':
					//Этот блок отвечает за выполнение операции факториала
						if(thisAction->a>0)
						{
							thisAction->res = thisAction->a;
							for(int i = 1;i<thisAction->a;i++) thisAction->res = thisAction->res*i;
							break;
						}
						else
						{
							if(thisAction->a==0)
							{
								thisAction->res = 1;
								//В случае ввода факториала числа '0' переменная res
								//принимает значение константы 1
								break;
							}
							else
							{
								if(thisAction->a<0) break;
							}
							break;
						}
					default:
						break;
				}
			}
			nextElement(actions);
		}
		goHeadElement(actions);
		FILE *output = fopen (output_name,"w");
		while(actions->current != NULL)
		{
			iElement *thisAction = actions->current;
			if(actions->current->mode == 'v')
			{
				switch(actions->current->operation)
				//switch для выполнения действия выбранного пользователем
				{
					case '+':
					//Блок отвечающий за сложение векторов
						fprintf(output, "(");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->av[i]);
						fprintf(output, ") + (");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->bv[i]);
						fprintf(output, ") = (");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->resv[i]);
						fprintf(output, ")\n");
						//Циклы, выполняющие действие и выводящие результат в правильном виде
						//Освобождение памяти
						break;
					case '-':
					//Блок отвечающий за вычитание векторов
						fprintf(output, "(");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->av[i]);
						fprintf(output, ") - (");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->bv[i]);
						fprintf(output, ") = (");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->resv[i]);
						fprintf(output, ")\n");
						//Циклы, выполняющие действие и выводящие результат в правильном виде
						//Освобождение памяти
						break;
					case '*':
					//Блок отвечающий за скалярное произведение векторов
						fprintf(output, "(");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->av[i]);
						fprintf(output, ") * (");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->bv[i]);
						fprintf(output, ") = ");
						fprintf(output, "%lf\n", thisAction->res);
						//Циклы, выполняющие действие и выводящие результат в правильном виде
						//Освобождение памяти
						break;
					default:
						fprintf(output, "Неизвестная операция\n");
						fprintf(output, "Я не знаю такой команды, но вы можете обратиться к моему создателю, чтобы он ввел эту операцию 0-0\n");
						fprintf(output, "Вот его почта: 'vovan.kreshchenko@mail.ru'\n");
						break;
				}
				free(thisAction->av);
				free(thisAction->bv);
				free(thisAction->resv);
			}
			else if (actions->current->mode == 's')
			{
				switch(actions->current->operation)
				//Разбиваем на действия в зависимости от выбора пользователя
				{
					case '+':
					//Этот блок отвечает за выполнение операции сложения
						fprintf(output, "%lf + %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						//Пользователь вводит вторую переменную, после чего выводится ответ
						break;
					case '-':
					//Этот блок отвечает за выполнение операции вычитания
						fprintf(output, "%lf - %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						break;
					case '*':
					//Этот блок отвечает за выполнение операции умножения
						fprintf(output, "%lf * %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						break;
					case '/':
					//Этот блок отвечает за выполнение операции деления
						fprintf(output, "%lf / %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						break;
					case '^':
					//Этот блок отвечает за выполнение операции возведения в степень
					//может рассчитать только положительную целую степень
						if(thisAction->b>=0)
						{
							fprintf(output, "%lf^%.0lf = %lf\n",thisAction->a,thisAction->b,thisAction->res);
							break;
						}
						else
						{
						//Если пользователь введет отрицательную степень
						//поступит запрос на повторное выполнение программы
							fprintf(output, "Я не умею находить отрицательную степень, попробуйте ввести значение еще раз :(\n");
							break;
						}
					case '!':
					//Этот блок отвечает за выполнение операции факториала
						if(thisAction->a>=0)
						{
							fprintf(output, "%.0lf! = %.0lf\n",thisAction->a,thisAction->res);
							break;
						}
						else
						{
							fprintf(output, "Недопустимое значение\n");
							fprintf(output, "Факториал не бывает отрицательным, попробуйте ввести значение еще раз :(\n");
							//При попытке вычислить факториал отрицательного числа пользователь
							//получает предупреждение и предлагается ввести переменную снова
							break;
						}
					default:
						fprintf(output, "Неизвестная операция\n");
						fprintf(output, "Я не знаю такой команды, но вы можете обратиться к моему создателю, чтобы он ввел эту операцию 0-0\n");
						fprintf(output, "Вот его почта: 'vovan.kreshchenko@mail.ru'\n");
						//В случае ввода неизвестной операции предлагается
						//написать разработчику
						break;
				}
			}
			else fprintf(output, "Неизвестный режим операций, пожалуйста, введите 'v' или 's'\n");
			//Вывод, если символ типа, с какими данными предстоит работать не соответствует
			fprintf(output, "\n");
			deleteElement(actions);
		}
		free(actions);
		fclose(output);
		printf("Результаты записаны в файл\n");
		printf("Вычислить что-то еще?0-0\n");
		printf("(Введите 'y' чтобы продолжить и ввести новые файлы для работы или любой другой символ чтобы закончить)");
		scanf(" %c",&reply);
		//Вывод о завершении работы и вывод запроса на повторное выполнение
	}
	while(reply == 'y');
	//Цикл while отвечает за повтор функции калькулятора
	//В конце каждого блока предлагается ввести 'y', чтобы повторить
	printf("Приходите еще!(^-^)/");
	return 0;
}

