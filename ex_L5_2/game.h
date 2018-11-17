#ifndef GAME_H_
#define GAME_H_

#include <memory>

#include "playfield.h"
#include "alphonse_playfield.h"
#include "alphonse_playfield_traits.h"
#include "player.h"

typedef alphonse::playfield_traits<playfield> PT;

class game
{

	std::shared_ptr<alphonse_playfield> field;
	std::shared_ptr<player> player1;
	std::shared_ptr<player> player2;
	char current;

	void play_round();
	void ensure_play(std::shared_ptr<player> player, int p);

public:

	game(std::shared_ptr<alphonse_playfield> f, std::shared_ptr<player> a, std::shared_ptr<player> b);
	void play();

};

#endif  // GAME_H_
