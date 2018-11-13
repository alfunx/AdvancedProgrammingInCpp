#include <iostream>
#include "random_player.h"

random_player::random_player(int player_id) :
	player_id(player_id)
{
	srand(time(NULL));
}

random_player::~random_player()
{
	/* void */
}

int random_player::play(const playfield& field)
{
	int column;

	do {
		column = rand() % playfield::width;
	} while (!PT::column_playable(field, column));

	return column;
}
