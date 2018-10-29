#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_

#include <iostream>
#include "alphonse_playfield_traits.h"

template<typename F>
class random_player
{

	int player_id;
	typedef alphonse::playfield_traits<F> pt;

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
		} while (!pt::column_playable(field, column));

		return column;
	}

};

#endif  // RANDOM_PLAYER_H_
