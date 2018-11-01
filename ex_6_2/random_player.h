#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_

#include <iostream>
#include "alphonse_playfield_traits.h"

template<typename F, typename PT=alphonse::playfield_traits<F>>
class random_player
{

	int player_id;

public:

	random_player(int player_id) :
		player_id(player_id)
	{
		srand(time(NULL));
	}

	int play(const F& field)
	{
		int column;

		do {
			column = rand() % F::width;
		} while (!PT::column_playable(field, column));

		return column;
	}

};

#endif  // RANDOM_PLAYER_H_
