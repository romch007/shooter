#pragma once

#include <SFML/System/Vector2.hpp>
#include <Utils.hpp>
#include <cmath>

class Player {
public:
  Player() = default;

  void move_forward();
  void move_backward();
  void turn_left();
  void turn_right();

  float angle() const { return m_angle; }
  float fov() const { return m_fov; }
  float half_fov() const { return m_fov / 2; }

  const sf::Vector2f &position() const { return m_position; }

  sf::Vector2f direction() const {
    auto original = sf::Vector2f(std::sin(m_angle), std::cos(m_angle));
    return original / norm(original);
  }

private:
  static constexpr float move_amount = 0.02;
  static constexpr float turn_amount = 0.03;

  sf::Vector2f m_position;
  float m_angle{0.0};
  float m_fov{1};
};
