#include "player_factory.h"

std::list<make_type*> player_factory::make_functions;

void player_factory::add(make_type* m)
{
	make_functions.push_back(m);
}

std::shared_ptr<player> player_factory::make(const std::string name, int id)
{
	for (auto make : make_functions) {
		auto player = make(name, id);

		if (player)
			return player;
	}

	return NULL;
}
