#ifndef DOMINIK_PLAYER_H
#define DOMINIK_PLAYER_H

#include <random>
#include <iostream>
#include <vector>

namespace dominik {

using namespace std;

template<typename F>
class player {
    int player_id;
    int enemy_id;

    int enemy_player() {
        if (player_id == F::player1) return  F::player2;
        else return F::player1;
    }

    int probe(int column, const F &field) {
        // May not be necessary
        if (column > field.width || column <= 0) return -1;

        int number = 0;
        while (field.stoneat(column - 1, (field.height - 1) - number) != field.none) {
            number++;
            if (number > (field.height - 1)) {
                return - 2;
            }
        }
        return (field.height - 1) - number;
//        return field.height - number;
    }

    int choose_column(const F &field) {
        vector<int> y_values (7, 0);
        vector<int> connections (7, 0);
        int counter = 0;
        // needed variables for evaluation
        int score = 1;
        int count = 1;
        int dangerous = -1; // Needed to decide choice
        for (int x = 0; x < field.width; ++x) {
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
                while ((x + count < field.width) && (y_values[x] + count < field.height)) {
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

                while ((x + count < field.width) && (y_values[x] - count >= 0)) {
                    if (field.stoneat(x + count, y_values[x] - count) == player_id) { //Check direction NE
                        score++;
                        count++;
                    } else break;  //If no combo is detected break from the loop
                }

                count = 1;
                while ((x - count >= 0) && (y_values[x] + count < field.height)) {
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

                while ((y_values[x] + count >= 0) && (y_values[x] + count < field.height)) {
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
                while ((x + count >= 0) && (x + count < field.width)) {
                    if (field.stoneat(x + count, y_values[x]) == player_id) {  //Check East
                        score++;
                        count++;
                    } else break;  //If no combo is detected break from the loop
                }
                // right
                count = 1;
                while ((x - count < field.height) && (x - count >= 0)) {
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
                while ((x + count < field.width) && (y_values[x] + count < field.height)) {
                    if (field.stoneat(x + count, y_values[x] + count) == enemy_id) { //Check direction SE
                        score++;
                        count++;
                    } else break;  //If no combo is detected break from the loop
                }

                if (score == 4) return x + 1;

                // check diagonal NE SW
                score = 1;
                count = 1;

                while ((x + count < field.width) && (y_values[x] - count >= 0)) {
                    if (field.stoneat(x + count, y_values[x] - count) == enemy_id) { //Check direction NE
                        score++;
                        count++;
                    } else break;  //If no combo is detected break from the loop
                }

                count = 1;
                while ((x - count >= 0) && (y_values[x] + count < field.height)) {
                    if (field.stoneat(x - count, y_values[x] + count) == enemy_id) { //Check direction SW
                        score++;
                        count++;
                    } else break;  //If no combo is detected break from the loop
                }

                if (score == 4) return x + 1;

                // check vertical
                score = 1;
                count = 1;

                while ((y_values[x] + count >= 0) && (y_values[x] + count < field.height)) {
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
                while ((x + count >= 0) && (x + count < field.width)) {
                    if (field.stoneat(x + count, y_values[x]) == enemy_id) {  //Check East
                        score++;
                        count++;
                    } else break;  //If no combo is detected break from the loop
                }
                // right
                count = 1;
                while ((x - count < field.height) && (x - count >= 0)) {
                    if (field.stoneat(x - count, y_values[x]) == enemy_id) { //Check West
                        score++;
                        count++;
                    } else break;  //If no combo is detected break from the loop
                }

                // score 3 means a position where two enemy fields are in the middle
                if (score == 4) return x + 1;
                if (score == 3) {
                    cout << "column " << x + 1 << "was dangerous" << endl;
                    dangerous = x;
                }
            }
        }

            if (counter == (field.height - 1) * field.width) {
                return 4;
            }

            else {
                int choice = 3;
//                int choice = dangerous;
                bool shall_choose = true;
                for (int x = 0; x < field.width; ++x) {
                    cout << "connection of " << x << ": " << connections[x] << endl;
//                    if (connections[choice] < connections[x] && y_values[x] > 0) {
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
                        while ((x + count < field.width) && (y_values[x] - 1 + count < field.height)) {
                            if (field.stoneat(x + count, y_values[x] - 1 + count) == enemy_id) { //Check direction SE
                                score++;
                                count++;
                            } else break;  //If no combo is detected break from the loop
                        }

                        if (score >= 3) {
                            cout << "\nNW SE" << endl;
                            shall_choose = false;
                        }

                        // check diagonal NE SW
                        score = 1;
                        count = 1;

                        while ((x + count < field.width) && (y_values[x] - 1 - count >= 0)) {
                            if (field.stoneat(x + count, y_values[x] - 1 - count) == enemy_id) { //Check direction NE
                                score++;
                                count++;
                            } else break;  //If no combo is detected break from the loop
                        }

                        count = 1;
                        while ((x - count >= 0) && (y_values[x] - 1 + count < field.height)) {
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

                        while ((y_values[x] + count >= 0) && (y_values[x] - 1 + count < field.height)) {
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
                        while ((x + count >= 0) && (x + count < field.width)) {
                            if (field.stoneat(x + count, y_values[x] - 1) == enemy_id) {  //Check East
                                score++;
                                count++;
                            } else break;  //If no combo is detected break from the loop
                        }
                        // right
                        count = 1;
                        while ((x - count < field.height) && (x - count >= 0)) {
                            if (field.stoneat(x - count, y_values[x] - 1) == enemy_id) { //Check West
                                score++;
                                count++;
                            } else break;  //If no combo is detected break from the loop
                        }

                        if (score >= 3) {
                            cout << "\nhorizontal" << endl;
                            shall_choose = false;
                        }

                        if (shall_choose) choice = x;
                        else if (dangerous == x) {
                            cout << "\ndangarous: " << x << endl;
                            choice = x;
                            break;
                        }

                        cout << "\nChoice is: " << choice;
                    }
                }
                return choice + 1;
            }
    }
public:
    player(int player_id) : player_id(player_id) {
        enemy_id = enemy_player();
    };
// returns the column where the player decides to throw in his
// stone
// F is the playfield which may be any playfield implementing
// the stoneat method, if you expect a different class because
// you need methods to verify whether the opponent can win,
// copy the field into the class that you expect.
    int play(const F &field) {
            int choice = choose_column(field);
            cout << "\ncomputers choice is: " << choice << endl;
        return choice;
    }
};

}

#endif // DOMINIK_PLAYER_H
