/* thomas_playfield.h
 *
 *  Created on: Nov 7, 2008
 *      Author: thg
 */

#ifndef MY_PLAYFIELD_H_
#define MY_PLAYFIELD_H_

#include <iostream>
#include <stdlib.h>

#include <set>

#include "playfield.h"

using namespace std;

class thomas_playfield : public playfield {
	char colp[playfield::width];
	public:
	thomas_playfield() {
		for(int x = 0; x < playfield::width; ++x) {
			colp[x] = playfield::height;
		}
		for(int y = 0; y < playfield::height; ++y) {
			for(int x = 0; x < playfield::width; ++x) {
				rep[x][y] = playfield::none;
			}
		}
	}
	thomas_playfield(const playfield &fld) {
		for (int x = 0; x < playfield::width; ++x) {
			colp[x] = playfield::height;
		}
		for (int y = 0; y < playfield::height; ++y) {
			for (int x = 0; x < playfield::width; ++x) {
				char s = fld.stoneat(x, y);
				rep[x][y] = s;
				if (s != playfield::none) {
					--colp[x];
				}
			}
		}
	}

	void print() {
		cout << endl << " 0123456 " << endl;
		for (int y = 0; y < playfield::height; ++y) {
			cout << "|";
			for (int x = 0; x < playfield::width; ++x) {
				switch(rep[x][y]) {
					case playfield::none:    cout << ' '; break;
					case playfield::player1: cout << 'X'; break;
					case playfield::player2: cout << 'O'; break;
					default:                 cout << '?'; break;
				}
			}
			cout << "|" << endl;
		}
		cout << "`-------'" << endl;
	}

	set<int> get_possible_moves() const {
		set<int> possible_moves;
		for (int i = 0; i < playfield::width; ++i){
			if (rep[i][0] == playfield::none){
				possible_moves.insert(i);
			}
		}
		return possible_moves;
	}

	int insert(int pos, int player) {
		if (pos < 0 || playfield::width <= pos) {
			cerr << "illegal move, out of range" << endl;
			exit(-1);
		}
		if (rep[pos][0] != playfield::none) {
			cerr << "illegal move, column full" << endl;
			exit(-1);
		}

		int p = player;
		int y = --colp[pos];
		rep[pos][y] = p;

		// check vertical victory
		if (y < playfield::height-3 &&
				rep[pos][y+1] == p &&
				rep[pos][y+2] == p &&
				rep[pos][y+3] == p) return -1;

		// check horizontal victory
		int xs = pos-3<0 ? 0:pos-3;
		int xn = pos+4>playfield::width?playfield::width:pos+4;
		int n = 0;
		for (int i = xs; i < xn; ++i) {
			if (rep[i][y] == p) {
				if (++n == 4) return -1;
			} else {
				n=0;
			}
		}

		int ys = y-3, yn = y+1;
		if (ys < 0) ys = 0;
		for (int y = ys; y < yn; ++y) {
			for (int x = 0; x < playfield::width; ++x) {
				if (y < playfield::height-3) {
					if (x > 2 &&
							rep[x-0][y+0] == p && rep[x-1][y+1] == p &&
							rep[x-2][y+2] == p && rep[x-3][y+3] == p) return -1;
					if (x < playfield::width-3 &&
							rep[x+0][y+0] == p && rep[x+1][y+1] == p &&
							rep[x+2][y+2]==p && rep[x+3][y+3]==p) return -1;
				}
			}
		}
		return 0;
	}

	void remove(int pos) {
		int y = colp[pos];
		if (y < playfield::height) {
			rep[pos][y] = playfield::none;
			++colp[pos];
		} else {
			cerr << "illegal remove call at " << pos << endl;
		}
	}

	int haswon(int player) const {
		int p=player;
		for (int y = 0; y < playfield::height; ++y) {
			for (int x = 0; x < playfield::width; ++x) {
				if (x < playfield::width-3 &&
						rep[x+0][y] == p && rep[x+1][y] == p &&
						rep[x+2][y] == p && rep[x+3][y] == p) return -1;
				if (y < playfield::height-3) {
					if (rep[x][y+0] == p && rep[x][y+1] == p &&
							rep[x][y+2] == p && rep[x][y+3] == p) return -1;
					if (x > 2 &&
							rep[x-0][y+0] == p && rep[x-1][y+1] == p &&
							rep[x-2][y+2] == p && rep[x-3][y+3] == p) return -1;
					if (x < playfield::width-3 &&
							rep[x+0][y+0] == p && rep[x+1][y+1] == p &&
							rep[x+2][y+2] == p && rep[x+3][y+3] == p) return -1;
				}
			}
		}
		return 0;
	}

	virtual int stoneat(int x, int y) const { return rep[x][y]; }

protected:

	char rep[playfield::width][playfield::height];

};

#endif /* MY_PLAYFIELD_H_ */
