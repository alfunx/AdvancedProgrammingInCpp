#ifndef ALPHONSE_PLAYER_H_
#define ALPHONSE_PLAYER_H_

#include <iostream>
#include <random>
#include "alphonse_playfield_traits.h"

namespace alphonse {

template<typename F>
class player
{

	const static int alpha = -100;
	const static int beta = 100;
	const int recursion_depth;

	const int player_id;
	int column_order[F::width];
	typedef alphonse::playfield_traits<F> pt;

	struct internal_playfield
	{

		const static int width = 7;
		const static int height = 6;
		const static int none = 0;
		const static int player1 = 1;
		const static int player2 = 2;
		char rep[F::width][F::height];
		int stoneat(int x, int y) const { return rep[x][y]; }

		internal_playfield(const F& field) {
			for (int j = 0; j < height; ++j) {
				for (int i = 0; i < width; ++i) {
					rep[i][j] = field.stoneat(i, j);
				}
			}
		}

		int moves() {
			int m = 0;
			for (int j = 0; j < height; ++j) {
				for (int i = 0; i < width; ++i) {
					if (rep[i][j] != none)
						++m;
				}
			}
			return m;
		}

	};
	typedef alphonse::playfield_traits<internal_playfield> ipt;

public:

	player(int player_id, int recursion_depth = 10) :
		player_id(player_id),
		recursion_depth(recursion_depth)
	{
		for(int i = 0; i < F::width; i++) {
			column_order[i] = F::width / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2;
		}
	}

	int play(const F& field)
	{
		internal_playfield ipf(field);

		for (int i = 0; i < F::width; ++i) {
			if (win_on_column(ipf, player_id, i))
				return i;
		}

		int column = -1;
		int enemy_score = ipf.width * ipf.height;

		for (int i = 0; i < ipf.width; ++i) {
			if (!ipt::column_playable(ipf, column_order[i]))
				continue;

			ipt::insert(ipf, ipf.rep, column_order[i], player_id);
			int new_score = calculate_score(ipf, alpha, beta, ipt::next_player(player_id), recursion_depth);
			ipt::remove(ipf, ipf.rep, column_order[i], player_id);

			if (new_score < enemy_score) {
				enemy_score = new_score;
				column = column_order[i];
			}
		}

		std::cout << "column: " << column << std::endl;
		return column;
	}

	int calculate_score(internal_playfield& ipf, int a, int b, int p, int depth) const
	{
		if (depth == 0)
			return a;

		if (!ipt::grid_playable(ipf))
			return 0;

		for (int i = 0; i < F::width; ++i) {
			if (win_on_column(ipf, p, i))
				return (ipf.width * ipf.height + 1 - ipf.moves()) / 2;
		}

		int max = (ipf.width * ipf.height - 1 - ipf.moves()) / 2;
		if (b > max) {
			b = max;
			if (a >= b)
				return b;
		}

		for (int i = 0; i < ipf.width; ++i) {
			if (!ipt::column_playable(ipf, column_order[i]))
				continue;

			ipt::insert(ipf, ipf.rep, column_order[i], p);
			int score = - calculate_score(ipf, -b, -a, ipt::next_player(p), depth - 1);
			ipt::remove(ipf, ipf.rep, column_order[i], p);

			if (score >= b)
				return score;
			if (score > a)
				a = score;
		}

		return a;
	}

	static bool win_on_column(internal_playfield& ipf, int p, int x)
	{
		if (!ipt::column_playable(ipf, x))
			return false;

		ipt::insert(ipf, ipf.rep, x, p);
		bool win = ipt::has_won(ipf, p);
		ipt::remove(ipf, ipf.rep, x, p);
		return win;
	}

};

}

#endif  // ALPHONSE_PLAYER_H_
