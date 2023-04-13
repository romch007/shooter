#include <Game.hpp>
#include <Map.hpp>
#include <Utils.hpp>
#include <cxxopts.hpp>
#include <iostream>

int main(int argc, char **argv) {
  cxxopts::Options options("shooter", "Ray casting shooter");

  // clang-format off
  options.add_options()  
    ("f,fov", "Field of view (degrees)", cxxopts::value<int>()->default_value("70"))
    ("m,map", "Map filename", cxxopts::value<std::string>()->default_value("maps/basic.map"))
    ("d,dimensions", "Window dimensions", cxxopts::value<std::string>()->default_value("1280x720"))
    ("h,help", "Print help", cxxopts::value<bool>())
    ;
  // clang-format on
  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  Game::start(result["map"].as<std::string>(),
              degrees_to_radian(result["fov"].as<int>()), 1280, 720);
  return 0;
}
