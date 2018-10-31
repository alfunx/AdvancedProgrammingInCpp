//Janik Lüchinger, 17-704-339
//Exercise 3, Task 3.3

#ifndef INC_3_3_PLAYER_H
#define INC_3_3_PLAYER_H

namespace janik {

template<typename F>
class player {
    int player_number = -1;
    int enemy_number = -1;
    int count_stones(int column, int row, int direction, const F &field, bool self_bool=true);
    bool check_win_insert(int column, int row, const F &field);
    bool check_defeat_insert(int column, int row, const F &field);
public:
    player() = default;
    player(int i) = default;
    // returns the column where the player decides to throw in his stone
    // F is the playfield which may be any playfield implementing the stoneat method, if you expect a different class
    // because you need methods to verify whether the opponent can win, copy the field into the class that you expect.
    int play(const F &field);
};

}

#endif //INC_3_3_PLAYER_H
