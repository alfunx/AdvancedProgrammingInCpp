#include "player_factory.h"

std::map<std::string, make_type*> player_factory::make_functions;

void player_factory::add(std::string name, make_type* function)
{
	make_functions[name] = function;
}

std::shared_ptr<player> player_factory::make(const std::string name, int id)
{
	auto make = make_functions[name];

	if (!make)
		return NULL;

	return make(id);
}
