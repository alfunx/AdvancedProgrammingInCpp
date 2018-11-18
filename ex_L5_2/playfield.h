#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

class playfield
{

public:

	const static int width = 7;
	const static int height = 6;

	const static int none = 0;
	const static int player1 = 1;
	const static int player2 = 2;

	virtual ~playfield()
	{
		/* void */
	};

	virtual int stoneat(int x, int y) const = 0;

};

#endif  // PLAYFIELD_H_
