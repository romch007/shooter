#pragma once

#include <Map.hpp>
#include <SFML/System/Vector2.hpp>
#include <Utils.hpp>
#include <cmath>

class Player {
public:
  Player(const Map &map, int fov);

  void move_forward(float amount = 1);
  void move_backward(float amount = 1);
  void turn_left(float amount = 1);
  void turn_right(float amount = 1);

  float angle() const { return m_angle; }
  float fov() const { return m_fov; }
  float half_fov() const { return m_fov / 2; }
  bool is_colliding() const;

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
  const Map &m_map;
};
