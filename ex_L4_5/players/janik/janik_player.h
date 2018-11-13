//
// Created by Janik on 10.11.2018.
//

#ifndef JANIK_PLAYER_H_
#define JANIK_PLAYER_H_

#include "player.h"
#include "playfield.h"

class janik_player : public player {
public:
    explicit janik_player(int player_id);
    virtual int play(const playfield &field) override;
    virtual ~janik_player() = default;

protected:
    int player_number, enemy_number;

    int count_stones(int column, int row, int direction, const playfield &field, int player_id);
    bool check_insert(int column, int row, const playfield &field, int player_id);
};


janik_player::janik_player(int player_id) {
    player_number = player_id;
    if(player_number%2 == 0) {
        enemy_number = 1;
    } else {
        enemy_number = 2;
    }
}
int janik_player::play(const playfield &field) {
    int top = 0;
    for(int column=0; column < field.width; ++column) {//check if PLAYER can win in 1 move
        if(field.stoneat(column, top) == field.none) {//column is available
            int row = top;
            while((field.stoneat(column, row) == '\000') && (row <= field.height-1)) {
                ++row;
            }
            --row;//get lowest available slot
            if(check_insert(column, row, field, this->player_number)) {
                return column;
            }
        }
    }//now, no direct win is possible

    for(int column=0; column < field.width; ++column) {//check if ENEMY can win in 1 move
        if (field.stoneat(column, top) == field.none) {//column is available
            int row = top;
            while ((field.stoneat(column, row) == '\000') && (row <= field.height-1)) {
                ++row;
            }
            --row;//get lowest available slot
            if (check_insert(column, row, field, this->enemy_number)) {
                return column;//enemy has one way less to win
            }
        }
    }//now, enemy was unable to win

    int rand_col, rand_row, rand_counter=0;
    do {
        rand_col = 1 + (rand() % (int)(field.width-1));
        //printf("Random = %d\n", rand_col);
        --rand_col;
        rand_row = top;
        while ((field.stoneat(rand_col, rand_row) == '\000') && (rand_row <= field.height-1)) {
            ++rand_row;
        }
        --rand_row;//get lowest available slot for hypothetically inserting a stone in rand_col
        ++rand_counter;
    } while(((field.stoneat(rand_col, top) != field.none) && (rand_counter < 100))
            || (check_insert(rand_col, rand_row-1, field, this->enemy_number)));//do again if: occupied, <100 times
    // or if immediate defeat

    if(rand_counter < 100) {//slot is available and no immediate defeat
        //printf("counter<100\n");
        return rand_col;
    } else if(rand_counter >= 100) {//after 100 tries, check manually for free slot
        for(int man_col = 0; man_col < field.width; ++man_col) {//check if inserting possible without immediate defeat
            if(field.stoneat(man_col, top) == field.none) {
                int man_row = top;
                while ((field.stoneat(man_col, man_row) == '\000') && (man_row <= field.height-1)) {
                    ++man_row;
                }
                --man_row;
                if(!check_insert(man_col, man_row-1, field, this->enemy_number)) {
                    //printf("counter >= 100, w/o loss\n");
                    return man_col;
                }
            }
        }

        for (int column = 0; column < field.width; ++column) {//check manually if any column available
            if(field.stoneat(column, top) == field.none) {
                //printf("counter >= 100, manually\n");
                return column;
            }
        }//no free slot found, playfield should prevent allowing insertion without any free slot
        throw "Exception: Playfield is full!";
    } else {
        return -1;//something really unexpected happened
    }
}
int janik_player::count_stones(int column, int row, int direction, const playfield &field, int player_id) {
/*count amount of stones for player in direction recursively, returns amount of stones connected
     * direction 0 = left           if column >= 0
     * direction 1 = top-left       if column >= 0 && row >= 0
     * direction 2 = top            if row >= 0
     * direction 3 = top-right      if column < width && row >= 0
     * direction 4 = right          if column < width
     * direction 5 = bottom-right   if column < width && row < height
     * direction 6 = bottom         if row < height
     * direction 7 = bottom-left    if column >= 0 && row < height
     */

    if((direction == 0) && (column >= 0)) {//left
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column-1, row, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else if((direction == 1) && (column >= 0) && (row >= 0)) {//top-left
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column-1, row-1, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else if((direction == 2) && (row >= 0)) {//top
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column, row-1, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else if((direction == 3) && (column < field.width) && (row >= 0)) {//top-right
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column+1, row-1, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else if((direction == 4) && (column < field.width)) {//right
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column+1, row, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else if((direction == 5) && (column < field.width) && (row < field.height)) {//bottom-right
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column+1, row+1, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else if((direction == 6) && (row < field.height)) {//bottom
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column, row+1, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else if((direction == 7) && (column >= 0) && (row < field.height)) {//bottom-left
        if(field.stoneat(column, row) == player_id) {
            return 1 + count_stones(column-1, row+1, direction, field, player_id);
        } else {//streak broken by other player
            return 0;
        }
    } else {//out of bounds
        return 0;
    }
}
bool janik_player::check_insert(int column, int row, const playfield &field, int player_id) {
    int hori, diagL, vert, diagR;
    //printf("WIN_insert:\n");

    //center slot not checked (since hypothetical situation), added separately to amount
    hori = count_stones(column-1, row, 0, field, player_id) + count_stones(column+1, row, 4, field, player_id) + 1;
    diagL = count_stones(column-1, row-1, 1, field, player_id) + count_stones(column+1, row+1, 5, field, player_id) + 1;
    vert = count_stones(column, row-1, 2, field, player_id) + count_stones(column, row+1, 6, field, player_id) + 1;
    diagR = count_stones(column+1, row-1, 3, field,player_id) + count_stones(column-1, row+1, 7, field, player_id) + 1;

    return (((hori >= 4) || (diagL >= 4) || (vert >= 4) || (diagR >= 4))
            && (field.stoneat(column, 0) == field.none));
}

#endif //JANIK_PLAYER_H_
