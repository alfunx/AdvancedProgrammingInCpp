#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "playfield.h"
#include "alphonse_player.h"
#include "random_player.h"
using namespace std;

void print_help()
{
	cout << "usage: connect4 [-n] [-c] [-ii | -ri | -ai | -ar | -aa]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);
	vector<string> stone {" ", "\e[91m●\e[0m", "\e[93m●\e[0m"};
	bool clear = true;

	if (argc < 2) {
		print_help();
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		if ("-ii" == args[i]) {
			game<playfield> g(stone, clear);
			g.play();
		} else if ("-ri" == args[i]) {
			game<playfield, random_player<playfield>> g(stone, clear);
			g.play();
		} else if ("-ai" == args[i]) {
			game<playfield, alphonse::player<playfield>> g(stone, clear);
			g.play();
		} else if ("-ar" == args[i]) {
			game<playfield, alphonse::player<playfield>, random_player<playfield>> g(stone, clear);
			g.play();
		} else if ("-aa" == args[i]) {
			game<playfield, alphonse::player<playfield>, alphonse::player<playfield>> g(stone, clear);
			g.play();
		} else if ("-n" == args[i]) {
			stone = {" ", "1", "2"};
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
