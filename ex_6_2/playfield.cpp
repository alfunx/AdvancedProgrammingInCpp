#include <iostream>
#include <string>
#include <vector>
#include "playfield.h"

playfield::playfield(const std::vector<std::string>& s, bool c) :
	stone(s),
	clear(c)
{
	std::fill(&rep[0][0], &rep[0][0] + width * height, (int)none);
}

int playfield::stoneat(int x, int y) const
{
	return rep[x][y];
}

void playfield::insert(int x, int p)
{
	if (!PT::column_playable(*this, x))
		return;

	int i = height - 1;
	while (rep[x][i] != none) --i;

	rep[x][i] = p;
}

void playfield::print() const
{
	// clear screen
	if (clear)
		std::cout << "\e[2J\e[1;1H" << std::endl;

	// print header
	print_header();
	std::cout << std::endl;

	// print grid
	print_grid();
	std::cout << std::endl;
}

void playfield::print_header() const
{
	print_indent();
	for (int i = 0; i < width; ++i) {
		std::cout << "  " << i << " ";
	}
}

void playfield::print_grid() const
{
	print_indent();
	print_line("┌───", "┬───", "┐");

	for (int j = 0; j < height; ++j) {
		print_indent();

		for (int i = 0; i < width; ++i) {
			std::cout << "│ " << stone[rep[i][j]] << " ";
		}
		std::cout << "│" << std::endl;

		if (j + 1 < height) {
			print_indent();
			print_line("├───", "┼───", "┤");
		} else {
			print_indent();
			print_line("└───", "┴───", "┘");
		}
	}
}

void playfield::print_line(const std::string& l, const std::string& m, const std::string& r) const
{
	std::cout << l;
	for (int i = 1; i < width; ++i) {
		std::cout << m;
	}
	std::cout << r << std::endl;
}

void playfield::print_indent() const
{
	for (int i = 0; i < indent; ++i) {
		std::cout << ' ';
	}
}
