#ifndef INTERACTIVE_PLAYER_H_
#define INTERACTIVE_PLAYER_H_

#include <iostream>
#include "alphonse_playfield_traits.h"

template<typename F>
class interactive_player
{

	int player_id;
	typedef alphonse::playfield_traits<F> pt;

public:

	interactive_player(int player_id) :
		player_id(player_id)
	{
		/* void */
	}

	int play(const F& field)
	{
		int column;

		do {
			std::cout << ">>> ";
			std::cin >> column;
			std::cout << std::endl;
		} while (!pt::column_playable(field, column));

		return column;
	}

};

#endif  // INTERACTIVE_PLAYER_H_
