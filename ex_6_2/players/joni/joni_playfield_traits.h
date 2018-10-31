#ifndef PLAYFIELD_TRAITS_H
#define PLAYFIELD_TRAITS_H

#include <iostream>
#include <vector>

namespace joni {

template <typename F>
struct playfield_traits {

  static const int win = 4;

  static std::vector<std::vector<char>> copyrep(const F &field) {
    std::vector<std::vector<char>> rep(F::width, std::vector<char>(F::height));
    for (int i = 0; i < F::width; i++) {
      for (int j = 0; j < F::height; j++) {
        rep[i][j] = field.stoneat(i,j);
      }
    }
    return rep;
  }

  static bool columnfull(const F &field, int column) {
    return field.stoneat(column, 0) != F::none;
  }

  static bool haswonhorizontal(const F &field, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (field.stoneat(column + i, row) != player) {
        return false;
      }
    }
    return true;
  }

  static bool haswonvertical(const F &field, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (field.stoneat(column, row - i) != player) {
        return false;
      }
    }
    return true;
  }

  static bool haswondiagonalslash(const F &field, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (field.stoneat(column + i, row - i) != player) {
        return false;
      }
    }
    return true;
  }

  static bool haswondiagonalbackslash(const F &field, int column, int row, int player) {
    for (int i = 0; i < win; i++) {
      if (field.stoneat(column - i, row - i) != player) {
        return false;
      }
    }
    return true;
  }

  static bool haswon(const F &field, int player) {
    for (int i = F::height - 1; i >= 0; i--) {
      for (int j = 0; j < F::width; j++) {

        if (j + (win-1) <= F::width && haswonhorizontal(field, j, i, player)) {
          return true;
        }

        if (i - (win-1) >= 0 && haswonvertical(field, j, i, player)) {
          return true;
        }

        if (j + (win-1) <= F::width && i - (win-1) >= 0 &&
            haswondiagonalslash(field, j, i, player)) {
          return true;
        }

        if (i - (win-1) >= 0 && j - (win-1) >= 0 && haswondiagonalbackslash(field, j, i, player)) {
          return true;
        }
      }
    }
    return false;
  }
};

}

#endif // PLAYFIELD_TRAITS_H
