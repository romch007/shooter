#pragma once

#include <SFML/System/Vector2.hpp>
#include <optional>
#include <string>
#include <vector>

class Map {
 public:
  enum class Tile {
    Wall,
    Empty
  };

  static Map from_file(const std::string& file);

  const std::vector<std::vector<Tile>>& buffer() const {
    return m_buffer;
  }

  float intersection_to_wall(const sf::Vector2f& position,
                             const sf::Vector2f& direction) const;

  int width() const {
    return m_width;
  }
  int height() const {
    return m_height;
  }

  static constexpr float cell_size = 100.0;

 private:
  Map() = default;

  std::vector<std::vector<Tile>> m_buffer;
  int m_width;
  int m_height;
};
