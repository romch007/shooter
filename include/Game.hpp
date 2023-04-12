#pragma once

#include <Map.hpp>
#include <Player.hpp>
#include <SFML/Graphics.hpp>

class Game {
public:
  static constexpr int heigth = 720;
  static constexpr int width = 1280;
  static constexpr int move_step = 10;
  static constexpr float cell_size = 500.0;

  static const sf::Color sky_color;
  static const sf::Color wall_color;
  static const sf::Color floor_color;

  static void start(const std::string &map_filename);

private:
  Game(const std::string &map_filename);

  void internal_start();
  void draw_2d_player();
  void draw_2d_map();
  void draw_screen();
  void draw_screen_column(int x, sf::Image &screen,
                          const sf::Vector2f &player_position,
                          const sf::Vector2f &player_direction);

  sf::RenderWindow m_window;
  Player m_player;
  Map m_map;
};
