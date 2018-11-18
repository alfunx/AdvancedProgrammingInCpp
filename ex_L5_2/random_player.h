#ifndef RANDOM_PLAYER_H_
#define RANDOM_PLAYER_H_

#include "playfield.h"
#include "player.h"
#include "player_factory.h"
#include "alphonse_playfield_traits.h"

typedef alphonse::playfield_traits<playfield> PT;

class random_player : public player
{

	int player_id;

public:

	random_player(int player_id);
	virtual ~random_player();
	virtual int play(const playfield& field);

	static std::shared_ptr<player> make(int id);

};

#endif  // RANDOM_PLAYER_H_
