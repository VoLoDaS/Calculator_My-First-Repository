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
char reply;
//reply - глобальная переменная, используемая циклом while после функции
int main(int argc,char *argv[])
//Функция калькулятора
{
	do
	{
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);
		printf("Здравствуйте, я Калькулятор (^-^)\n");
		printf("Прежде чем приступить к работе, советую прочитать README с инструкцией по использованию\n");
		FILE *input, *output;
		char input_name[259], output_name[259];
		//Переменные для записи имени файлов
		printf("Введите название файла формата '.txt', из которого я буду брать данные:");
		scanf("%s", input_name);
		printf("Введите название файла формата '.txt', в который я запишу результаты:");
		scanf("%s", output_name);
		//Ввод имени файлов для чтения и записи
		input = fopen (input_name,"r");
		output = fopen (output_name,"w");
		//Открытие файлов для чтение и записи
		char c, mode;
		//с - символ операции, mode - режим работы программы
		fscanf(input, " %c", &c);
		fscanf(input, " %c", &mode);
		if(mode == 'v')
		//Проверяем символ введенный пользователем для выбора режима
		{
			int size;
			//Эта переменная отвечает за размеры выделяемой памяти для векторов и соответсвенно за размеры векторов
			double *av, *bv, resv;
			//Переменные, которым будем присваивать значения векторов
			fscanf(input, "%i", &size);
			av = malloc(size*sizeof(double));
			bv = malloc(size*sizeof(double));
			//Выделение памяти под координаты векторов
			for(int i = 0; i<size; i++)
			{
				fscanf(input, "%lf", &av[i]);
			}
			//Цикл, отвечающий за ввод коодинат первого вектора
			for(int i = 0; i<size; i++)
			{
				fscanf(input, "%lf", &bv[i]);
			}
			//Цикл, отвечающий за ввод коодинат второго вектора
			fclose(input);
			switch(c)
			//switch для выполнения действия выбранного пользователем
			{
				case '+':
				//Блок отвечающий за сложение векторов
					fprintf(output, "(");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", av[i]);
					}
					fprintf(output, ") +");
					fprintf(output, " (");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", bv[i]);
					}
					fprintf(output, ") = ");
					fprintf(output, "(");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", av[i]+bv[i]);
					}
					fprintf(output, ")");
					//Цикл, выполняющий действие и выводящий результат в строку через ';'
					free(av);
					free(bv);
					//Освобождение памяти
					break;
				case '-':
				//Блок отвечающий за вычитание векторов
					fprintf(output, "(");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", av[i]);
					}
					fprintf(output, ") -");
					fprintf(output, " (");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", bv[i]);
					}
					fprintf(output, ") = ");
					fprintf(output, "(");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", av[i]-bv[i]);
					}
					fprintf(output, ")");
					//Цикл, выполняющий действие и выводящий результат в строку через ';'
					free(av);
					free(bv);
					//Освобождение памяти
					break;
				case '*':
				//Блок отвечающий за скалярное произведение векторов
					for(int i = 0; i<size; i++)
					{
						resv += av[i]*bv[i];
					}
					//Цикл выполняющий действие
					fprintf(output, "(");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", av[i]);
					}
					fprintf(output, ") *");
					fprintf(output, " (");
					for(int i = 0; i<size; i++)
					{
						fprintf(output, "%lf ", bv[i]);
					}
					fprintf(output, ") = ");
					fprintf(output, "%lf\n", resv);
					free(av);
					free(bv);
					//Освобождение памяти
					break;
				default:
					fprintf(output, "Неизвестная операция\n");
					fprintf(output, "Я не знаю такой команды, но вы можете обратиться к моему создателю, чтобы он добавил эту операцию 0-0\n");
					fprintf(output, "Вот его почта: 'vovan.kreshchenko@mail.ru'\n");
					//В случае ввода неизвестной операции предлагается
					//написать разработчику
					break;
			}
			fclose(output);
			printf("Результаты записаны в файл\n");
			printf("Вычислить что-то еще?0-0\n");
			printf("(Введите 'y' чтобы продолжить, или любой другой символ чтобы закончить)");
			scanf(" %c",&reply);
		}
		else if (mode == 's')
		{
			double a, b, res;
			fscanf(input, "%lf", &a);
			fscanf(input, "%lf", &b);
			fclose(input);
			switch(c)
			//Разбиваем на действия в зависимости от выбора пользователя
			{
				case '+':
				//Этот блок отвечает за выполнение операции сложения
					fprintf(output, "%lf + %lf = %lf\n",a,b, a+b);
					//Пользователь вводит вторую переменную, после чего выводится ответ
					break;
				case '-':
				//Этот блок отвечает за выполнение операции вычитания
					fprintf(output, "%lf - %lf = %lf\n",a,b, a-b);
					break;
				case '*':
				//Этот блок отвечает за выполнение операции умножения
					fprintf(output, "%lf * %lf = %lf\n",a,b, a*b);
					break;
				case '/':
				//Этот блок отвечает за выполнение операции деления
					fprintf(output, "%lf / %lf = %lf\n",a,b,a/b);
					break;
				case '^':
				//Этот блок отвечает за выполнение операции возведения в степень
				//может рассчитать только положительную целую степень
					if(b>0)
					{
						res = a;
						for(int i = 1;i<b;i++)
						//Этот цикл рассчитывает результат
						{
							res = res*a;
						}
						fprintf(output, "%lf^%.0lf = %lf\n",a,b,res);
						break;
					}
					else if(b == 0)
					{
					//Если степень равна нулю, то ответ равен 1
						res = 1;
						fprintf(output, "%lf^%.0lf = %lf\n",a,b,res);
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
					if(a>0)
					{
						res = a;
						for(int i = 1;i<a;i++)
						{
							res = res*i;
						}
						fprintf(output, "%.0lf! = %.0lf\n",a,res);
						break;
					}
					else
					{
						if(a==0)
						{
							res = 1;
							fprintf(output, "%.0lf! = %.0lf\n",a,res);
							//В случае ввода факториала числа '0' переменная res
							//принимает значение константы 1
							break;
						}
						else
						{
							if(a<0)
								{
								fprintf(output, "Недопустимое значение\n");
								fprintf(output, "Факториал не бывает отрицательным, попробуйте ввести значение еще раз :(\n");
								//При попытке вычислить факториал отрицательного числа пользователь
								//получает предупреждение и предлагается ввести переменную снова
								break;
								}
						}
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
		fclose(output);
		printf("Результаты записаны в файл\n");
		printf("Вычислить что-то еще?0-0\n");
		printf("(Введите 'y' чтобы продолжить, или любой другой символ чтобы закончить)");
		scanf(" %c",&reply);
		}
		else
		{
			fclose(input);
			fprintf(output, "Неизвестный режим операций, пожалуйста, введите 'v' или 's'\n");
			fclose(output);
			printf("(Введите 'y' чтобы продолжить, или любой другой символ чтобы закончить)");
			scanf(" %c",&reply);
		}
	}
	while(reply == 'y');
	//Цикл while отвечает за повтор функции калькулятора
	//В конце каждого блока предлагается ввести 'y', чтобы повторить
	printf("Приходите еще!(^-^)/");
	return 0;
}
