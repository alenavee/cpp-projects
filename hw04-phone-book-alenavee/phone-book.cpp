#include "phone-book.h"

bool phone_book_t::create_user(const std::string &number, const std::string &name) {
  if (user_number.find(number) != user_number.end()) {
    return false;
  }
  user_info_t new_user = user_info_t({{number, name}, 0});
  user_number.insert({number, new_user});
  users_sorted_name.insert(new_user);

  for (int i = 0; i <= number.size(); ++i) {
    auto number_prefix_it = users_sorted_number.find(number.substr(0, i));
    if (number_prefix_it != users_sorted_number.end()) {
      number_prefix_it->second.insert(new_user);
    } else {
      users_sorted_number.insert({number.substr(0, i), {new_user}});
    }
  }
  return true;
}

bool phone_book_t::add_call(const call_t &call) {
  if (user_number.find(call.number) == user_number.end()) {
    return false;
  }
  user_info_t user_tmp;
  auto it_number = user_number.find(call.number);

  user_tmp = it_number->second;

  users_sorted_name.erase(user_tmp);
  for (int i = 0; i <= call.number.size(); ++i) {
    auto number_prefix_it = users_sorted_number.find(call.number.substr(0, i));
    number_prefix_it->second.erase(user_tmp);
  }

  user_tmp.total_call_duration_s += call.duration_s;
  it_number->second.total_call_duration_s += call.duration_s;

  users_sorted_name.insert(user_tmp);
  for (int i = 0; i <= call.number.size(); ++i) {
    auto number_prefix_it = users_sorted_number.find(call.number.substr(0, i));
    number_prefix_it->second.insert(user_tmp);
  }

  call_history.push_back(call);

  return true;
}

std::vector<call_t> phone_book_t::get_calls(size_t start_pos, size_t count) const {

  return std::vector<call_t>(call_history.begin() + std::min(call_history.size(), start_pos),
                             call_history.begin() + std::min(call_history.size(), start_pos + count));
}

std::vector<user_info_t> phone_book_t::search_users_by_name(const std::string &name_prefix, size_t count) const {

  user_info_t some_user;
  some_user.user.name = name_prefix;
  some_user.total_call_duration_s = std::numeric_limits<double>::max();
  some_user.user.number = "";

  auto itlow = users_sorted_name.lower_bound(some_user);
  auto iterator_end = itlow;
  int start_count = 0;

  while (iterator_end != users_sorted_name.end() && start_count != count &&
         name_prefix.end() ==
             std::mismatch(name_prefix.begin(), name_prefix.end(), iterator_end->user.name.begin()).first) {

    ++iterator_end;
    ++start_count;
  }

  return std::vector<user_info_t>(itlow, iterator_end);
}

std::vector<user_info_t> phone_book_t::search_users_by_number(const std::string &number_prefix, size_t count) const {

  auto prefix_it = users_sorted_number.find(number_prefix);
  if (prefix_it == users_sorted_number.end()) {
    return std::vector<user_info_t>();
  }

  auto itlow = prefix_it->second.begin();
  auto iterator_end = itlow;
  int start_count = 0;

  while (iterator_end != prefix_it->second.end() && start_count != count) {
    ++iterator_end;
    ++start_count;
  }
  return std::vector<user_info_t>(itlow, iterator_end);
}

void phone_book_t::clear() {
  users_sorted_name = {};
  user_number = {};
  users_sorted_number = {};
  call_history = {};
}

size_t phone_book_t::size() const {
  return user_number.size();
}

bool phone_book_t::empty() const {
  return user_number.empty();
}
