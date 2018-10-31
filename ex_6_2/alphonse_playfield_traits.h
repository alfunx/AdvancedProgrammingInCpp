#ifndef PLAYFIELD_TRAITS_H_
#define PLAYFIELD_TRAITS_H_

namespace alphonse {

template<typename F>
struct playfield_traits
{

	const static int max_players = 2;
	const static int win = 4;

	static bool has_won(const F& field, int p)
	{
		int c = win - 1;
		for (int j = F::height - 1; j >= 0; --j) {
			for (int i = 0; i < F::width; ++i) {
				if (i + c < F::width && check_horizontal(field, i, j, p))
					return true;
				if (j - c >= 0 && check_vertical(field, i, j, p))
					return true;
				if (i + c < F::width && j - c >= 0 &&
						(check_slash(field, i, j, p) ||
						 check_backslash(field, i, j, p)))
					return true;
			}
		}
		return false;
	}

	static bool column_playable(const F& field, int x)
	{
		return x >= 0 && x < F::width && field.stoneat(x, 0) == F::none;
	}

	static bool grid_playable(const F& field)
	{
		for (int i = 0; i < F::width; ++i) {
			if (field.stoneat(i, 0) == F::none)
				return true;
		}

		return false;
	}

	static void insert(const F& field, char rep[F::width][F::height], int x, int p)
	{
		if (!column_playable(field, x))
			return;

		int i = F::height - 1;
		while (rep[x][i] != F::none) --i;

		rep[x][i] = p;
	}

	static void remove(const F& field, char rep[F::width][F::height], int x, int p)
	{
		if (rep[x][F::height - 1] == F::none)
			return;

		int i = 0;
		while (rep[x][i] == F::none && i < F::height - 1) ++i;

		if (rep[x][i] == p)
			rep[x][i] = F::none;
	}

	static int next_player(int current)
	{
		return current % max_players + 1;
	}

private:

	static bool check_horizontal(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i) {
			if (field.stoneat(x + i, y) != p)
				return false;
		}
		return true;
	}

	static bool check_vertical(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i) {
			if (field.stoneat(x, y - i) != p)
				return false;
		}
		return true;
	}

	static bool check_slash(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i) {
			if (field.stoneat(x + i, y - i) != p)
				return false;
		}
		return true;
	}

	static bool check_backslash(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i) {
			if (field.stoneat(x + i, y + i - (win - 1)) != p)
				return false;
		}
		return true;
	}

};

}

#endif  // PLAYFIELD_TRAITS_H_
