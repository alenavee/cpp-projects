#include "players/human-player.h"

#include <algorithm>
#include <cassert>
#include <string>

std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl
                << my_field << std::endl
                << "Enemy's field" << std::endl
                << enemy_field << std::endl
                << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;

  std::vector<std::string> field_coordinates;
  int number_coordinate;
  int letter_coordinate;

  for (int i = 1; i <= field_t::FIELD_SIZE; ++i) {
    for (auto j : letters) {
      field_coordinates.push_back(std::to_string(i) + j);
    }
  }

  std::string given_coordinates;
  bool input = false;
  while (!input) {
    std::getline(input_stream, given_coordinates);
    if (std::find(field_coordinates.begin(), field_coordinates.end(), given_coordinates) != field_coordinates.end()) {
      input = true;
    } else {
      output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
    }
  }

  if (given_coordinates.size() == 2) {
    std::string number = given_coordinates.substr(0, 1);
    number_coordinate = std::stoi(number) - 1;
  } else {
    number_coordinate = field_t::FIELD_SIZE - 1;
  }

  auto letter_it = std::find(letters.begin(), letters.end(),
                             given_coordinates.substr(given_coordinates.size() - 1, given_coordinates.size()));
  letter_coordinate = distance(letters.begin(), letter_it);

  return std::pair<int, int>(number_coordinate, letter_coordinate);
}

void human_player_t::on_incorrect_move(int x, int y) {
  assert(false);
}
void human_player_t::on_duplicate_move(int x, int y) {
  output_stream << x + 1 << letters[y] << " "
                << "DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int x, int y) {
  output_stream << x + 1 << letters[y] << " "
                << "MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int x, int y) {
  output_stream << x + 1 << letters[y] << " "
                << "HIT! Your next move!" << std::endl;
}

void human_player_t::on_kill(int x, int y) {
  output_stream << x + 1 << letters[y] << " "
                << "KILL! Your next move!" << std::endl;
}

void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}

void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}
