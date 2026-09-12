#pragma once

#include "cube_device.hpp"
#include "cube_game_object.hpp"
#include "cube_renderer.hpp"
#include "cube_window.hpp"

// std
#include <memory>
#include <vector>

namespace cube {
class FirstApp {
 public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  FirstApp();
  ~FirstApp();

  FirstApp(const FirstApp &) = delete;
  FirstApp &operator=(const FirstApp &) = delete;

  void run();

 private:
  void loadGameObjects();

  Window lveWindow{WIDTH, HEIGHT, "Vulkan Tutorial"};
  Device lveDevice{lveWindow};
  Renderer lveRenderer{lveWindow, lveDevice};

  std::vector<GameObject> gameObjects;
};
}  // namespace lve
