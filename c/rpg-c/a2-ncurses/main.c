#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int move_hero( int move_hero_yx, int *y, int *x, int cols, char (*map)[cols] )
{
	int py = *y;
	int px = *x;

	if ( move_hero_yx == KEY_UP && map[py - 1][px] == ' ' ) py--;
	if ( move_hero_yx == KEY_DOWN && map[py + 1][px] == ' ' ) py++;
	if ( move_hero_yx == KEY_LEFT && map[py][px - 1] == ' ' ) px--;
	if ( move_hero_yx == KEY_RIGHT && map[py][px + 1] == ' ' ) px++;

	*y = py;
	*x = px;

	return 0;
}

int dungeon( int rows, int cols, char (*map)[cols],
 	int *hy, int *hx, bool *hero_placed, int *hero_gold,
 	int *gy, int *gx, bool *goblin_placed,
 	bool *room_placed, int *room_y, int *room_x, int *room_size_y, int *room_size_x
 	)
{
	int hhy = *hy;
	int hhx = *hx;
	int ggy = *gy;
	int ggx = *gx;

	if ( !*room_placed )
	{
		*room_placed = 1;
		
		*room_y = rand() & (rows - 3);
		*room_x = rand() & (cols - 3);

		*room_size_y = rand() % 5 + 4;
		*room_size_x = rand() % 10 + 8;
	}

	for ( int yy = 0; yy < rows; yy++ ) 
	{
		for ( int xx = 0; xx < cols; xx++ ) 
		{
			map[yy][xx] = '#';
			mvaddch( yy, xx, '#' );
		}
	}

	for ( int yy = *room_y; yy < *room_y + *room_size_y; yy++ ) 
	{
		for ( int xx = *room_x; xx < *room_x + *room_size_x; xx++ ) 
		{
			map[yy][xx] = ' ';
			mvaddch( yy, xx, ' ' );
		}
	}

	if ( !*hero_placed ) {
		do
		{
			hhy = rand () % rows;
			hhx = rand () % cols;
		}
		while ( map[hhy][hhx] == '#' );

		*hero_placed = 1;
	}

	if ( hhy == ggy && hhx == ggx )
	{
		*goblin_placed = 0;
		*hero_gold += rand() % 10 + 1;
	}

	if ( !*goblin_placed ) {
		do
		{
			ggy = rand () % rows;
			ggx = rand () % cols;
		}
		while ( map[ggy][ggx] == '#' );

		*goblin_placed = 1;
	}


	*hy = hhy;
	*hx = hhx;
	*gy = ggy;
	*gx = ggx;

	return 0;
}

int main( void )
{
	srand( time( NULL ) );

	bool room_placed = 0;
	char hero = '@';
	int hy = 11, hx = 11;
	bool hero_placed = 0; 
	int hero_gold = 0;
	char goblin = 't';
	int gy = 13, gx = 15;
	bool goblin_placed = 0; 
	char EXIT_GAME = 27;
	int move_hero_yx; // input user

	int room_y = 0;
	int room_x = 0;
	int room_size_y = 0;
	int room_size_x = 0;
	

	int cols = 0, rows = 0;

	initscr();
	keypad( stdscr, 1 ); // success allow arrows 
	noecho(); // don't display input
	curs_set( 0 ); // hide cursor
	getmaxyx( stdscr, rows, cols );

	char map[rows][cols];

	do
	{
		dungeon( rows, cols, map, 
			&hy, &hx, &hero_placed, &hero_gold, 
			&gy, &gx, &goblin_placed,
			&room_placed, &room_y, &room_x, &room_size_y, &room_size_x );
		move_hero( move_hero_yx, &hy, &hx, cols, map );

		mvaddch( gy, gx, goblin ); // print goblin
		mvaddch( hy, hx, hero ); // print hero
		mvprintw(rows - 1, 0, "Gold: %d ", hero_gold);
	}
	while ( (move_hero_yx = getch()) != EXIT_GAME );

	endwin();

	return 0;
}