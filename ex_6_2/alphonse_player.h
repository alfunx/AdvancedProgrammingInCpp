#ifndef ALPHONSE_PLAYER_H_
#define ALPHONSE_PLAYER_H_

#include <iostream>
#include <random>
#include "alphonse_playfield_traits.h"

namespace alphonse {

template<typename F>
class player
{

	int player_id;
	typedef alphonse::playfield_traits<F> pt;

	static const int distribution_factor = 6;
	std::default_random_engine generator;
	std::binomial_distribution<int> distribution;

	struct internal_playfield
	{
		const static int width = 7;
		const static int height = 6;
		const static int none = 0;
		const static int player1 = 1;
		const static int player2 = 2;
		char rep[F::width][F::height];
		int stoneat(int x, int y) const { return rep[x][y]; }
	};
	typedef alphonse::playfield_traits<internal_playfield> ipt;

public:

	player(int player_id) :
		player_id(player_id),
		distribution((F::width - 1) * distribution_factor, 0.5),
		generator(time(NULL))
	{
		/* void */
	}

	int play(const F& field)
	{
		internal_playfield ipf;
		pt::copy(field, ipf.rep);

		int column = -1;

		// win
		column = check_win_grid(ipf, player_id);
		if (column >= 0) return column;

		// prevent oponent win
		column = check_win_grid(ipf, next_player(player_id));
		if (column >= 0) return column;

		// random move
		int enemy_win = 0;
		int try_guess = distribution_factor * F::width * 2;

		do {
			do {
				column = get_random_column();
				std::cout << ">>> " << column << std::endl;
			} while (!pt::column_playable(field, column));

			ipt::insert(ipf, ipf.rep, column, player_id);
			enemy_win = check_win_grid(ipf, next_player(player_id));
			// std::cout << "enemy: " << enemy_win << std::endl;
			ipt::remove(ipf, ipf.rep, column);
		} while (enemy_win > 0 && --try_guess > 0);
		std::cout << std::endl;

		return column;
	}

	int get_random_column()
	{
		int column;
		do {
			column = distribution(generator) - (distribution_factor - 1) * ((F::width - 1) / 2);
		} while (column < 0 || column >= F::width);
		return column;
	}

	int check_win_grid(internal_playfield& ipf, int pid)
	{
		for (int i = 0; i < F::width; ++i) {
			if (check_win_column(ipf, pid, i))
				return i;
		}

		return -1;
	}

	bool check_win_column(internal_playfield& ipf, int pid, int x)
	{
		if (!ipt::column_playable(ipf, x))
			return false;

		ipt::insert(ipf, ipf.rep, x, pid);
		bool win = ipt::has_won(ipf, pid);
		ipt::remove(ipf, ipf.rep, x);
		return win;
	}

	int next_player(int current)
	{
		return current % pt::max_players + 1;
	}

};

}

#endif  // ALPHONSE_PLAYER_H_
