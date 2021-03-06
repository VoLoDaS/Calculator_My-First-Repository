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
#include "queue.h"
#include "stack.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
int reverPolNot(char* string, iElement *out)
//Функция для работы с ОПН через стек, на вход получаем строку и указатель на текущий элемент
{
	stack *stk = calloc(1, sizeof(stack));
	//Указатель на наш стек
	int numChar = 0;
	//Значение предыдущего символа
	for(int i = 0; string[i] != '\0'; i++)
    //Цикл для обработки всей строки
	{
		float aCode = string[i];
		//Переменная для хранения ascii-кода текущего символа
		if((aCode - 48 <10)&(aCode - 48 >=0))
		//48 - код '0' в ascii таблице, проверяем чтобы этот символ был числом
		{
			if(numChar > 0) stk->head->iData = stk->head->iData*10 + (aCode - 48);
			//Если предыдущий символ тоже был числом, продолжаем "собирать" его поразрядно
			else if(numChar < 0)
			{
				double w;
				w = 10;
				for(int i = 1;i<numChar*(-1);i++) w = w*10;
				stk->head->iData = stk->head->iData + (aCode - 48)/w;
				numChar -= 1;
			}
			else
			//Если предыдущий символ не был числом, добавляем новое число в стек
			{
			stackElement *new = calloc(1, sizeof(stackElement));
			new->iData = aCode - 48;
			numChar = 1;
			pushElement(stk, new);
			}
		}
		else
	    //Если текущий символ не число
		{
			stackElement *new = calloc(1, sizeof(stackElement));
			switch (string[i])
			//switch которым проходимся по всем символам строки
				{
				case '.':
				//встретив точку после числа, готовимся дописывать дробную часть в след. итерациях
					if(numChar > 0) numChar = -1;
					break;
				case '+':
					new->iData = popElement(stk)->iData + popElement(stk)->iData;
					pushElement(stk, new);
					//То есть мы добавляем в стек результат сложения первого и второго числа, с остальными аналогично
					break;
				case '-':
					new->iData = (popElement(stk)->iData - popElement(stk)->iData)*(-1);
					pushElement(stk, new);
					break;
				case '*':
					new->iData = popElement(stk)->iData*popElement(stk)->iData;
					pushElement(stk, new);
					break;
				case '/':;
					float second = popElement(stk)->iData;
					new->iData = popElement(stk)->iData/second;
					pushElement(stk, new);
					break;
				default:
					numChar = 0;
				}
		}
	}
	out->res = stk->head->iData;
	//Результат работы записываем в очередь на вывод
	free(stk);
	return 0;
}
int main(int argc,char *argv[])
//Функция калькулятора
{
	char reply;
	//reply - переменная, используемая циклом while после функции
	do
    //Основной цикл, в котором производится работа с файлами, пока пользователь не завершит работу
	{
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);
		printf("Здравствуйте, я Калькулятор (^-^)\n");
		printf("Прежде чем приступить к работе, советую прочитать README с инструкцией по использованию\n");
		char input_name[259], output_name[259], modeNotation;
		//Переменные для записи имени файлов и режима нотации
		printf("Введите режим работы, с какой нотацией придется работать,\n");
		printf("введите 'r', если с обратной польской или любой другой символ, если с префиксной:");
		scanf(" %c", &modeNotation);
		//Выбор пользователем с какой нотацией предстоит работать
		printf("Введите название файла формата '.txt', из которого я буду брать данные:");
		scanf("%s", input_name);
		printf("Введите название файла формата '.txt', в который я запишу результаты:");
		scanf("%s", output_name);
		//Ввод имени файлов для чтения и записи
		FILE *input = fopen(input_name,"r");
		//Открытие файла для чтения
		queue *actions = calloc(1, sizeof(queue));
		//Выделение памяти для указателя на очередь
		char operation, mode;
		//Переменные для работы цикла while ниже, где проверяется наличие этих переменных в строке с действием
		while(feof(input) == 0)
	    //Этот while считывает строчки с данными из файла и добавляем в нашу очередь
		{
			iElement *newAction = calloc(1, sizeof(iElement));
			//Выделяем память для указателя на новый элемент очереди
			if(modeNotation == 'r')
			{
				newAction->str = calloc(255, sizeof(char));
				fgets(newAction->str, 255, input);
				//Выделяем память и помещаем строку в переменную str для работы с ОПН
			}
			else
			{
				fscanf(input, " %c %c", &operation, &mode);
				newAction->operation = operation;
				newAction->mode = mode;
				//Присваиваем значения из нового элемента в переменные
				if(mode == 'v')
				//Проверяем символ введенный пользователем для выбора режима
				{
					fscanf(input, "%i", &newAction->size);
					//Берем значение из файла для переменной size для нового элемента
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
					//Берем значение первой переменной из файла
					if(operation != '!') fscanf(input, "%lf", &newAction->b);
					//Если у нас проходит действие факториала, мы не считываем вторую переменную
				}
			}
			queueAppend(actions, newAction);
			//Добавляем новый элемент в очередь
		}
		fclose(input);
	    //После записи всех данных закрываем файл, чтобы не нагружать память
		queue *data = calloc(1, sizeof(queue));
		while(actions->head != NULL)
		//Этот цикл отвечает за выполнение рассчетов результатов считанных ранее действий и сохранения их в соответствующие элементы очереди
		{
			iElement *thisAction = actions->head;
			//Указатель для выполнения работы с элементами очереди поочередно
			if(modeNotation == 'r')
			{
				reverPolNot(thisAction->str, thisAction);
			}
			//Если пользователь выбрал режим для обработки данных в ОПН, то выполняется функция
			else
			{
				if(actions->head->mode == 'v')
				{
					thisAction->resv = malloc(thisAction->size*sizeof(double));
					//Выделение памяти для переменной с результатами вычислений
					switch(actions->head->operation)
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
				else if (actions->head->mode == 's')
				{
					switch(actions->head->operation)
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
								for(int i = 1;i<thisAction->b;i++) thisAction->res *= thisAction->a;
								break;
							}
							else if(thisAction->b == 0)
							{
							//Если степень равна нулю, то ответ равен 1
								thisAction->res = 1;
								break;
							}
							else break;
						case '!':
						//Этот блок отвечает за выполнение операции факториала
							if(thisAction->a>0)
							{
								thisAction->res = thisAction->a;
								for(int i = 1;i<thisAction->a;i++) thisAction->res *= i;
								break;
							}
							if(thisAction->a==0)
							{
								thisAction->res = 1;
								//В случае ввода факториала числа '0' переменная res
								//принимает значение константы 1
								break;
							}
							else break;
						default:
							break;
					}
				}
			}
			queueAppend(data, thisAction);
			nextElement(actions);
			//Добавляем значения результатов в элементы очереди и переходим к следующим
		}
		free(actions);
		//Освобождаем память от указателя на очередь за не надобностью
		FILE *output = fopen (output_name,"w");
		//Открываем файл для записи реезультатов
		while(data->head != NULL)
		//Этот цикл отвечает за запись результатов в файл в правильной форме
		{
			iElement *thisAction = data->head;
			//Этот указатель нужен для работы с элементами очереди
			if(modeNotation == 'r') fprintf(output, "%g\n", thisAction->res);
			//Вывод ответа в файл
			else if(data->head->mode == 'v')
			{
				switch(data->head->operation)
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
						//Циклы, выводящие результат в правильном виде
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
						//Циклы, выводящие результат в правильном виде
						break;
					case '*':
					//Блок отвечающий за скалярное произведение векторов
						fprintf(output, "(");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->av[i]);
						fprintf(output, ") * (");
						for(int i = 0; i<thisAction->size; i++) fprintf(output, "%lf ", thisAction->bv[i]);
						fprintf(output, ") = ");
						fprintf(output, "%lf\n", thisAction->res);
						//Циклы, выводящие результат в правильном виде
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
				//Освобождение памяти
			}
			else if (data->head->mode == 's')
			{
				switch(data->head->operation)
				//Разбиваем на действия в зависимости от выбора пользователя
				{
					case '+':
					//Этот блок отвечает за вывод операции сложения
						fprintf(output, "%lf + %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						break;
					case '-':
					//Этот блок отвечает за вывод операции вычитания
						fprintf(output, "%lf - %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						break;
					case '*':
					//Этот блок отвечает за вывод операции умножения
						fprintf(output, "%lf * %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						break;
					case '/':
					//Этот блок отвечает за вывод операции деления
						fprintf(output, "%lf / %lf = %lf\n",thisAction->a, thisAction->b, thisAction->res);
						break;
					case '^':
					//Этот блок отвечает за вывод операции возведения в степень
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
			nextElement(data);
			//Переход к следующему элементу
		}
		fclose(output);
		//Закрытие файла для записи
		free(data);
		printf("Результаты записаны в файл\n");
		printf("Вычислить что-то еще?0-0\n");
		printf("(Введите 'y' чтобы продолжить и ввести новые файлы для работы или любой другой символ чтобы закончить)");
		scanf(" %c",&reply);
		//Вывод о завершении работы и запроса на повторное выполнение
	}
	while(reply == 'y');
	//Цикл while отвечает за повтор функции калькулятора
	//В конце каждого блока предлагается ввести 'y', чтобы повторить
	printf("Приходите еще!(^-^)/");
	return 0;
}

