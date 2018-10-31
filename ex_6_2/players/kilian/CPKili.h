//
// Created by kilia on 23.10.2018.
//


#ifndef INC_3_3_CPKILI_H_
#define INC_3_3_CPKILI_H_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <ios>
#include <sstream>
#include <fstream>
#include <random>
#include <cstdlib>

using namespace std;

template<typename A>
class CPKili{
public:
    char playerNr;
    char oponentNr;
    CPKili(int playerID){
        playerNr=playerID;
        if(playerID==1){oponentNr=2;}
        else{oponentNr=1;}
    }
    int play(const A &field){
        for(int i=0;i<=6; i++){
            if(checker(i,playerNr,field)){
                return i;
            }
        }

        for(int i=0;i<=6; i++){
            if(checker(i,oponentNr,field)){
                return i;
            }
        }


        int random_Nr;
        random_Nr = rand()%7;

        while(1){
            if(freeslot(random_Nr,field)){
                return random_Nr;
            }
            random_Nr = rand()%7;
        }

    }

    bool checker(int x, char player, A field){
        int y;
        int j=6-1;
        while(field.stoneat(x,j)!=0 && j>=0){
            j--;
        }
        if(j<0){
            return false;
        }
        else if(field.stoneat(x,j)==0){
            y=j;
        }


        int vertical = 1;//(|)
        int horizontal = 1;//(-)
        int diagonal1 = 1;//(\)
        int diagonal2 = 1;//(/)
        int i;//vertical
        int ii;//horizontal
        //check for vertical(|)
        for(i = y +1;field.stoneat(x,i) == player && i < 6;i++,vertical++);//Check down
        for(i = y -1;field.stoneat(x,i) == player && i >= 0;i--,vertical++);//Check up
        if(vertical >= 4)return true;
        //check for horizontal(-)
        for(ii = x -1;field.stoneat(ii,y) == player && ii >= 0;ii--,horizontal++);//Check left
        for(ii = x +1;field.stoneat(ii,y) == player && ii < 7 ;ii++,horizontal++);//Check right
        if(horizontal >= 4) return true;
        //check for diagonal 1 (\)
        for(i = y -1, ii= x -1;field.stoneat(ii,i) == player && i>=0 && ii >=0; diagonal1 ++, i --, ii --);//up and left
        for(i = y +1, ii = x+1;field.stoneat(ii,i) == player && i<6 && ii <7;diagonal1 ++, i ++, ii ++);//down and right
        if(diagonal1 >= 4) return true;
        //check for diagonal 2(/)
        for(i = y -1, ii= x +1;field.stoneat(ii,i) == player && i>=0 && ii <7; diagonal2 ++, i --, ii ++);//up and right
        for(i = y +1, ii= x -1;field.stoneat(ii,i) == player && i<6 && ii >=0; diagonal2 ++, i ++, ii --);//up and left
        if(diagonal2 >= 4) return true;
        return false;
    }
    bool freeslot(int x, A field){
        int j=6-1;
        while(field.stoneat(x,j)!=0 && j>=0){
            j--;
        }
        if(j<0){
            return false;
        }
        else if(field.stoneat(x,j)==0){
            return true;
        }
    }

};


#endif //INC_3_3_CPKILI_H_
