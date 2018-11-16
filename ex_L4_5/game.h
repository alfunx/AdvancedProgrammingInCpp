#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "playfield.h"
#include "alphonse_playfield.h"
#include "player.h"
#include "alphonse_playfield_traits.h"

typedef alphonse::playfield_traits<playfield> PT;

class game
{

	std::shared_ptr<alphonse_playfield> field;
	std::shared_ptr<player> player1;
	std::shared_ptr<player> player2;

	char first;
	char current;

public:

	game(std::shared_ptr<alphonse_playfield> f, std::shared_ptr<player> a, std::shared_ptr<player> b)
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

		// print with last move
		field->print();

		// print final board
		field->finalize();
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

	void ensure_play(std::shared_ptr<player> player, int p)
	{
		int column;
		do {
			column = player->play(*field);
		} while (!PT::column_playable(*field, column));
		field->insert(column, p);
	}

};

#endif  // GAME_H_
