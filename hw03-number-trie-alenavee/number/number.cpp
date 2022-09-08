#include "number.h"

//конструктор копирования

// number_t::number_t(number_t &copy) {
//  number = copy.number;
//}

//конструктор копирования от числа
number_t::number_t(std::int64_t a) {
  number = a;
}

//оператор присвоения
number_t &number_t::operator=(std::int64_t a) {
  number = a;
  return *this;
}

//каст числу
number_t::operator int64_t() const {
  return number;
}

//каст bool
number_t::operator bool() const {
  return number;
}

//каст std string
number_t::operator std::string() const {
  return std::to_string(number);
}

//Бинарные арифметические и битовые операторы
//+, -, *, /, %, &, |, ^, <<, >>
number_t operator+(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number += num2.number;
  return new_num;
}

number_t operator-(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number -= num2.number;
  return new_num;
}

number_t &number_t::operator-=(const number_t &num) {
  number -= num.number;
  return *this;
}

number_t &number_t::operator+=(const number_t &num) {
  number += num.number;
  return *this;
}

number_t operator*(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number *= num2.number;
  return new_num;
}
number_t operator/(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number /= num2.number;
  return new_num;
}
number_t operator%(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number %= num2.number;
  return new_num;
}

number_t &number_t::operator*=(const number_t &num) {
  number *= num.number;
  return *this;
}
number_t &number_t::operator/=(const number_t &num) {
  number /= num.number;
  return *this;
}
number_t &number_t::operator%=(const number_t &num) {
  number %= num.number;
  return *this;
}

number_t operator^(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number ^= num2.number;
  return new_num;
}
number_t operator&(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number &= num2.number;
  return new_num;
}
number_t operator|(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number |= num2.number;
  return new_num;
}

number_t &number_t::operator^=(const number_t &num) {
  number ^= num.number;
  return *this;
}
number_t &number_t::operator&=(const number_t &num) {
  number &= num.number;
  return *this;
}
number_t &number_t::operator|=(const number_t &num) {
  number |= num.number;
  return *this;
}

number_t operator>>(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number >>= num2.number;
  return new_num;
}
number_t operator<<(const number_t &num1, const number_t &num2) {
  number_t new_num = num1;
  new_num.number <<= num2.number;
  return new_num;
}
number_t &number_t::operator>>=(const number_t &num) {
  number >>= num.number;
  return *this;
}
number_t &number_t::operator<<=(const number_t &num) {
  number <<= num.number;
  return *this;
}

//Унарные операторы
number_t number_t::operator-() const {
  return number_t(-number);
}

number_t number_t::operator+() const {
  return number_t(number);
}

bool number_t::operator!() const {
  return (number == 0);
}

number_t number_t::operator~() const {
  return number_t(~number);
}

//Операторы инкремента и декремента

//префикс
number_t &number_t::operator++() {
  ++number;
  return *this;
}
number_t &number_t::operator--() {
  --number;
  return *this;
}

//постфикс
number_t number_t::operator++(int) {
  number_t temp(number);
  ++(*this);
  return temp;
}

number_t number_t::operator--(int) {
  number_t temp(number);
  --(*this);
  return temp;
}

//операторы сравнения

bool operator==(const number_t &num1, const number_t &num2) {
  return (num1.number == num2.number);
}

bool operator!=(const number_t &num1, const number_t &num2) {
  return !(num1 == num2);
}

bool operator>(const number_t &num1, const number_t &num2) {
  return num1.number > num2.number;
}
bool operator>=(const number_t &num1, const number_t &num2) {
  return num1.number >= num2.number;
}

bool operator<(const number_t &num1, const number_t &num2) {
  return num1.number < num2.number;
}
bool operator<=(const number_t &num1, const number_t &num2) {
  return num1.number <= num2.number;
}

//Операторы вывода в поток и ввода из потока

std::ostream &operator<<(std::ostream &out, const number_t &number) {
  out << number.number;
  return out;
}
std::istream &operator>>(std::istream &in, number_t &number) {
  in >> number.number;
  return in;
}
