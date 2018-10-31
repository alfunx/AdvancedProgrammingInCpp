#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "playfield.h"
#include "interactive_player.h"
#include "random_player.h"
#include "alphonse_player.h"

#include "CPKili.h"
#include "janik_player.h"
#include "dominik_player.h"
#include "joni_player.h"

using namespace std;

const int a = playfield::player1;
const int b = playfield::player2;

vector<string> stone {" ", "\e[91m●\e[0m", "\e[93m●\e[0m"};
bool clear = true;

void print_help()
{
	cout << "usage: connect4 [-n] [-c] [-ii | -ri | -ai | -ar | -aa | -ak | -aj | -ad | -ajo]" << endl;
}

template<typename P1, typename P2>
void play(P1 a, P2 b)
{
	game<playfield, P1, P2> g(a, b, stone, clear);
	g.play();
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);
	if (argc < 2) {
		print_help();
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		if ("-ii" == args[i]) {
			play(interactive_player<playfield>(a), interactive_player<playfield>(b));
		} else if ("-ri" == args[i]) {
			play(random_player<playfield>(a), interactive_player<playfield>(b));
		} else if ("-ai" == args[i]) {
			play(alphonse::player<playfield>(a), interactive_player<playfield>(b));
		} else if ("-ar" == args[i]) {
			play(alphonse::player<playfield>(a), random_player<playfield>(b));
		} else if ("-aa" == args[i]) {
			play(alphonse::player<playfield>(a), alphonse::player<playfield>(b));
		} else if ("-ak" == args[i]) {
			play(alphonse::player<playfield>(a), CPKili<playfield>(b));
		} else if ("-aj" == args[i]) {
			play(alphonse::player<playfield>(a), janik::player<playfield>(b));
		} else if ("-ad" == args[i]) {
			play(alphonse::player<playfield>(a), dominik::player<playfield>(b));
		} else if ("-ajo" == args[i]) {
			play(alphonse::player<playfield>(a), joni::aiplayer<playfield>(b));
		} else if ("-n" == args[i]) {
			stone = {" ", to_string(a), to_string(b)};
		} else if ("-c" == args[i]) {
			clear = false;
		} else if ("-h" == args[i]) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	return 0;
}
