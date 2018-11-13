#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "playfield.h"
#include "alphonse_playfield.h"
#include "player.h"
#include "interactive_player.h"
#include "random_player.h"
#include "alphonse_player.h"

using namespace std;

const int a = playfield::player1;
const int b = playfield::player2;

vector<string> stone {" ", "\e[91m●\e[0m", "\e[93m●\e[0m"};
bool clear = true;

void print_help()
{
	cout << "usage: connect4 [-n] [-c] [-i | -r | -a]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);
	if (argc < 2) {
		print_help();
		return 1;
	}

	vector<player*> players;
	int player_count = 0;

	for (int i = 1; i < argc; ++i) {
		if ("-i" == args[i] && player_count < 2) {
			players.push_back(new interactive_player(++player_count));
		} else if ("-r" == args[i] && player_count < 2) {
			players.push_back(new random_player(++player_count));
		} else if ("-a" == args[i] && player_count < 2) {
			players.push_back(new alphonse_player(++player_count));
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

	alphonse_playfield* field = new alphonse_playfield(stone, clear);
	game g(field, players[0], players[1]);
	g.play();

	for (auto p : players)
		delete p;
	delete field;

	return 0;
}
