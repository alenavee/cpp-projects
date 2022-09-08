#include "sudoku-solver.h"
#include <set>

std::set<int> get_block_set(const std::vector<std::vector<int>>& field,
                        int block_row, int block_col) {
  std::set<int> block;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      block.insert(field[(block_row / 3) * 3 + i][(block_col / 3) * 3 + j]);
    }
  }
  return block;
}

std::set<int> get_col(const std::vector<std::vector<int>>& field, int pos) {
  std::set<int> col;
  for (int i = 0; i < 9; ++i) {
    col.insert(field[i][pos]);
  }
  return col;
}

std::set<int> get_row(const std::vector<std::vector<int>>& field, int pos) {
  std::set<int> row;
  for (int i = 0; i < 9; ++i) {
    row.insert(field[pos][i]);
  }
  return row;
}

std::set<int> get_possible_values(const std::vector<std::vector<int>>& field,
                                  int row, int col) {

  std::set<int> rows = get_row(field, row);
  std::set<int> cols = get_col(field, col);
  std::set<int> block = get_block_set(field, row, col);

  std::set<int> possible_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (auto element : rows) {
    auto pos_v = rows.find(element);
    possible_values.erase(*pos_v);
  }

  for (auto element : cols) {
    auto pos_v = cols.find(element);
    possible_values.erase(*pos_v);
  }

  for (auto element : block) {
    auto pos_v = block.find(element);
    possible_values.erase(*pos_v);
  }
  return possible_values;
}

std::pair<int, int>
get_empty_position(const std::vector<std::vector<int>>& field) {

  std::set<int> possible_values;
  std::pair<int, int> best_pos =
      std::make_pair(-1, -1); // no empty positions return -1
  std::set<int> best_values;
  int min_values = 9;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (field[i][j] == 0) {
        possible_values = get_possible_values(field, i, j);
        // optimal empty position with the least possible values
        if (possible_values.size() < min_values) {
          min_values = possible_values.size();
          best_pos = std::make_pair(i, j);
        }
      }
    }
  }

  return best_pos;
}

int counter(const std::vector<std::vector<int>>& field,
            std::vector<std::vector<int>>& solution) {
  int count = 0;

  // copy initial field to make changes in it
  std::vector<std::vector<int>> field_change = field;

  std::pair<int, int> empty_position = get_empty_position(field);

  // no empty position marked as -1
  if (empty_position.first == -1) {
    solution = field_change;
    return 1;
  }

  std::set<int> possible_values = get_possible_values(
      field_change, empty_position.first, empty_position.second);

  // placing possible values in empty positions
  for (auto value : possible_values) {
    field_change[empty_position.first][empty_position.second] = value;
    count += counter(field_change, solution);
  }

  return count;
}

std::pair<size_t, std::vector<std::vector<int>>>
sudoku_solve(const std::vector<std::vector<int>>& field) {
  int count = 0;
  std::vector<std::vector<int>> solution = field;
  count = counter(field, solution);
  return std::make_pair(count, solution);
}

