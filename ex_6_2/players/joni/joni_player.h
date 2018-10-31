#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <iostream>
#include <ctime>
#include "joni_playfield_traits.h"

namespace joni {

template <typename F, typename P = playfield_traits<F>>
class aiplayer {
  const int player_id;
  const int opponent_id;
  const int win = 4;

public:
  using playfieldtraits = P;
  aiplayer(int player_id)
      : player_id(player_id), opponent_id(player_id == 1 ? 2 : 1) {
    std::srand(std::time(NULL));
  }

  int getrandomcolumn(const F &field) {
    int column = std::rand() % 7;
    while (playfieldtraits::columnfull(field, column)) {
      column = std::rand() % 7;
    }

    return column;
  }

  void insertteststone(std::vector<std::vector<char>> &rep, int column, int player) {
    int row = F::height - 1;
    while (rep[column][row] != F::none) {
      row--;
    }

    rep[column][row] = player;
  }

  int findbestcolumn(const F &field) {
    // Tests if oppenent coudl win in one move and prevents that
    for (int i = 0; i < F::width; i++) {
      std::vector<std::vector<char>> rep = playfieldtraits::copyrep(field);
      if (!playfieldtraits::columnfull(field, i)) {
        insertteststone(rep, i, opponent_id);
        if (haswon(rep, opponent_id)) {
          return i;
        }
      }
    }
    // Tests if player can win in one move an chooses winning column
    for (int i = 0; i < F::width; i++) {
      std::vector<std::vector<char>> rep = playfieldtraits::copyrep(field);
      if (!playfieldtraits::columnfull(field, i)) {
        insertteststone(rep, i, player_id);
        if (haswon(rep, player_id)) {
          return i;
        }
      }
    }

    // If both is not the case, choose random column
    return getrandomcolumn(field);
  }

  bool haswonhorizontal(const std::vector<std::vector<char>> rep, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (rep[column + i][row] != player) {
        return false;
      }
    }
    return true;
  }

  bool haswonvertical(const std::vector<std::vector<char>> rep, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (rep[column][row - i] != player) {
        return false;
      }
    }
    return true;
  }

  bool haswondiagonalslash(const std::vector<std::vector<char>> rep, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (rep[column + i][row - i] != player) {
        return false;
      }
    }
    return true;
  }

  bool haswondiagonalbackslash(const std::vector<std::vector<char>> rep, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (rep[column - i][row - i] != player) {
        return false;
      }
    }
    return true;
  }

  bool haswon(const std::vector<std::vector<char>> rep, int player) {
    for (int i = F::height - 1; i >= 0; i--) {
      for (int j = 0; j < F::width; j++) {

        if (j + (win-1) < F::width && haswonhorizontal(rep, j, i, player)) {
          return true;
        }

        if (i - (win-1) >= 0 && haswonvertical(rep, j, i, player)) {
          return true;
        }

        if (j + (win-1) < F::width && i - (win-1) >= 0 &&
            haswondiagonalslash(rep, j, i, player)) {
          return true;
        }

        if (i + (win-1) >= 0 && j - (win-1) >= 0 &&
            haswondiagonalbackslash(rep, j, i, player)) {
          return true;
        }
      }
    }
    return false;
  }

  // returns the column where the player decides to throw in his stone
  // F is the playfield which may be any playfield implementing
  // the stoneat method, if you expect a different class because
  // you need methods to verify whether the opponent can win,
  // copy the field into the class that you expect.
  int play(F &field) { return findbestcolumn(field); }
};

}

#endif // AIPLAYER_H
