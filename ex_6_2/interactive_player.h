#ifndef INTERACTIVE_PLAYER_H_
#define INTERACTIVE_PLAYER_H_

#include <iostream>

template<typename F>
class interactive_player
{

public:

	int play(const F& field)
	{
		int column;

		do {
			std::cout << ">>> ";
			std::cin >> column;
			std::cout << std::endl;
		} while (field.stoneat(column, 0) != F::none);

		return column;
	}

};

#endif  // INTERACTIVE_PLAYER_H_
