#include <Player.hpp>
#include <cmath>

void Player::move_forward() {
  m_position.x += move_amount * std::sin(m_angle);
  m_position.y += move_amount * std::cos(m_angle);
}

void Player::move_backward() {
  m_position.x -= move_amount * std::sin(m_angle);
  m_position.y -= move_amount * std::cos(m_angle);
}

void Player::turn_left() {
  m_angle += turn_amount;
}

void Player::turn_right() {
  m_angle -= turn_amount;
}
