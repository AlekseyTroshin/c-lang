#include <stdio.h>
#include <string.h>

#include "game.h"
#include "functions.h"

char nickname[10];

int game()
{
	int player_gold = 0;
	char action = 0;

	hello(nickname);

	printf("Hi, %s! What do you want to do today? "
		"Go to the forest to 'h'unt goblins or to drink "
		"ale in the 't'avern or 'q'uit?\n", nickname);

	

	while ( action != 'q' ) 
	{
		action = getchar();
		
		if ( action == '\n' ) 
		{
			action = 0;
		} 
		else 
		{
			CLEAR_BUFFER_CHAR
		}

		
		if ( action == 'h' || action == 'H' )
		{
			player_gold = battle(player_gold);
		}
		else if ( action == 't' || action == 'T' ) 
		{
			player_gold = tavern(player_gold);
		}	
		else if ( action == 'q' )
		{
			printf( "You've decided to run away! Good bye!.\n" );
			break;
		}


		printf( "Next action? 'H'unt, 't'avern or 'q'uit\n" );
	}

	printf( "Your earned %d gold! Good job!\n", player_gold );

	return 0;
}