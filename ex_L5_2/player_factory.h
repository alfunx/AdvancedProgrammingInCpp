#ifndef PLAYER_FACTORY_H_
#define PLAYER_FACTORY_H_

#include <list>
#include <memory>
#include <string>

#include "player.h"

typedef std::shared_ptr<player> make_type(const std::string&, int);

class player_factory
{

	static std::list<make_type*> make_functions;

public:

	static void add(make_type* m);
	static std::shared_ptr<player> make(const std::string name, int id);

};

template<typename T>
struct player_factory_helper
{

	player_factory_helper(make_type* make = (make_type*)&T::make)
	{
		player_factory::add(make);
	}

};

#endif  // PLAYER_FACTORY_H_
