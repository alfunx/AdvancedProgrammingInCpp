#ifndef GAME_H_
#define GAME_H_

#include "interactive_player.h"
#include <iostream>
#include <string>
#include <vector>

template<typename F, typename P=interactive_player<F>, typename Q=interactive_player<F>>
class game
{

	F field;
	P player1;
	Q player2;

	char current;
	std::vector<std::string> stone;

public:

	game() : player1(), player2()
	{
		srand(time(NULL));
		current = rand() % F::max_players + 1;
		stone = {" ", "1", "2"};
	}

	game(const std::vector<std::string>& s) : field(s), player1(), player2(), stone(s)
	{
		srand(time(NULL));
		current = rand() % F::max_players + 1;
	}

	void play()
	{
		bool draw = true;

		while (field.grid_playable()) {
			field.print();

			std::cout << "It's player "
				<< stone[current]
				<< "'s turn." << std::endl;

			play_round();

			if (field.has_won(current)) {
				draw = false;
				break;
			}

			next_round();
		}

		field.print();

		if (draw) {
			std::cout << "It's a draw!" << std::endl;
		} else {
			std::cout << "Player "
				<< stone[current]
				<< " is the winner!" << std::endl;
		}
	}

	void play_round()
	{
		if (current == F::player1)
			ensure_play(player1, F::player1);
		else if (current == F::player2)
			ensure_play(player2, F::player2);
	}

	void next_round()
	{
		current = current % F::max_players + 1;
	}

	template<typename T>
	void ensure_play(T t, int p)
	{
		int column;
		do {
			column = t.play(field);
		} while (!field.column_playable(column));
		field.insert(column, p);
	}

};

#endif  // GAME_H_
