#include <iostream>

#include "interactive_player.h"

interactive_player::interactive_player(int player_id) :
	player_id(player_id)
{
	/* void */
}

interactive_player::~interactive_player()
{
	/* void */
}

int interactive_player::play(const playfield& field)
{
	int column;

	do {
		std::cout << ">>> ";
		std::cin >> column;
		std::cout << std::endl;
	} while (!PT::column_playable(field, column));

	return column;
}

std::shared_ptr<player> interactive_player::make(int id)
{
	return std::make_shared<interactive_player>(id);
}

static register_player<interactive_player> p("interactive");
