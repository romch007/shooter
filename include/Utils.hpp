#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

template <typename T> inline float norm(const sf::Vector2<T> &vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

template <typename T> inline void debug_vector(const sf::Vector2<T> &vector) {
  std::cout << "x " << vector.x << ", y: " << vector.y << "\n";
}

template <typename T>
inline sf::Vector2<T> rotate_by(const sf::Vector2<T> &vector, T angle) {
  return sf::Vector2<T>(vector.x * std::cos(angle) - vector.y * std::sin(angle),
                        vector.x * std::sin(angle) +
                            vector.y * std::cos(angle));
}
