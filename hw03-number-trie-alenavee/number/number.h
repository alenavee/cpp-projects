#pragma once

#include <cstdint>
#include <iostream>

class number_t {
private:
  std::int64_t number = 0;

public:
  //конструкторы
  number_t() = default;
  number_t(const number_t &copy) = default;
  number_t(int64_t);

  //оператор присвоения
  number_t &operator=(int64_t);

  //каст
  explicit operator int64_t() const;
  explicit operator bool() const;
  explicit operator std::string() const;

  //Бинарные арифметические и битовые операторы
  friend number_t operator+(const number_t &num1, const number_t &num2);
  friend number_t operator-(const number_t &num1, const number_t &num2);

  number_t &operator+=(const number_t &num);
  number_t &operator-=(const number_t &num);

  friend number_t operator*(const number_t &num1, const number_t &num2);
  friend number_t operator/(const number_t &num1, const number_t &num2);
  friend number_t operator%(const number_t &num1, const number_t &num2);

  number_t &operator*=(const number_t &num);
  number_t &operator/=(const number_t &num);
  number_t &operator%=(const number_t &num);

  friend number_t operator^(const number_t &num1, const number_t &num2);
  friend number_t operator&(const number_t &num1, const number_t &num2);
  friend number_t operator|(const number_t &num1, const number_t &num2);

  number_t &operator^=(const number_t &num);
  number_t &operator&=(const number_t &num);
  number_t &operator|=(const number_t &num);

  friend number_t operator>>(const number_t &num1, const number_t &num2);
  friend number_t operator<<(const number_t &num1, const number_t &num2);

  number_t &operator>>=(const number_t &num);
  number_t &operator<<=(const number_t &num);

  //Унарные операторы
  number_t operator-() const;
  number_t operator+() const;
  bool operator!() const;
  number_t operator~() const;

  //Операторы инкремента и декремента
  number_t &operator++();
  number_t &operator--();

  number_t operator++(int);
  number_t operator--(int);

  //операторы сравнения
  friend bool operator==(const number_t &num1, const number_t &num2);
  friend bool operator!=(const number_t &num1, const number_t &num2);

  friend bool operator>(const number_t &num1, const number_t &num2);
  friend bool operator>=(const number_t &num1, const number_t &num2);

  friend bool operator<(const number_t &num1, const number_t &num2);
  friend bool operator<=(const number_t &num1, const number_t &num2);

  //Операторы вывода в поток и ввода из потока

  friend std::ostream &operator<<(std::ostream &out, const number_t &number);
  friend std::istream &operator>>(std::istream &in, number_t &number);
};
