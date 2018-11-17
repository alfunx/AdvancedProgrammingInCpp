#include <random>
#include <iostream>
#include <vector>

#include "dominik_player.h"

using namespace std;

int dominik_player::enemy_player() {
	if (player_id == playfield::player1) return  playfield::player2;
	else return playfield::player1;
}

int dominik_player::probe(int column, const playfield &field) {
	// May not be necessary
	if (column > playfield::width || column <= 0) return -1;

	int number = 0;
	while (field.stoneat(column - 1, (playfield::height - 1) - number) != playfield::none) {
		number++;
		if (number > (playfield::height - 1)) {
			return - 2;
		}
	}
	return (playfield::height - 1) - number;
}

int dominik_player::choose_column(const playfield &field) {
	vector<int> y_values (7, 0);
	vector<int> connections (7, 0);
	int counter = 0;
	// needed variables for evaluation
	int score = 1;
	int count = 1;
	int dangerous = -1; // Needed to decide choice
	for (int x = 0; x < playfield::width; ++x) {
		y_values[x] = probe(x + 1, field);
		if (y_values[x] >= 0) counter += y_values[x];

		// Try that one
		if (y_values[x] >= 0) {
			counter += y_values[x];

			/* Analise the field for yourself */
			// check diagonal NW SE
			score = 1;
			count = 1;

			while ((x - count >= 0) && (y_values[x] - count >= 0)) {
				if (field.stoneat(x - count, y_values[x] - count) == player_id) { //Check direction NW
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			count = 1;
			while ((x + count < playfield::width) && (y_values[x] + count < playfield::height)) {
				if (field.stoneat(x + count, y_values[x] + count) == player_id) { //Check direction SE
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			if (score == 4) return x + 1;
			else connections[x] += count;

			// check diagonal NE SW
			score = 1;
			count = 1;

			while ((x + count < playfield::width) && (y_values[x] - count >= 0)) {
				if (field.stoneat(x + count, y_values[x] - count) == player_id) { //Check direction NE
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			count = 1;
			while ((x - count >= 0) && (y_values[x] + count < playfield::height)) {
				if (field.stoneat(x - count, y_values[x] + count) == player_id) { //Check direction SW
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			if (score == 4) return x + 1;
			else connections[x] += count;

			// check vertical
			score = 1;
			count = 1;

			while ((y_values[x] + count >= 0) && (y_values[x] + count < playfield::height)) {
				if (field.stoneat(x, y_values[x] + count) == player_id) { //Check South
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			if (score == 4) return x + 1;
			else connections[x] += count;

			// check horizontal
			score = 1;
			count = 1;

			// left
			while ((x + count >= 0) && (x + count < playfield::width)) {
				if (field.stoneat(x + count, y_values[x]) == player_id) {  //Check East
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}
			// right
			count = 1;
			while ((x - count < playfield::height) && (x - count >= 0)) {
				if (field.stoneat(x - count, y_values[x]) == player_id) { //Check West
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			if (score == 4) return x + 1;
			else connections[x] += count;



			/* Analise whether the enemy wins */
			// check diagoinal NW SE
			score = 1;
			count = 1;

			while ((x - count >= 0) && (y_values[x] - count >= 0)) {
				if (field.stoneat(x - count, y_values[x] - count) == enemy_id) { //Check direction NW
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			count = 1;
			while ((x + count < playfield::width) && (y_values[x] + count < playfield::height)) {
				if (field.stoneat(x + count, y_values[x] + count) == enemy_id) { //Check direction SE
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			if (score == 4) return x + 1;

			// check diagonal NE SW
			score = 1;
			count = 1;

			while ((x + count < playfield::width) && (y_values[x] - count >= 0)) {
				if (field.stoneat(x + count, y_values[x] - count) == enemy_id) { //Check direction NE
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			count = 1;
			while ((x - count >= 0) && (y_values[x] + count < playfield::height)) {
				if (field.stoneat(x - count, y_values[x] + count) == enemy_id) { //Check direction SW
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			if (score == 4) return x + 1;

			// check vertical
			score = 1;
			count = 1;

			while ((y_values[x] + count >= 0) && (y_values[x] + count < playfield::height)) {
				if (field.stoneat(x, y_values[x] + count) == enemy_id) { //Check South
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			if (score == 4) return x + 1;

			// check horizontal
			score = 1;
			count = 1;

			// left
			while ((x + count >= 0) && (x + count < playfield::width)) {
				if (field.stoneat(x + count, y_values[x]) == enemy_id) {  //Check East
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}
			// right
			count = 1;
			while ((x - count < playfield::height) && (x - count >= 0)) {
				if (field.stoneat(x - count, y_values[x]) == enemy_id) { //Check West
					score++;
					count++;
				} else break;  //If no combo is detected break from the loop
			}

			// score 3 means a position where two enemy fields are in the middle
			if (score == 4) return x + 1;
			if (score == 3) {
				dangerous = x;
			}
		}
	}

	if (counter == (playfield::height - 1) * playfield::width) {
		return 4;
	}

	else {
		int choice = 3;
		bool shall_choose = true;
		for (int x = 0; x < playfield::width; ++x) {

			if ((connections[choice] < connections[x] && y_values[x] > 0) || (dangerous == x && y_values[x] > 0)) {

				/* check if enemy would win next round */

				// check diagoinal NW SE
				score = 1;
				count = 1;

				while ((x - count >= 0) && (y_values[x] - 1 - count >= 0)) {
					if (field.stoneat(x - count, y_values[x] - 1 - count) == enemy_id) { //Check direction NW
						score++;
						count++;
					} else break;  //If no combo is detected break from the loop
				}

				count = 1;
				while ((x + count < playfield::width) && (y_values[x] - 1 + count < playfield::height)) {
					if (field.stoneat(x + count, y_values[x] - 1 + count) == enemy_id) { //Check direction SE
						score++;
						count++;
					} else break;  //If no combo is detected break from the loop
				}

				if (score >= 3) {
//					cout << "\nNW SE" << endl;
					shall_choose = false;
				}

				// check diagonal NE SW
				score = 1;
				count = 1;

				while ((x + count < playfield::width) && (y_values[x] - 1 - count >= 0)) {
					if (field.stoneat(x + count, y_values[x] - 1 - count) == enemy_id) { //Check direction NE
						score++;
						count++;
					} else break;  //If no combo is detected break from the loop
				}

				count = 1;
				while ((x - count >= 0) && (y_values[x] - 1 + count < playfield::height)) {
					if (field.stoneat(x - count, y_values[x] - 1 + count) == enemy_id) { //Check direction SW
						score++;
						count++;
					} else break;  //If no combo is detected break from the loop
				}

				if (score >= 3) {
					shall_choose = false;
				}

				// check vertical
				score = 1;
				count = 1;

				while ((y_values[x] + count >= 0) && (y_values[x] - 1 + count < playfield::height)) {
					if (field.stoneat(x, y_values[x] - 1 + count) == enemy_id) { //Check South
						score++;
						count++;
					} else break;  //If no combo is detected break from the loop
				}

				if (score >= 3) {
					shall_choose = false;
				}

				// check horizontal
				score = 1;

				count = 1;

				// left
				while ((x + count >= 0) && (x + count < playfield::width)) {
					if (field.stoneat(x + count, y_values[x] - 1) == enemy_id) {  //Check East
						score++;
						count++;
					} else break;  //If no combo is detected break from the loop
				}
				// right
				count = 1;
				while ((x - count < playfield::height) && (x - count >= 0)) {
					if (field.stoneat(x - count, y_values[x] - 1) == enemy_id) { //Check West
						score++;
						count++;
					} else break;  //If no combo is detected break from the loop
				}

				if (score >= 3) {
//					cout << "\nhorizontal" << endl;
					shall_choose = false;
				}

				if (shall_choose) choice = x;
				else if (dangerous == x) {
					choice = x;
					break;
				}
			}
		}
		return choice;
	}
}

dominik_player::dominik_player(int player_id) : player_id(player_id) {
	enemy_id = enemy_player();
}

dominik_player::~dominik_player() {
	/* void */
}

int dominik_player::play(const playfield &field) {
	int choice = choose_column(field);
	cout << "\ncomputers choice is: " << choice << endl;
	return choice;
}

std::shared_ptr<player> dominik_player::make(int id)
{
	return std::make_shared<dominik_player>(id);
}

static register_player<dominik_player> p("dominik");
