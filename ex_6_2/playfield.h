#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

#include <iostream>

class playfield
{

	const static int indent = 4;

	int current_height = playfield::height;

public:

	const static char max_players = 2;
	const static int win = 4;
	const static int win_check = win - 1;

	const static int width = 7;
	const static int height = 6;

	const static int none = 0;
	const static int player1 = 1;
	const static int player2 = 2;

protected:

	char rep[playfield::width][playfield::height];

public:

	playfield()
	{
		for (int j = 0; j < playfield::height; j++) {
			for (int i = 0; i < playfield::width; i++) {
				rep[i][j] = playfield::none;
			}
		}
	}

	int stoneat(int x, int y) const
	{
		return rep[x][y];
	}

public:

	bool column_playable(int x) const
	{
		return x < playfield::width &&
			rep[x][0] == playfield::none;
	}

	bool grid_playable() const
	{
		for (int i = 0; i < width; i++) {
			if (rep[i][0] == playfield::none)
				return true;
		}

		return false;
	}

	void insert(int x, int p)
	{
		int i = playfield::height;
		while (rep[x][--i] != playfield::none);

		current_height = std::min(current_height, i);

		rep[x][i] = p;
	}

	bool has_won(int p) const
	{
		for (int j = playfield::height - 1; j >= current_height; j--) {
			for (int i = 0; i < playfield::width; i++) {
				if (i + playfield::win_check < playfield::width &&
						check_horizontal(i, j, p))
					return true;
				if (j - playfield::win_check > 0 &&
						check_vertical(i, j, p))
					return true;
				if (i + playfield::win_check < playfield::width &&
						j - playfield::win_check > 0 &&
						(check_diagonal_left(i, j, p) ||
						 check_diagonal_right(i, j, p)))
					return true;
			}
		}
		return false;
	}

private:

	bool check_horizontal(int x, int y, int p) const
	{
		for (int i = 0; i < playfield::win; i++) {
			if (rep[x + i][y] != p)
				return false;
		}
		return true;
	}

	bool check_vertical(int x, int y, int p) const
	{
		for (int i = 0; i < playfield::win; i++) {
			if (rep[x][y - i] != p)
				return false;
		}
		return true;
	}

	bool check_diagonal_left(int x, int y, int p) const
	{
		for (int i = 0; i < playfield::win; i++) {
			if (rep[x + i][y - i] != p)
				return false;
		}
		return true;
	}

	bool check_diagonal_right(int x, int y, int p) const
	{
		for (int i = 0; i < playfield::win; i++) {
			if (rep[x + i][y + i - playfield::win_check] != p)
				return false;
		}
		return true;
	}

public:

	void print() const
	{
		// define stones
		const std::string stone[] = {" ", "\e[91m●\e[0m", "\e[93m●\e[0m"};

		// clear screen
		std::cout << "\e[2J\e[1;1H" << std::endl;

		// print header
		playfield::print_header();
		std::cout << std::endl;

		// print grid
		playfield::print_grid(rep, stone);
		std::cout << std::endl;
	}

private:

	static void
	print_header()
	{
		playfield::print_indent();
		for (int i = 0; i < playfield::width; i++) {
			std::cout << "  " << i << " ";
		}
	}

	static void
	print_grid(const char rep[playfield::width][playfield::height], const std::string stone[])
	{
		playfield::print_indent();
		print_line("┌───", "┬───", "┐");

		for (int j = 0; j < playfield::height; j++) {
			playfield::print_indent();

			for (int i = 0; i < playfield::width; i++) {
				std::cout << "│ " << stone[rep[i][j]] << " ";
			}
			std::cout << "│" << std::endl;

			if (j + 1 < playfield::height) {
				playfield::print_indent();
				print_line("├───", "┼───", "┤");
			} else {
				playfield::print_indent();
				print_line("└───", "┴───", "┘");
			}
		}
	}

	static void
	print_line(const std::string l, const std::string m, const std::string r)
	{
		std::cout << l;
		for (int i = 1; i < playfield::width; i++) {
			std::cout << m;
		}
		std::cout << r << std::endl;
	}

	static void
	print_indent()
	{
		for (int i = 0; i < indent; i++) {
			std::cout << ' ';
		}
	}

};

#endif  // PLAYFIELD_H_
