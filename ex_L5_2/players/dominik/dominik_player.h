#ifndef DOMINIK_PLAYER_H_
#define DOMINIK_PLAYER_H_

#include <iostream>
#include "playfield.h"
#include "player.h"
#include "player_factory.h"

class dominik_player : public player {
	const int player_id;
	int enemy_id;

	int enemy_player();

	int probe(int column, const playfield &field);

	int choose_column(const playfield &field);

public:
	dominik_player(int player_id);

	virtual ~dominik_player();

	virtual int play(const playfield &field);

	static std::shared_ptr<player> make(int id);
};

#endif // DOMINIK_PLAYER_H_
