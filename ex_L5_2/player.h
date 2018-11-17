#ifndef PLAYER_H_
#define PLAYER_H_

#include "playfield.h"

class player
{

public:

	virtual ~player()
	{
		/* void */
	};

	virtual int play(const playfield& field) =0;

};

#endif  // PLAYER_H_
