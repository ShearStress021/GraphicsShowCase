#pragma once

#include "cube_device.hpp"
#include "cube_game_object.hpp"
#include "cube_pipeline.hpp"

// std
#include <memory>
#include <vector>

namespace cube {
class SimpleRenderSystem {
 public:
  SimpleRenderSystem(Device &device, VkRenderPass renderPass);
  ~SimpleRenderSystem();

  SimpleRenderSystem(const SimpleRenderSystem &) = delete;
  SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

  void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects);

 private:
  void createPipelineLayout();
  void createPipeline(VkRenderPass renderPass);

  Device &lveDevice;

  std::unique_ptr<Pipeline> lvePipeline;
  VkPipelineLayout pipelineLayout;
};
}  // namespace lve
