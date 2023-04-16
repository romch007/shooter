#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <numbers>

template <typename T>
inline float norm(const sf::Vector2<T>& vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

template <typename T>
inline void debug_vector(const sf::Vector2<T>& vector) {
  std::cout << "x " << vector.x << ", y: " << vector.y << "\n";
}

template <typename T>
inline sf::Vector2<T> rotate_by(const sf::Vector2<T>& vector, T angle) {
  return sf::Vector2<T>(
      vector.x * std::cos(angle) - vector.y * std::sin(angle),
      vector.x * std::sin(angle) + vector.y * std::cos(angle));
}

inline float degrees_to_radian(float value) {
  return value * std::numbers::pi / 180;
}

inline std::pair<int, int> parse_dimensions(const std::string& dimensions) {
  auto delimiter_pos = dimensions.find('x');
  auto width = dimensions.substr(0, delimiter_pos);
  auto heigth = dimensions.substr(delimiter_pos + 1);
  return {std::stoi(width), std::stoi(heigth)};
}
