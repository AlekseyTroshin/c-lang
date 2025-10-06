#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"

int tavern(int player_gold)
{
	int ale_mug_cost = 3;

	if (player_gold >= ale_mug_cost)
	{
		player_gold -= ale_mug_cost;
		printf("You've bought mug of ale for %d gols! "
		"Now you have %d gold left\n", ale_mug_cost, player_gold);
	}
	else 
	{
		printf("You don't have enough gold to by an ale :( \n");
	}
	

	return player_gold;
}

int battle(int player_gold)
{
	int goblin_gold = (rand() % 15 + 1);
	int goblin_hp = (rand() % 5 + 3);

	srand(time(NULL));

	for (; goblin_hp >= 0; goblin_hp--) 
	{
		if ( goblin_hp > 0 )
			printf( "You kick goblin. Goblin HP: %d\n", goblin_hp );

		if ( goblin_hp == 0 )
		{
			printf( "You defeat it.\n" );

			player_gold += goblin_gold;

			printf( "You found %d gold. " 
				"You have %d gold total.\n", goblin_gold, player_gold );
			break;
		}
	}

	return player_gold;
}

int hello( char *nickname )
{
	int lenName;

	printf("What is your name?\n");

	fgets(nickname, sizeof(nickname), stdin);

	lenName = strlen(nickname);

	if ( nickname[lenName - 1] == '\n' ) 
	{
		nickname[lenName - 1] = '\0';
	} 
	else 
	{
		CLEAR_BUFFER_CHAR
	}

	return 0;
}