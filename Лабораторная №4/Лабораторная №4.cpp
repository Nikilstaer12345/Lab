#include <iostream>
#include <time.h> 
#include "Заголовочный.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Приветствую вас в игре." << endl;
	srand((unsigned)time(NULL));
	char a;
	while (1) {
		cout << "Выберите символ: X или 0 " << endl;
		cin >> a;
		if (a == '0' || a == 'X') 
		break;
		
	}
	Game game = initGame(a);

	if (game.isUserTurn)
	{
		while (1)
		{
			userTurn(&game);
			updateDisplay(game);
			if (updateGame(&game))
			{
				break;
			}
			botTurn(&game);
			updateDisplay(game);
			if (updateGame(&game))
			{
				break;
			}
		}
	}
	else
	{
		while (1)
		{
			botTurn(&game);
			updateDisplay(game);
			if (updateGame(&game))
			{
				break;
			}
			userTurn(&game);
			updateDisplay(game);
			if (updateGame(&game))
			{
				break;
			}
		}
	}
	switch (game.status)
	{
	case USER_WIN:
		cout << "Вы победили!";
		break;
	case NOT_WIN:
		cout << "Ничья!";
		break;
	case BOT_WIN:
		cout << "Вы проиграли!";
		break;

	}
	return  0;
}
