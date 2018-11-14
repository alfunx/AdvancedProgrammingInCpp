#ifndef ALPHONSE_PLAYFIELD_H_
#define ALPHONSE_PLAYFIELD_H_

#include <string>
#include <vector>

#include "playfield.h"
#include "alphonse_playfield_traits.h"

class alphonse_playfield : public playfield
{

	const static int indent = 4;
	const int clear;
	typedef alphonse::playfield_traits<playfield> PT;

public:

	const std::vector<std::string> stone;

protected:

	char rep[width][height];

public:

	alphonse_playfield(const std::vector<std::string>& s = {" ", "1", "2"}, bool c = true);
	~alphonse_playfield();
	virtual int stoneat(int x, int y) const;
	virtual void insert(int x, int p);
	virtual void print() const;

private:

	virtual void print_header() const;
	virtual void print_grid() const;
	virtual void print_line(const std::string& l, const std::string& m, const std::string& r) const;
	virtual void print_indent() const;

};

#endif  // ALPHONSE_PLAYFIELD_H_
