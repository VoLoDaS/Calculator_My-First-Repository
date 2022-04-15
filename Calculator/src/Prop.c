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
		FILE *test;
		test = fopen ("test.txt","r");
		char c, mode;
		//с - символ операции, mode - режим работы программы
		fscanf(test, " %c", &c);
		fscanf(test, " %c", &mode);
		if(mode == 'v')
		//Проверяем символ введенный пользователем для выбора режима
		{
			int size;
			//Эта переменная отвечает за размеры выделяемой памяти для векторов и соответсвенно за размеры векторов
			double *av, *bv, resv;
			//Переменные, которым будем присваивать значения векторов
			fscanf(test, "%i", &size);
			av = malloc(size*sizeof(double));
			bv = malloc(size*sizeof(double));
			//Выделение памяти под координаты векторов
			for(int i = 0; i<size; i++)
			{
				fscanf(test, "%lf", &av[i]);
			}
			//Цикл, отвечающий за ввод коодинат первого вектора
			for(int i = 0; i<size; i++)
			{
				fscanf(test, "%lf", &bv[i]);
			}
			//Цикл, отвечающий за ввод коодинат второго вектора
			fclose(test);
			switch(c)
			//switch для выполнения действия выбранного пользователем
			{
				case '+':
				//Блок отвечающий за сложение векторов
					printf("(");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", av[i]);
					}
					printf(") +");
					printf(" (");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", bv[i]);
					}
					printf(") = ");
					printf("(");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", av[i]+bv[i]);
					}
					printf(")");
					//Цикл, выполняющий действие и выводящий результат в строку через ';'
					free(av);
					free(bv);
					//Освобождение памяти
					break;
				case '-':
				//Блок отвечающий за вычитание векторов
					printf("(");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", av[i]);
					}
					printf(") -");
					printf(" (");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", bv[i]);
					}
					printf(") = ");
					printf("(");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", av[i]-bv[i]);
					}
					printf(")");
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
					printf("(");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", av[i]);
					}
					printf(") *");
					printf(" (");
					for(int i = 0; i<size; i++)
					{
						printf("%lf ", bv[i]);
					}
					printf(") = ");
					printf("%lf\n", resv);
					free(av);
					free(bv);
					//Освобождение памяти
					break;
				default:
					printf("Неизвестная операция\n");
					printf("Я не знаю такой команды, но вы можете обратиться к моему создателю, чтобы он добавил эту операцию 0-0\n");
					printf("Вот его почта: 'vovan.kreshchenko@mail.ru'\n");
					//В случае ввода неизвестной операции предлагается
					//написать разработчику
					break;
			}
			printf("Вычислить что-то еще?0-0\n");
			printf("(Введите 'y' чтобы продолжить, или любой другой символ чтобы закончить)");
			scanf(" %c",&reply);
		}
		else if (mode == 's')
		{
			double a, b, res;
			fscanf(test, "%lf", &a);
			fscanf(test, "%lf", &b);
			fclose(test);
			switch(c)
			//Разбиваем на действия в зависимости от выбора пользователя
			{
				case '+':
				//Этот блок отвечает за выполнение операции сложения
					printf("%lf + %lf = %lf\n",a,b, a+b);
					//Пользователь вводит вторую переменную, после чего выводится ответ
					break;
				case '-':
				//Этот блок отвечает за выполнение операции вычитания
					printf("%lf - %lf = %lf\n",a,b, a-b);
					break;
				case '*':
				//Этот блок отвечает за выполнение операции умножения
					printf("%lf * %lf = %lf\n",a,b, a*b);
					break;
				case '/':
				//Этот блок отвечает за выполнение операции деления
					printf("%lf / %lf = %lf\n",a,b,a/b);
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
						printf("%lf^%.0lf = %lf\n",a,b,res);
						break;
					}
					else if(b == 0)
					{
					//Если степень равна нулю, то ответ равен 1
						res = 1;
						printf("%lf^%.0lf = %lf\n",a,b,res);
						break;
					}
					else
					{
					//Если пользователь введет отрицательную степень
					//поступит запрос на повторное выполнение программы
						printf("Я не умею находить отрицательную степень, попробуйте ввести значение еще раз :(\n");
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
						printf("%.0lf! = %.0lf\n",a,res);
						break;
					}
					else
					{
						if(a==0)
						{
							res = 1;
							printf("%.0lf! = %.0lf\n",a,res);
							//В случае ввода факториала числа '0' переменная res
							//принимает значение константы 1
							break;
						}
						else
						{
							if(a<0)
								{
								printf("Недопустимое значение\n");
								printf("Факториал не бывает отрицательным, попробуйте ввести значение еще раз :(\n");
								//При попытке вычислить факториал отрицательного числа пользователь
								//получает предупреждение и предлагается ввести переменную снова
								break;
								}
						}
						break;
					}
				default:
					printf("Неизвестная операция\n");
					printf("Я не знаю такой команды, но вы можете обратиться к моему создателю, чтобы он ввел эту операцию 0-0\n");
					printf("Вот его почта: 'vovan.kreshchenko@mail.ru'\n");
					//В случае ввода неизвестной операции предлагается
					//написать разработчику
					break;
			}
		printf("Вычислить что-то еще?0-0\n");
		printf("(Введите 'y' чтобы продолжить, или любой другой символ чтобы закончить)");
		scanf(" %c",&reply);
		}
		else
		{
			printf("Неизвестный режим операций, пожалуйста, введите 'v' или 's'\n");
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
