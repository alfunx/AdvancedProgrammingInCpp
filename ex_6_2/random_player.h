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
		return (rand() % F::width);
	}

};

#endif  // RANDOM_PLAYER_H_
