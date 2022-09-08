#include "field-checker.h"
#include <set>

std::set<int> get_block(const std::vector<std::vector<int>>& field,
                        int block_row, int block_col) {
  std::set<int> block;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      block.insert(field[(block_row / 3) * 3 + i][(block_col / 3) * 3 + j]);
    }
  }
  return block;
}

bool check_field(const std::vector<std::vector<int>>& init_field,
                 const std::vector<std::vector<int>>& solution) {
  // compare init field
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (init_field[i][j] != 0 && init_field[i][j] != solution[i][j]) {
        return false;
      }
    }
  }

  // check columns
  for (int i = 0; i < 9; ++i) {
    std::set<int> col;
    col.insert(begin(solution[i]), end(solution[i]));
    col.erase(0);
    if (col.size() != 9) {
      return false;
    }
  }

  // check rows
  for (int i = 0; i < 9; ++i) {
    std::set<int> row;
    for (int j = 0; j < 9; ++j) {
      row.insert(solution[i][j]);
    }
    row.erase(0);
    if (row.size() != 9) {
      return false;
    }
  }

  // check block
  for (int i = 0; i < 9; i += 3) {
    for (int j = 0; j < 9; j += 3) {
      std::set<int> block = get_block(solution, i, j);
      block.erase(0);
      if (block.size() != 9) {
        return false;
      }
    }
  }
  return true;
}
