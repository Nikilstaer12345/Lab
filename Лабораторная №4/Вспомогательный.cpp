#include <iostream>

using namespace std;

/*Состояния игры*/
enum Status{
	PLAY,            // Игра продолжается
	USER_WIN,       // Игрок победил
	BOT_WIN,         // Бот победил
	NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
};
struct Game{
	char bord[3][3];  //Игровое поле
	bool isUserTurn;   // Чей ход. Если пользователя, то isUserTurn=true;
	char userChar;     // Символ, которым играет пользователь
	char botChar;      // Символ, которым играет бот
	Status status;
};

Game initGame(char userChar)
/**
* Выполняет следующие действия:
*  1. Очищает экран
*  2. Отображает содержимое игрового поля:
*         0   1   2
*       -------------
*     0 | O | O | X |
*       -------------
*     1 |   |   |   |
*       -------------
*     2 |   |   | X |
*       -------------
*/
{
	Game game;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			game.bord[i][j] = ' ';
		}
	}
	if (rand() % 2) {
		game.isUserTurn = true; 
	}
	game.userChar = userChar; 
	switch (game.userChar) // символ для бота
	{ 
	case '0':
		game.botChar = 'X';
		break;
	case 'X':
		game.botChar = '0';
		break;
	}
	return game;
}

void updateDisplay(const Game game)
{
	system("cls");
	cout << "0   1   2" << endl;
	cout << "----------" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << game.bord[i][j] << " | ";
		}
		cout << i << endl << "----------" << endl;
	}
}

void botTurn(Game* game)
{
	bool True = true, False = false;
	int str;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (game->bord[i][j] != game->botChar && game->bord[i][j] != game->userChar) {
				True = false;
			}
		}
	}
	if (True) {
		game->bord[1][1] = game->botChar; game->isUserTurn = true;
	}
	else {
		for (int i = 0; i < 3; ++i) {
			str = 0;
			if (game->bord[i][0] == game->userChar) {
				str++;
			}
			if (game->bord[i][1] == game->userChar) {
				str++;
			}
			if (game->bord[i][2] == game->userChar) {
				str++;
			}
			if (str > 1) {
				for (int j = 0; j < 3; ++j) {
					if (game->bord[i][j] != game->botChar && game->bord[i][j] != game->userChar) {
						game->bord[i][j] = game->botChar; game->isUserTurn = true;
						False = true; 
						return;
					}
				}
				break;
			}
		}
		if (!False) {
			for (int j = 0; j < 3; ++j) { 
				str = 0;
				if (game->bord[0][j] == game->userChar) {
					str++;
				}
				if (game->bord[1][j] == game->userChar) {
					str++;
				}
				if (game->bord[2][j] == game->userChar) {
					str++;
				}
				if (str > 1) {
					for (int i = 0; i < 3; ++i) {
						if (game->bord[i][j] != game->botChar && game->bord[i][j] != game->userChar) {
							game->bord[i][j] = game->botChar;
							game->isUserTurn = true; 
							False = true;
							return;
						}
					}
					break;
				}
			}
		}
		if (!False) {
			str = 0;
			if (game->bord[0][2] == game->userChar) {
				str++;
			}
			else if (game->bord[1][1] == game->userChar) {
				str++;
			}
			else if (game->bord[2][0] == game->userChar) {
				str++;
			}
			else if (str > 1) {
				if ((game->bord[0][2] != game->botChar && game->bord[0][2] != game->userChar) && !False) {
					game->bord[0][2] = game->botChar;
					game->isUserTurn = true;
					False = true;
					return;
				}
				else if ((game->bord[1][1] != game->botChar && game->bord[1][1] != game->userChar) && !False) {
					game->bord[1][1] = game->botChar;
					game->isUserTurn = true;
					False = true; 
					return;
				}
				else if ((game->bord[2][0] != game->botChar && game->bord[2][0] != game->userChar) && !False) {
					game->bord[2][0] = game->botChar;
					game->isUserTurn = true; 
					False = true; 
					return;
				}
			}
		}
		if (!False) {
			str = 0;
			for (int i = 0; i < 3; ++i) {
				if (game->bord[i][i] == game->userChar) {
					str++;
				}
			}
			if (str > 1) {
				for (int i = 0; i < 3; ++i) {
					if (game->bord[i][i] != game->botChar && game->bord[i][i] != game->userChar) {
						game->bord[i][i] = game->botChar;
						game->isUserTurn = true;
						False = true;
						return;
					}
				}
			}
		}
		if (!False) {
			while (true) {
				int i = rand() % 3;
				int j = rand() % 3;
				if (game->bord[i][j] != game->botChar && game->bord[i][j] != game->userChar) {
					game->bord[i][j] = game->botChar;
					game->isUserTurn = true; 
					False = true;
					break;
				}
			}
		}
	}
}
void userTurn(Game* game)
{
	int i, j;

	                                                                                             
		while (1)
		{
			cout << "Введите координаты клетки :" << endl;
			cin >> i >> j;
			if (i < 0|| j < 0 || j > 3 || i > 3|| &game->bord[i][j] == " ")
			{
				cout << "Данные координаты не соответствуют требуемым. Введите повторно: ";
			}
			else
			{
				game->bord[j][i] = game->userChar;
				break;
			}
		}
}
bool updateGame(Game* game)
{
	if (game->bord[0][2] == game->userChar && game->bord[1][1] == game->userChar && game->bord[2][0] == game->userChar) {
		game->status = USER_WIN;
		return true;
	}
	if (game->bord[0][0] == game->userChar && game->bord[1][1] == game->userChar && game->bord[2][2] == game->userChar) {
		game->status = USER_WIN;
		return true;
	}
	if (game->bord[0][2] == game->botChar && game->bord[1][1] == game->botChar && game->bord[2][0] == game->botChar) {
		game->status = BOT_WIN;
		return true;
	}
	if (game->bord[0][0] == game->botChar && game->bord[1][1] == game->botChar && game->bord[2][2] == game->botChar) {
		game->status = BOT_WIN;
		return true;
	}
	for (int i = 0; i < 3; i++)
	{
		int len1 = 0;
		int len2 = 0;
		for (int j = 0; j < 3; j++) {
			if (game->bord[i][j] == game->userChar)
			{
				len1++;
			}
			else if (game->bord[i][j] == game->botChar)
			{
				len2++;
			}
		}
		if ((len1 == 3) || (len2 == 3)) {
			game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
			return true;
		}
	}


		for (int i = 0; i < 3; i++)
		{
			int len1 = 0;
			int len2 = 0;
			for (int j = 0; j < 3; j++)
			{
				if (game->bord[j][i] == game->userChar)
				{
					len1++;
				}
				else if (game->bord[j][i] == game->botChar)
				{
					len2++;
				}
			}
			if ((len1 == 3) || (len2 == 3))
			{
				game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
				return true;
			}
		}

	{
		int len1 = 0;
		int len2 = 0;
		for (int i = 0; i < 3; i++)
		{
			if (game->bord[i][i] == game->userChar)
			{
				len1++;
			}
			else if (game->bord[i][i] == game->botChar)
			{
				len2++;
			}
		}
		if ((len1 == 3) || (len2 == 3))
		{
			game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
			return true;
		}
	}

	{
		int len1 = 0;
		int len2 = 0;
		for (int i = 0; i < 3; i++) {
			if (game->bord[i][3 - i] == game->userChar)
			{
				len1++;
			}
			else if (game->bord[i][3 - i] == game->botChar)
			{
				len2++;
			}
		}
		if ((len1 == 3) || (len2 == 3))
		{
			game->status = (len1 == 3 ? USER_WIN : BOT_WIN);
			return true;
		}
	}
	int len = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game->bord[i][j] != ' ')
			{
				len++;
			}
		}
	}
	if (len == 9)
	{
		game->status = NOT_WIN;
		return true;
	}
	game->status = PLAY;
	return false;
}
