#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <vector>
#include "alphonse_playfield_traits.h"

template<typename F, typename P1, typename P2, typename PT=alphonse::playfield_traits<F>>
class game
{

	F field;
	P1 player1;
	P2 player2;

	char first;
	char current;

public:

	game(P1 a, P2 b, const std::vector<std::string>& s = {" ", "1", "2"}, bool c = true) :
		field(s, c),
		player1(a),
		player2(b)
	{
		srand(time(NULL));
		first = rand() % PT::max_players + 1;
		current = first;
	}

	void play()
	{
		bool draw = true;

		while (PT::grid_playable(field)) {
			field.print();

			std::cout << "It's player "
				<< field.stone[current]
				<< "'s turn." << std::endl;

			play_round();

			if (PT::has_won(field, current)) {
				draw = false;
				break;
			}

			current = PT::next_player(current);
		}

		field.print();

		if (draw) {
			std::cout << "It's a draw!" << std::endl;
			std::cout << "Player "
				<< field.stone[first]
				<< " had the first move." << std::endl;
		} else {
			std::cout << "Player "
				<< field.stone[current]
				<< " is the winner!" << std::endl;
			std::cout << "Player "
				<< field.stone[first]
				<< " had the first move." << std::endl;
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
		} while (!PT::column_playable(field, column));
		field.insert(column, p);
	}

};

#endif  // GAME_H_
