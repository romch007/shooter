#include <Map.hpp>
#include <Utils.hpp>
#include <cmath>
#include <fstream>
#include <stdexcept>

Map Map::from_file(const std::string &filename) {
  Map map;
  std::ifstream file(filename);

  if (!file.is_open())
    throw std::runtime_error("Error reading file");

  file >> map.m_height;
  file >> map.m_width;

  map.m_buffer.reserve(map.m_height);
  for (int i = 0; i < map.m_height; i++)
    map.m_buffer.push_back(std::vector<Tile>(map.m_width));

  char c;
  for (int y = 0; y < map.m_width; y++) {
    for (int x = 0; x < map.m_height; x++) {
      file >> c;

      auto tile = c == 'O' ? Map::Tile::Empty : Map::Tile::Wall;
      map.m_buffer.at(y).at(x) = tile;
    }
  }

  return map;
}

float Map::intersection_to_wall(const sf::Vector2f &position,
                                const sf::Vector2f &direction) const {
  sf::Vector2f ray_step_size(
      std::sqrt(1 + std::pow(direction.y / direction.x, 2)),
      std::sqrt(1 + std::pow(direction.x / direction.y, 2)));
  sf::Vector2f ray;
  sf::Vector2i step;
  sf::Vector2i map_check(static_cast<int>(position.x),
                         static_cast<int>(position.y));

  if (direction.x < 0) {
    step.x = -1;
    ray.x = (position.x - map_check.x) * ray_step_size.x;
  } else {
    step.x = 1;
    ray.x = ((map_check.x + 1) - position.x) * ray_step_size.x;
  }

  if (direction.y < 0) {
    step.y = -1;
    ray.y = (position.y - map_check.y) * ray_step_size.y;
  } else {
    step.y = 1;
    ray.y = ((map_check.y + 1) - position.y) * ray_step_size.y;
  }

  bool tile_found = false;
  float max_distance = 500;
  float distance = 0;

  while (!tile_found && distance < max_distance) {
    if (ray.x < ray.y) {
      map_check.x += step.x;
      distance = ray.x;
      ray.x += ray_step_size.x;
    } else {
      map_check.y += step.y;
      distance = ray.y;
      ray.y += ray_step_size.y;
    }

    if (map_check.x >= 0 && map_check.x < m_width && map_check.y >= 0 &&
        map_check.y < m_height) {
      if (m_buffer[map_check.y][map_check.x] == Tile::Wall) {
        tile_found = true;
      }
    }
  }

  return distance;
}
