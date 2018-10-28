#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

#include <string>
#include <vector>

class playfield
{

	const static int indent = 4;

	int current_height = height;

public:

	const static char max_players = 2;
	const static int win = 4;

	const static int width = 7;
	const static int height = 6;

	const static int none = 0;
	const static int player1 = 1;
	const static int player2 = 2;

	const std::vector<std::string> stone;

protected:

	char rep[width][height];

public:

	playfield();
	playfield(const std::vector<std::string>& s);
	int stoneat(int x, int y) const;

public:

	bool column_playable(int x) const;
	bool grid_playable() const;
	void insert(int x, int p);
	bool has_won(int p) const;

private:

	bool check_horizontal(int x, int y, int p) const;
	bool check_vertical(int x, int y, int p) const;
	bool check_diagonal_left(int x, int y, int p) const;
	bool check_diagonal_right(int x, int y, int p) const;

public:

	void print() const;

private:

	void print_header() const;
	void print_grid() const;
	void print_line(const std::string& l, const std::string& m, const std::string& r) const;
	void print_indent() const;

};

#endif  // PLAYFIELD_H_
