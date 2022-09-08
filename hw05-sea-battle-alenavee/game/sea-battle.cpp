#include "game/sea-battle.h"
#include "sea-battle.h"
#include <algorithm>

bool sea_battle_t::is_correct_cell(int x, int y) {
  return x >= 0 && x < field_t::FIELD_SIZE && y >= 0 && y < field_t::FIELD_SIZE;
}
bool sea_battle_t::is_ship_killed(field_t &field, int x, int y) {
  for (const auto &i : field_t::DIRECTIONS) {
    int curr_x = x;
    int curr_y = y;
    while (is_correct_cell(curr_x, curr_y)) {
      if (field[curr_x][curr_y] == field_t::SHIP_CELL) {
        return false;
      } else if (field[curr_x][curr_y] == field_t::MISS_CELL || field[curr_x][curr_y] == field_t::EMPTY_CELL) {
        break;
      }
      curr_x += i.first;
      curr_y += i.second;
    }
  }
  return true;
}
bool sea_battle_t::is_no_ship_left(field_t &field) {
  for (int row = 0; row < field_t::FIELD_SIZE; ++row) {
    if (field[row].find(field_t::SHIP_CELL) != std::string::npos) {
      return false;
    }
  }
  return true;
}

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
  return turn == FIRST_PLAYER ? "First" : "Second";
}
sea_battle_t::sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1,
                           std::shared_ptr<player_interface_t> player2, field_t field2)
    : player1(player1), field1(field1), player2(player2), field2(field2) {}

void sea_battle_t::play() {
  while (true) {
    std::pair<int, int> coordinates;
    int x;
    int y;

    if (current_turn == turn_t::FIRST_PLAYER) {
      field_t second_player_field = field2;
      for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
        std::replace(second_player_field[i].begin(), second_player_field[i].end(), field_t::SHIP_CELL,
                     field_t::EMPTY_CELL);
      }
      coordinates = player1->make_move(field1, second_player_field);

    } else {
      field_t first_player_field = field1;
      for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
        std::replace(first_player_field[i].begin(), first_player_field[i].end(), field_t::SHIP_CELL,
                     field_t::EMPTY_CELL);
      }
      coordinates = player2->make_move(field2, first_player_field);
    }
    x = coordinates.first;
    y = coordinates.second;

    if (!is_correct_cell(x, y)) {
      if (current_turn == turn_t::FIRST_PLAYER) {
        player1->on_incorrect_move(x, y);
        continue;
      } else {
        player2->on_incorrect_move(x, y);
        continue;
      }
    }

    if (current_turn == turn_t::FIRST_PLAYER) {
      if (field2[x][y] == field_t::HIT_CELL || field2[x][y] == field_t::MISS_CELL) {
        player1->on_duplicate_move(x, y);
        continue;
      }
    } else {
      if (field1[x][y] == field_t::HIT_CELL || field1[x][y] == field_t::MISS_CELL) {
        player2->on_duplicate_move(x, y);
        continue;
      }
    }

    if (current_turn == turn_t::FIRST_PLAYER) {
      if (field2[x][y] == field_t::EMPTY_CELL) {
        field2[x][y] = field_t::MISS_CELL;
        player1->on_miss(x, y);
        current_turn = change_turn(current_turn);
        continue;
      }
    } else {
      if (field1[x][y] == field_t::EMPTY_CELL) {
        field1[x][y] = field_t::MISS_CELL;
        player2->on_miss(x, y);
        current_turn = change_turn(current_turn);
        continue;
      }
    }

    if (current_turn == turn_t::FIRST_PLAYER) {
      if (field2[x][y] == field_t::SHIP_CELL) {
        field2[x][y] = field_t::HIT_CELL;
        if (is_ship_killed(field2, x, y)) {
          player1->on_kill(x, y);
          if (is_no_ship_left(field2)) {
            player1->on_win();
            player2->on_lose();
            break;
          }
        } else {
          player1->on_hit(x, y);
        }
      }
    } else {
      if (field1[x][y] == field_t::SHIP_CELL) {
        field1[x][y] = field_t::HIT_CELL;
        if (is_ship_killed(field1, x, y)) {
          player2->on_kill(x, y);
          if (is_no_ship_left(field1)) {
            player2->on_win();
            player1->on_lose();
            break;
          }
        } else {
          player2->on_hit(x, y);
          continue;
        }
      }
    }
  }
}