#ifndef INTERACTIVE_PLAYER_H_
#define INTERACTIVE_PLAYER_H_

#include <iostream>
#include "playfield.h"
#include "player.h"
#include "alphonse_playfield_traits.h"

typedef alphonse::playfield_traits<playfield> PT;

class interactive_player : public player
{

	int player_id;

public:

	interactive_player(int player_id) :
		player_id(player_id)
	{
		/* void */
	}

	virtual ~interactive_player()
	{
		/* void */
	}

	int play(const playfield& field)
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
