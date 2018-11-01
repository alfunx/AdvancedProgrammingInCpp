#ifndef ALPHONSE_PLAYFIELD_TRAITS_H_
#define ALPHONSE_PLAYFIELD_TRAITS_H_

namespace alphonse {

template<typename F>
struct playfield_traits
{

	const static int max_players = 2;
	const static int win = 4;

	static bool has_won(const F& field, int p)
	{
		int c = win - 1;
		for (int j = 0; j < F::height; ++j) {
			for (int i = 0; i < F::width; ++i) {
				if (i + c < F::width &&
						check_horizontal(field, i, j, p))
					return true;
				if (j + c < F::height &&
						check_vertical(field, i, j, p))
					return true;
				if (i + c < F::width && j + c < F::height &&
						(check_slash(field, i, j, p) ||
						 check_backslash(field, i, j, p)))
					return true;
			}
		}
		return false;
	}

	static bool column_playable(const F& field, int x)
	{
		return x >= 0 && x < F::width &&
			field.stoneat(x, 0) == F::none;
	}

	static bool grid_playable(const F& field)
	{
		for (int i = 0; i < F::width; ++i)
			if (field.stoneat(i, 0) == F::none)
				return true;

		return false;
	}

	static int next_player(int current)
	{
		return current % max_players + 1;
	}

private:

	static bool check_horizontal(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i)
			if (field.stoneat(x + i, y) != p)
				return false;

		return true;
	}

	static bool check_vertical(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i)
			if (field.stoneat(x, y + i) != p)
				return false;

		return true;
	}

	static bool check_slash(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i)
			if (field.stoneat(x + i, y + (win - 1) - i) != p)
				return false;

		return true;
	}

	static bool check_backslash(const F& field, int x, int y, int p)
	{
		for (int i = 0; i < win; ++i)
			if (field.stoneat(x + i, y + i) != p)
				return false;

		return true;
	}

};

}

#endif  // ALPHONSE_PLAYFIELD_TRAITS_H_
