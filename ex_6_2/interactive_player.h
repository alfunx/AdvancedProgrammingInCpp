#ifndef INTERACTIVE_PLAYER_H_
#define INTERACTIVE_PLAYER_H_

#include <iostream>
#include "alphonse_playfield_traits.h"

template<typename F, typename PT=alphonse::playfield_traits<F>>
class interactive_player
{

	int player_id;

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
		} while (!PT::column_playable(field, column));

		return column;
	}

};

#endif  // INTERACTIVE_PLAYER_H_
