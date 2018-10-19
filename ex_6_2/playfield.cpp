#include "playfield.h"
#include <iostream>
#include <string>
#include <vector>

playfield::playfield()
{
	for (int j = 0; j < playfield::height; j++) {
		for (int i = 0; i < playfield::width; i++) {
			rep[i][j] = playfield::none;
		}
	}
	stone = {" ", "1", "2"};
}

playfield::playfield(const std::vector<std::string>& s) : stone(s)
{
	for (int j = 0; j < playfield::height; j++) {
		for (int i = 0; i < playfield::width; i++) {
			rep[i][j] = playfield::none;
		}
	}
}

int playfield::stoneat(int x, int y) const
{
	return rep[x][y];
}

bool playfield::column_playable(int x) const
{
	return x < playfield::width &&
		rep[x][0] == playfield::none;
}

bool playfield::grid_playable() const
{
	for (int i = 0; i < width; i++) {
		if (rep[i][0] == playfield::none)
			return true;
	}

	return false;
}

void playfield::insert(int x, int p)
{
	int i = playfield::height;
	while (rep[x][--i] != playfield::none);

	current_height = std::min(current_height, i);

	rep[x][i] = p;
}

bool playfield::has_won(int p) const
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

bool playfield::check_horizontal(int x, int y, int p) const
{
	for (int i = 0; i < playfield::win; i++) {
		if (rep[x + i][y] != p)
			return false;
	}
	return true;
}

bool playfield::check_vertical(int x, int y, int p) const
{
	for (int i = 0; i < playfield::win; i++) {
		if (rep[x][y - i] != p)
			return false;
	}
	return true;
}

bool playfield::check_diagonal_left(int x, int y, int p) const
{
	for (int i = 0; i < playfield::win; i++) {
		if (rep[x + i][y - i] != p)
			return false;
	}
	return true;
}

bool playfield::check_diagonal_right(int x, int y, int p) const
{
	for (int i = 0; i < playfield::win; i++) {
		if (rep[x + i][y + i - playfield::win_check] != p)
			return false;
	}
	return true;
}

void playfield::print() const
{
	// clear screen
	std::cout << "\e[2J\e[1;1H" << std::endl;

	// print header
	playfield::print_header();
	std::cout << std::endl;

	// print grid
	playfield::print_grid();
	std::cout << std::endl;
}

void playfield::print_header() const
{
	playfield::print_indent();
	for (int i = 0; i < playfield::width; i++) {
		std::cout << "  " << i << " ";
	}
}

void playfield::print_grid() const
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

void playfield::print_line(const std::string& l, const std::string& m, const std::string& r) const
{
	std::cout << l;
	for (int i = 1; i < playfield::width; i++) {
		std::cout << m;
	}
	std::cout << r << std::endl;
}

void playfield::print_indent() const
{
	for (int i = 0; i < indent; i++) {
		std::cout << ' ';
	}
}
