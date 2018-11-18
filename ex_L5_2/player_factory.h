#ifndef PLAYER_FACTORY_H_
#define PLAYER_FACTORY_H_

#include <map>
#include <memory>
#include <string>

#include "player.h"

typedef std::shared_ptr<player> make_type(int);

class player_factory
{

	static std::map<std::string, make_type*> make_functions;

public:

	player_factory() = delete;
	static void add(std::string name, make_type* function);
	static std::shared_ptr<player> make(const std::string name, int id);

};

template<typename T>
struct register_player
{

	register_player(std::string name, make_type* make = (make_type*)&T::make)
	{
		player_factory::add(name, make);
	}

};

#endif  // PLAYER_FACTORY_H_
