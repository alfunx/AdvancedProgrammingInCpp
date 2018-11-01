#ifndef ALPHONSE_PLAYER_H_
#define ALPHONSE_PLAYER_H_

#include "alphonse_playfield_traits.h"

namespace alphonse {

template<typename F>
class player
{

	const static int alpha = -100;
	const static int beta = 100;
	const int recursion_depth;
	const int player_id;

	struct internal_playfield
	{

		const static int width = F::width;
		const static int height = F::height;
		const static int none = F::none;
		const static int player1 = F::player1;
		const static int player2 = F::player2;
		char rep[F::width][F::height];
		int stoneat(int x, int y) const { return rep[x][y]; }

		internal_playfield(const F& field)
		{
			for (int j = 0; j < height; ++j)
				for (int i = 0; i < width; ++i)
					rep[i][j] = field.stoneat(i, j);
		}

		void insert(int x, int p)
		{
			if (!PT::column_playable(*this, x))
				return;

			int i = height - 1;
			while (rep[x][i] != none) --i;

			rep[x][i] = p;
		}

		void remove(int x, int p)
		{
			if (rep[x][height - 1] == none)
				return;

			int i = 0;
			while (rep[x][i] == none && i < height - 1) ++i;

			if (rep[x][i] == p)
				rep[x][i] = none;
		}

		bool win_on(int x, int p)
		{
			if (!PT::column_playable(*this, x))
				return false;

			insert(x, p);
			bool win = PT::has_won(*this, p);
			remove(x, p);
			return win;
		}

		int moves()
		{
			int m = 0;

			for (int j = 0; j < height; ++j)
				for (int i = 0; i < width; ++i)
					if (rep[i][j] != none)
						++m;

			return m;
		}

	};

	typedef alphonse::playfield_traits<internal_playfield> PT;

public:

	player(int player_id, int recursion_depth = 10) :
		player_id(player_id),
		recursion_depth(recursion_depth)
	{
		/* void */
	}

	int play(const F& field)
	{
		internal_playfield ipf(field);

		for (int i = 0; i < F::width; ++i)
			if (ipf.win_on(i, player_id))
				return i;

		int column = -1;
		int enemy_score = ipf.width * ipf.height;

		for (int i = 0; i < ipf.width; ++i) {
			int c = get_center_column(i);

			if (!PT::column_playable(ipf, c))
				continue;

			ipf.insert(c , player_id);
			int score = calculate_score(ipf, alpha, beta, PT::next_player(player_id), recursion_depth);
			ipf.remove(c , player_id);

			if (score < enemy_score) {
				enemy_score = score;
				column = c;
			}
		}

		return column;
	}

	static int calculate_score(internal_playfield& ipf, int a, int b, int p, int d)
	{
		if (d == 0)
			return 0;

		if (!PT::grid_playable(ipf))
			return 0;

		for (int i = 0; i < F::width; ++i)
			if (ipf.win_on(i, p))
				return (ipf.width * ipf.height + 1 - ipf.moves()) / 2;

		int max = (ipf.width * ipf.height - 1 - ipf.moves()) / 2;
		if (b > max) {
			b = max;
			if (a >= b)
				return b;
		}

		for (int i = 0; i < ipf.width; ++i) {
			int c = get_center_column(i);

			if (!PT::column_playable(ipf, c))
				continue;

			ipf.insert(c , p);
			int score = -calculate_score(ipf, -b, -a, PT::next_player(p), d - 1);
			ipf.remove(c , p);

			if (score >= b)
				return score;
			if (score > a)
				a = score;
		}

		return a;
	}

	static int get_center_column(int i)
	{
		return F::width / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2;
	}

};

}

#endif  // ALPHONSE_PLAYER_H_
