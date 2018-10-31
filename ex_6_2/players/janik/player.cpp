//Janik Lüchinger, 17-704-339
//Exercise 3, Task 3.3

#include <iostream>
#include <cstdlib>//random generator
#include <ctime>//random generator
#include "janik_player.h"
using namespace std;

namespace janik {
//
// template <typename F>
// int player<F>::count_stones(int column, int row, int direction, const F &field, bool self_bool) {
//     /*count amount of stones for player in direction recursively, returns amount of stones connected
//      * direction 0 = left           if column >= 0
//      * direction 1 = top-left       if column >= 0 && row >= 0
//      * direction 2 = top            if row >= 0
//      * direction 3 = top-right      if column < width && row >= 0
//      * direction 4 = right          if column < width
//      * direction 5 = bottom-right   if column < width && row < height
//      * direction 6 = bottom         if row < height
//      * direction 7 = bottom-left    if column >= 0 && row < height
//      */
//     int player_id;
//     if(self_bool) {
//         player_id = player_number;//checking for wins
//         //printf("self_bool TRUE, player_id = %d\n", player_id);
//     } else {
//         player_id = enemy_number;//checking for losses
//         //printf("self_bool FALSE, player_id = %d\n", player_id);
//     }
//
//     if((direction == 0) && (column >= 0)) {//left
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column-1, row, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else if((direction == 1) && (column >= 0) && (row >= 0)) {//top-left
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column-1, row-1, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else if((direction == 2) && (row >= 0)) {//top
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column, row-1, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else if((direction == 3) && (column < field.width) && (row >= 0)) {//top-right
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column+1, row-1, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else if((direction == 4) && (column < field.width)) {//right
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column+1, row, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else if((direction == 5) && (column < field.width) && (row < field.height)) {//bottom-right
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column+1, row+1, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else if((direction == 6) && (row < field.height)) {//bottom
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column, row+1, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else if((direction == 7) && (column >= 0) && (row < field.height)) {//bottom-left
//         if(field.stoneat(column, row) == player_id) {
//             return 1 + count_stones(column-1, row+1, direction, field, self_bool);
//         } else {//streak broken by other player
//             return 0;
//         }
//     } else {//out of bounds
//         return 0;
//     }
// }
// template <typename F>
// bool player<F>::check_win_insert(int column, int row, const F &field) {
//     int hori, diagL, vert, diagR;
//     //printf("WIN_insert:\n");
//
//     //center slot not checked (since hypothetical situation), added separately to amount
//     hori = count_stones(column-1, row, 0, field) + count_stones(column+1, row, 4, field) + 1;
//     diagL = count_stones(column-1, row-1, 1, field) + count_stones(column+1, row+1, 5, field) + 1;
//     vert = count_stones(column, row-1, 2, field) + count_stones(column, row+1, 6, field) + 1;
//     diagR = count_stones(column+1, row-1, 3, field) + count_stones(column-1, row+1, 7, field) + 1;
//
//     /*
//     if(((hori >= 4) || (diagL >= 4) || (vert >= 4) || (diagR >= 4))
//     && (field.stoneat(column, 0) == field.none)) {
//         //column still available
//         printf("Thought to WIN at column %d (idx %d)\n", column+1, column);
//         return true;
//     } else {
//         return false;
//     }*/
//     return (((hori >= 4) || (diagL >= 4) || (vert >= 4) || (diagR >= 4))
//            && (field.stoneat(column, 0) == field.none));
// }
// template <typename F>
// bool player<F>::check_defeat_insert(int column, int row, const F &field) {
//     int hori, diagL, vert, diagR;
//     //printf("DEFEAT_insert:\n");
//
//     //center slot not checked (since hypothetical situation), added separately to amount
//     hori = count_stones(column-1, row, 0, field, false) + count_stones(column+1, row, 4, field, false) + 1;
//     diagL = count_stones(column-1, row-1, 1, field, false) + count_stones(column+1, row+1, 5, field, false) + 1;
//     vert = count_stones(column, row-1, 2, field, false) + count_stones(column, row+1, 6, field, false) + 1;
//     diagR = count_stones(column+1, row-1, 3, field, false) + count_stones(column-1, row+1, 7, field, false) + 1;
//
//     /*
//     if(((hori >= 4) || (diagL >= 4) || (vert >= 4) || (diagR >= 4))
//     && (field.stoneat(column, 0) == field.none)) {
//         //column still available
//         printf("Thought of DEFEAT at column %d (idx %d)\n", column+1, column);
//         return true;
//     } else {
//         return false;
//     }*/
//     return (((hori >= 4) || (diagL >= 4) || (vert >= 4) || (diagR >= 4))
//               && (field.stoneat(column, 0) == field.none));
// }
//
// template <typename F>
// int player<F>::play(const F &field) {//reads the playfield and decides in which column to insert a stone, returns column
//     if(player_number == -1) {//first call
//         bool empty = true;
//         for(int column=0; column < field.width; ++column) {
//             int stone = field.stoneat(column, field.height-1);
//             if(stone != field.none) {
//                 empty = false;
//                 if(stone == field.player1) {
//                     player_number = field.player2;
//                     enemy_number = field.player1;
//                 } else {
//                     player_number = field.player1;
//                     enemy_number = field.player2;
//                 }
//             }
//         }
//         if(empty) {//field still empty
//             //printf("player_number = 1, empty-case\n");
//             player_number = field.player1;//ASSUMPTION: STARTING WITH PLAYER1!
//             enemy_number = field.player2;
//         }
//         //printf("player_number = %d\n", player_number);
//         srand(time(NULL));//seeding random generator upon first call (executed only once)
//         //srand() may have already been called in playfield, depending on implementation
//     }
//
//     int top = 0;
//     for(int column=0; column < field.width; ++column) {//check if PLAYER can win in 1 move
//         if(field.stoneat(column, top) == field.none) {//column is available
//             int row = top;
//             while((field.stoneat(column, row) == '\000') && (row <= field.height-1)) {
//                 ++row;
//             }
//             --row;//get lowest available slot
//             if(check_win_insert(column, row, field)) {
//                 return column;
//             }
//         }
//     }//now, no direct win is possible
//
//     for(int column=0; column < field.width; ++column) {//check if ENEMY can win in 1 move
//         if (field.stoneat(column, top) == field.none) {//column is available
//             int row = top;
//             while ((field.stoneat(column, row) == '\000') && (row <= field.height-1)) {
//                 ++row;
//             }
//             --row;//get lowest available slot
//             if (check_defeat_insert(column, row, field)) {
//                 return column;//enemy has one way less to win
//             }
//         }
//     }//now, enemy was unable to win
//
//     int rand_col, rand_row, rand_counter=0;
//     do {
//         rand_col = 1 + (rand() % (int)(field.width-1));
//         //printf("Random = %d\n", rand_col);
//         --rand_col;
//         rand_row = top;
//         while ((field.stoneat(rand_col, rand_row) == '\000') && (rand_row <= field.height-1)) {
//             ++rand_row;
//         }
//         --rand_row;//get lowest available slot for hypothetically inserting a stone in rand_col
//         ++rand_counter;
//     } while(((field.stoneat(rand_col, top) != field.none) && (rand_counter < 100))
//     || (check_defeat_insert(rand_col, rand_row-1, field)));//do again if: occupied, <100 times or if immediate defeat
//
//     if(rand_counter < 100) {//slot is available and no immediate defeat
//         //printf("counter<100\n");
//         return rand_col;
//     } else if(rand_counter >= 100) {//after 100 tries, check manually for free slot
//         for(int man_col = 0; man_col < field.width; ++man_col) {//check if inserting possible without immediate defeat
//             if(field.stoneat(man_col, top) == field.none) {
//                 int man_row = top;
//                 while ((field.stoneat(man_col, man_row) == '\000') && (man_row <= field.height-1)) {
//                     ++man_row;
//                 }
//                 --man_row;
//                 if(!check_defeat_insert(man_col, man_row-1, field)) {
//                     //printf("counter >= 100, w/o loss\n");
//                     return man_col;
//                 }
//             }
//         }
//
//         for (int column = 0; column < field.width; ++column) {//check manually if any column available
//             if(field.stoneat(column, top) == field.none) {
//                 //printf("counter >= 100, manually\n");
//                 return column;
//             }
//         }//no free slot found, playfield should prevent allowing insertion without any free slot
//         throw "Exception: Playfield is full!";
//     } else {
//         return -1;//something really unexpected happened
//     }
// }
//
}
