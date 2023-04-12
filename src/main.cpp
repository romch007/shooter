#include <Game.hpp>
#include <Map.hpp>
#include <iostream>

int main(int argc, char** argv) {
  std::string map_filename = argc > 1 ? argv[1] : "basic.map";
  Game::start(map_filename);
  return 0;
}
