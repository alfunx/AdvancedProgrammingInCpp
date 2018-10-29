#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

#include <string>
#include <vector>
#include "alphonse_playfield_traits.h"

class playfield
{

	const static int indent = 4;

	const int clear;

	typedef alphonse::playfield_traits<playfield> pt;

public:

	const static int width = 7;
	const static int height = 6;

	const static int none = 0;
	const static int player1 = 1;
	const static int player2 = 2;

	const std::vector<std::string> stone;

protected:

	char rep[width][height];

public:

	playfield(const std::vector<std::string>& s = {" ", "1", "2"}, bool c = true);
	int stoneat(int x, int y) const;
	void insert(int x, int p);
	void print() const;

private:

	void print_header() const;
	void print_grid() const;
	void print_line(const std::string& l, const std::string& m, const std::string& r) const;
	void print_indent() const;

};

#endif  // PLAYFIELD_H_
