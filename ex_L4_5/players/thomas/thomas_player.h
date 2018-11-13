/*
 * thomas_player.h
 *
 *  Created on: Nov 7, 2008
 *      Author: thg
 */

#ifndef COMPUTER_PLAYER_SMART_H_
#define COMPUTER_PLAYER_SMART_H_

#include <iostream>
#include <stdlib.h>
#include <set>
#include <string>

#include "playfield.h"
#include "player.h"
#include "thomas_playfield.h"

inline int other_player(int player) {
	return player == playfield::player1 ?
		playfield::player2 :
		playfield::player1;
}

template<typename C>
inline void print_container(const C &container) {
	typename C::iterator begin = container.begin(), end = container.end();
	while (begin != end) {
		cout << *begin << " ";
		++begin;
	}
	cout << endl;
}

class thomas_player : public player {
	int player;
	int max_depth;
	public:
	thomas_player(int player, int depth) :
		player(player), max_depth(depth)
	{
		time_t t;
		time(&t);
		srand(t);
	}

	int play(const playfield &field) {
		thomas_playfield fld(field);

		// compute the possible moves and initialize the good moves
		set<int> possible_moves = fld.get_possible_moves();

		set<int> good_moves = possible_moves;
		int win = compute_good_moves(fld, good_moves, player, 0);
		if (win >= 0) return win;

		if (good_moves.size() == 0) {
			// no good moves
			good_moves = possible_moves;
		}

		// insert stone into a random column
		int p = rand()%good_moves.size();
		set<int>::iterator begin = good_moves.begin();
		while (p > 0) {
			++begin;
			--p;
		}

		return *begin;
	}

	int compute_good_moves(thomas_playfield fld,
			set<int> &pmoves, int player, int depth)
	{
		set<int>::iterator begin = pmoves.begin(), end = pmoves.end();
		while (begin != end) {
			int pos = *begin;
			// can we win the game by inserting a stone at pos?
			if (fld.insert(pos, player)) {
				fld.remove(pos);
				return pos;
			}
			fld.remove(pos);
			++begin;
		}

		// reached maximum recursion depth?
		if (depth == max_depth) return -1;

		begin = pmoves.begin();
		while (begin != end) {
			int pos = *begin;

			// we cannot win by this - already checked above
			fld.insert(pos, player);

			// filter out the bad moves, i.e., the opponent's win moves
			set<int> op_moves = fld.get_possible_moves();

			int win = compute_good_moves(fld, op_moves, other_player(player), depth+1);
			fld.remove(pos);
			if (win >= 0) {
				// opponent will win, if we do this
				pmoves.erase(begin++);
				continue;
			}

			if (op_moves.size() == 0) {
				return pos;
			}

			++begin;
		}
		return -1;
	}
};

#endif /* COMPUTER_PLAYER_SMART_H_ */
