#ifndef ALPHONSE_PLAYER_H_
#define ALPHONSE_PLAYER_H_

#include "playfield.h"
#include "player.h"
#include "alphonse_playfield_traits.h"

typedef alphonse::playfield_traits<playfield> PT;

class alphonse_player : public player
{

	const static int alpha = -100;
	const static int beta = 100;
	const int player_id;
	int recursion_depth;

	struct internal_playfield;

	typedef alphonse::playfield_traits<internal_playfield> PT;

public:

	alphonse_player(int player_id, int recursion_depth = 9);
	virtual ~alphonse_player();
	virtual int play(const playfield& field);
	static int calculate_score(internal_playfield& ipf, int a, int b, int p, int d);
	static int get_center_column(int i);

};

#endif  // ALPHONSE_PLAYER_H_
