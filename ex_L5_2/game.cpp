#include <iostream>
#include <string>
#include <vector>

#include "game.h"

game::game(std::shared_ptr<alphonse_playfield> f, std::shared_ptr<player> a, std::shared_ptr<player> b) :
	current(playfield::player1)
{
	field = f;
	player1 = a;
	player2 = b;
}

void game::play()
{
	bool draw = true;

	while (PT::grid_playable(*field)) {
		field->print();

		std::cout << "It's player "
			<< field->stone[current]
			<< "'s turn." << std::endl;

		play_round();

		if (PT::has_won(*field, current)) {
			draw = false;
			break;
		}

		current = PT::next_player(current);
	}

	// print with last move
	field->print();

	// print final board
	field->finalize();
	field->print();

	if (draw) {
		std::cout << "It's a draw!" << std::endl;
	} else {
		std::cout << "Player "
			<< field->stone[current]
			<< " is the winner!" << std::endl;
	}
}

void game::play_round()
{
	if (current == playfield::player1)
		ensure_play(player1, playfield::player1);
	else if (current == playfield::player2)
		ensure_play(player2, playfield::player2);
}

void game::ensure_play(std::shared_ptr<player> player, int p)
{
	int column;
	do {
		column = player->play(*field);
	} while (!PT::column_playable(*field, column));
	field->insert(column, p);
}
