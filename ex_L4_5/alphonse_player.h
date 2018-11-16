#ifndef ALPHONSE_PLAYER_H_
#define ALPHONSE_PLAYER_H_

#include <unordered_map>

#include "playfield.h"
#include "player.h"
#include "alphonse_playfield_traits.h"

typedef alphonse::playfield_traits<playfield> PT;

class alphonse_player : public player
{

	const static int alpha = -playfield::width * playfield::height / 2;
	const static int beta = playfield::width * playfield::height / 2;
	const int player_id;
	int recursion_depth;

	struct internal_playfield;
	typedef alphonse::playfield_traits<internal_playfield> PT;
	std::unordered_map<std::string, int> transposition;

	int calculate_score(internal_playfield& ipf, int a, int b, int p, int d);
	int get_center_column(int i);

public:

	alphonse_player(int player_id, int recursion_depth = 12);
	virtual ~alphonse_player();
	virtual int play(const playfield& field);

};

#endif  // ALPHONSE_PLAYER_H_
