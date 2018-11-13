#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <vector>
#include "playfield.h"
#include "alphonse_playfield.h"
#include "player.h"
#include "alphonse_playfield_traits.h"

typedef alphonse::playfield_traits<playfield> PT;

class game
{

	alphonse_playfield* field;
	player* player1;
	player* player2;

	char first;
	char current;

public:

	game(alphonse_playfield* f, player* a, player* b)
	{
		field = f;
		player1 = a;
		player2 = b;

		srand(time(NULL));
		first = rand() % PT::max_players + 1;
		current = first;
	}

	void play()
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

		field->print();

		if (draw) {
			std::cout << "It's a draw!" << std::endl;
			std::cout << "Player "
				<< field->stone[first]
				<< " had the first move." << std::endl;
		} else {
			std::cout << "Player "
				<< field->stone[current]
				<< " is the winner!" << std::endl;
			std::cout << "Player "
				<< field->stone[first]
				<< " had the first move." << std::endl;
		}
	}

	void play_round()
	{
		if (current == playfield::player1)
			ensure_play(player1, playfield::player1);
		else if (current == playfield::player2)
			ensure_play(player2, playfield::player2);
	}

	void ensure_play(player* player, int p)
	{
		int column;
		do {
			column = player->play(*field);
		} while (!PT::column_playable(*field, column));
		field->insert(column, p);
	}

};

#endif  // GAME_H_
