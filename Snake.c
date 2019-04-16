#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20

void Setup();
void Draw();
void Input();
void Logic();


_Bool gameOver;//переменная типа boolean, изначально должна быть false(инверсия game over, т.е. не проиграли)
int x, y, fruitX, fruitY, score;//переменные для нахождения координат змейки и фруктов,счет
int tailX[100], tailY[100];//объявление двух массивов для записи координат хвоста
int nTail;//переменная в которой хранится количество хвостовых деталей
typedef enum 
{
	STOP = 0,	
	LEFT,	
	RIGHT,	
	UP,
	DOWN 
}eDirect;//перечислимый тип для возможных вариантов движения змейки

eDirect dir;

int main()
{
	Setup();
		while (!gameOver)
	{
			Draw();
			Input();
			Logic();
	}
		system("pause");
	return 0;
	
}

void Setup()//функция инициализирует игру
{
	gameOver = 0;
	dir = STOP;//изначально змейка никуда не двигается
	x = WIDTH / 2 - 1;//змейка устанавливается посредине
	y = HEIGHT / 2 - 1;//змейка устанавливается посредине
	fruitX = rand() % WIDTH;
	fruitY = rand() % HEIGHT;
	score = 0;
}

void Draw()//фунция отрисовывает консольную графику, включая поле и все что на нем
{
	system("cls");//очищаем экран
	for (int i = 0; i < WIDTH+1; i++)
		printf("#");
		printf("\n");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if(j == 0 || j == WIDTH-1)
				printf("#");
			if (i == y && j == x)
				printf("O");
			else if (i == fruitY && j == fruitX)
				printf("P");
			else 
			{
				_Bool print = 0;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = 1;
						printf("o");
					}
						
				}
				if(!print)
				printf(" ");
			}
			
		}
		printf("\n");
	}
	
	for (int i = 0; i < WIDTH + 1; i++)
		printf("#");
		printf("\n");
		printf("Score: %d", score);
		Sleep(200);
}

void Input()//функция, которая контролирует все нажатия пользователя
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 75:
			dir = LEFT;
			break;
		case 77:
			dir = RIGHT;
			break;
		case 72:
			dir = UP;
			break;
		case 80:
			dir = DOWN;
			break;
		case 'x':
			gameOver = 1;
			break;

		}
	}

}

void Logic()//функция, которая описывает всю логику игры
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	
	}
	if (x > WIDTH - 2 || x < 0 || y > HEIGHT - 1 || y < 0)
	{
		gameOver = 1;
		system("cls");
		printf("_$$$$___$$$$__$$___$$_$$$$$\n");
		printf("$$_____$$__$$_$$$_$$$_$$\n");
		printf("$$_$$$_$$$$$$_$$_$_$$_$$$$\n");
		printf("$$__$$_$$__$$_$$___$$_$$\n");
		printf("_$$$$__$$__$$_$$___$$_$$$$$\n");
		printf("\n");
		printf("\n");
		printf("_$$$$__$$__$$_$$$$$__$$$$$\n");
		printf("$$__$$_$$__$$_$$_____$$__$$\n");
		printf("$$__$$_$$__$$_$$$$___$$$$$\n");
		printf("$$__$$__$$$$__$$_____$$__$$\n");
		printf("_$$$$____$$___$$$$$__$$__$$\n");
			
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = 1;
			system("cls");
			printf("_$$$$___$$$$__$$___$$_$$$$$\n");
			printf("$$_____$$__$$_$$$_$$$_$$\n");
			printf("$$_$$$_$$$$$$_$$_$_$$_$$$$\n");
			printf("$$__$$_$$__$$_$$___$$_$$\n");
			printf("_$$$$__$$__$$_$$___$$_$$$$$\n");
			printf("\n");
			printf("\n");
			printf("_$$$$__$$__$$_$$$$$__$$$$$\n");
			printf("$$__$$_$$__$$_$$_____$$__$$\n");
			printf("$$__$$_$$__$$_$$$$___$$$$$\n");
			printf("$$__$$__$$$$__$$_____$$__$$\n");
			printf("_$$$$____$$___$$$$$__$$__$$\n");
		}
	}
	


	if (x == fruitX && y == fruitY)
	{
		score += 5;
		fruitX = rand() % WIDTH;
		fruitY = rand() % HEIGHT;
		nTail++;//при поедании приза хвост увеличивается на 1 элемент

	}
}

