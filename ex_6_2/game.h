#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <vector>
#include "alphonse_playfield_traits.h"
#include "interactive_player.h"

template<typename F, typename P=interactive_player<F>, typename Q=interactive_player<F>>
class game
{

	F field;
	P player1;
	Q player2;

	char first;
	char current;

	typedef alphonse::playfield_traits<F> pt;

public:

	game(const std::vector<std::string>& s = {" ", "1", "2"}, bool c = true) :
		field(s, c),
		player1(F::player1),
		player2(F::player2)
	{
		srand(time(NULL));
		first = rand() % pt::max_players + 1;
		current = first;
	}

	void play()
	{
		bool draw = true;

		while (pt::grid_playable(field)) {
			field.print();

			std::cout << "It's player "
				<< field.stone[current]
				<< "'s turn." << std::endl;

			play_round();

			if (pt::has_won(field, current)) {
				draw = false;
				break;
			}

			current = pt::next_player(current);
		}

		field.print();

		if (draw) {
			std::cout << "It's a draw!" << std::endl;
		} else {
			std::cout << "Player "
				<< field.stone[current]
				<< " is the winner!" << std::endl;
			std::cout << "Player "
				<< field.stone[first]
				<< " played the first move." << std::endl;
		}
	}

	void play_round()
	{
		if (current == F::player1)
			ensure_play(player1, F::player1);
		else if (current == F::player2)
			ensure_play(player2, F::player2);
	}

	template<typename T>
	void ensure_play(T t, int p)
	{
		int column;
		do {
			column = t.play(field);
		} while (!pt::column_playable(field, column));
		field.insert(column, p);
	}

};

#endif  // GAME_H_
