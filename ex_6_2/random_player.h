#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_

#include <iostream>

template<typename F>
class random_player
{

public:

	random_player()
	{
		srand(time(NULL));
	}

	int play(const F& field)
	{
		int column;

		do {
			column = rand() % F::width;
		} while (field.stoneat(column, 0) != F::none);

		return column;
	}

};

#endif  // RANDOM_PLAYER_H_
