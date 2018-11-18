#include "alphonse_player.h"

#include <iostream>
using namespace std;
struct alphonse_player::internal_playfield : public playfield
{

	static const int min_score = -(width * height) / 2 + 3;
	static const int max_score = (width * height + 1) / 2 - 3;

	unsigned long long rep;
	unsigned long long occ;

	int stoneat(int x, int y) const {
		if (((occ >> (x + width * y)) & 1U) == 0U)
			return none;
		if (((rep >> (x + width * y)) & 1U) == 1U)
			return player1;
		else
			return player2;
	}

	internal_playfield(const playfield& field) :
		rep(0), occ(0)
	{
		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
				int x = field.stoneat(i, j);
				if (x != none)
					occ |= 1ULL << (i + width * j);
				if (x == player1)
					rep |= 1ULL << (i + width * j);
			}
		}

		cout << "rep:" << rep << endl;
		cout << "occ:" << occ << endl;
	}

	virtual ~internal_playfield()
	{
		/* void */
	};

	void insert(int x, int p)
	{
		if (!PT::column_playable(*this, x))
			return;

		int i = height - 1;
		while (i > 0 && ((occ >> (x + width * i)) & 1U) != 0U) --i;

		occ |= 1ULL << (x + width * i);
		if (p == player1)
			rep |= 1ULL << (x + width * i);
	}

	void remove(int x, int p)
	{
		if (((occ >> (x + width * (height - 1))) & 1U) == 0U)
			return;

		int i = 0;
		while (i < height - 1 && ((occ >> (x + width * i)) & 1U) == 0U) ++i;

		if (((occ >> (x + width * i)) & 1U) == 1U) {
			if ((p == player1 && ((rep >> (x + width * i)) & 1U) == 1) || p == player2) {
				occ &= ~(1ULL << (x + width * i));
				rep &= ~(1ULL << (x + width * i));
			}
		}
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
				if (((occ >> (i + width * j)) & 1U) != 0U)
					++m;

		return m;
	}

};

alphonse_player::alphonse_player(int player_id, int recursion_depth) :
	player_id(player_id),
	recursion_depth(recursion_depth)
{
	/* void */
}

alphonse_player::~alphonse_player()
{
	/* void */
}

int alphonse_player::play(const playfield& field)
{
	internal_playfield ipf(field);

	for (int i = 0; i < playfield::width; ++i)
		if (ipf.win_on(i, player_id))
			return i;

	// heuristic
	if (ipf.moves() > playfield::height)
		++recursion_depth;

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

int alphonse_player::calculate_score(internal_playfield& ipf, int a, int b, int p, int d)
{
	if (d == 0)
		return 0;

	if (!PT::grid_playable(ipf))
		return 0;

	for (int i = 0; i < playfield::width; ++i)
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

int alphonse_player::get_center_column(int i)
{
	return playfield::width / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2;
}

std::shared_ptr<player> alphonse_player::make(int id)
{
	return std::make_shared<alphonse_player>(id);
}

static register_player<alphonse_player> p("alphonse");
