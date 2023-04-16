#include <Game.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Utils.hpp>
#include <iostream>
#include <stdexcept>

const sf::Color Game::sky_color = sf::Color(135, 206, 235);
const sf::Color Game::wall_color = sf::Color::Black;
const sf::Color Game::floor_color = sf::Color(150, 85, 0);

void Game::start(const std::string& map_filename, int fov, int width,
                 int heigth) {
  Game(map_filename, fov, width, heigth).internal_start();
}

Game::Game(const std::string& map_filename, int fov, int width, int heigth)
    : m_window(sf::VideoMode(width, heigth), "Shooter"),
      m_player(m_map, fov),
      m_map(Map::from_file(map_filename)),
      m_heigth(heigth),
      m_width(width) {
  m_window.setVerticalSyncEnabled(true);
  if (!m_wall_image.loadFromFile("assets/wall.png"))
    throw std::runtime_error("cannot open texture file");
}

void Game::internal_start() {
  while (m_window.isOpen()) {
    sf::Event event;

    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) m_window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      m_player.move_forward();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      m_player.move_backward();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      m_player.turn_left();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      m_player.turn_right();
    }

    if (sf::Joystick::isConnected(0)) {
      auto movement = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
      std::cout << movement << "\n";
      m_player.move_forward(movement / -100.0f);
      auto direction = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
      m_player.turn_right(direction / 100.0f);
    }

    m_window.clear(sf::Color::Black);

    auto colliding = m_player.is_colliding();

    if (colliding) std::cout << "Collision!\n";

    draw_screen();

    m_window.display();
  }
}

void Game::draw_screen() {
  auto player_position = m_player.position();
  auto player_direction = m_player.direction();

  sf::Image screen;
  screen.create(m_width, m_heigth, sf::Color::Black);

  for (int x = 0; x < m_width; x++) {
    draw_screen_column(x, screen, player_position, player_direction);
  }

  sf::Texture screen_texture;
  screen_texture.loadFromImage(screen);

  sf::Sprite screen_sprite(screen_texture);

  m_window.draw(screen_sprite);
}

void Game::draw_screen_column(int x, sf::Image& screen,
                              const sf::Vector2f& player_position,
                              const sf::Vector2f& player_direction) {
  auto angle_shift = -m_width / 2 + x;
  float current_angle = (m_player.fov() / m_width) * angle_shift;

  auto current_direction = rotate_by(player_direction, current_angle);
  auto intersect_distance =
      m_map.intersection_to_wall(player_position, current_direction) *
      std::cos(current_angle);

  float wall_height = (m_heigth / intersect_distance) / 2;

  for (int y = 0; y < m_heigth / 2; y++) {
    if (y < (static_cast<float>(m_heigth) / 2) - wall_height) {
      screen.setPixel(x, y, sky_color);
      screen.setPixel(x, (m_heigth - 1) - y, floor_color);
    } else {
      screen.setPixel(x, y, wall_color);
      screen.setPixel(x, (m_heigth - 1) - y, wall_color);
    }
  }
}
