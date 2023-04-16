#include <Player.hpp>
#include <cmath>

Player::Player(const Map& map, int fov)
    : m_position(sf::Vector2f(1, 1)), m_fov(fov), m_map(map) {
}

void Player::move_forward(float amount) {
  m_position.x += move_amount * std::sin(m_angle) * amount;
  m_position.y += move_amount * std::cos(m_angle) * amount;
}

void Player::move_backward(float amount) {
  m_position.x -= move_amount * std::sin(m_angle) * amount;
  m_position.y -= move_amount * std::cos(m_angle) * amount;
}

void Player::turn_left(float amount) {
  m_angle += turn_amount * amount;
}

void Player::turn_right(float amount) {
  m_angle -= turn_amount * amount;
}

bool Player::is_colliding() const {
  int cell_x = std::floor(m_position.x);
  int cell_y = std::floor(m_position.y);

  return m_map.buffer().at(cell_y).at(cell_x) == Map::Tile::Wall;
}
