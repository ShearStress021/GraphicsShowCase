#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>




namespace triangle {

	const int MAX_FRAMES_IN_FLIGHT = 2;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	inline VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		} else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	inline void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;


	};
	struct UniformBufferObject {

		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;

	};


	const std::vector<Vertex> vertices = {
		{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}}
	};
	const std::vector<uint16_t> indices = {
			0, 1, 2, 2, 3, 0
	};



	class Triangle {
		public:
			Triangle(int w, int h, std::string name);
			void run();
			Triangle(const Triangle&) = delete;
			Triangle& operator=(const Triangle&) = delete;
			~Triangle();


		private:
			const uint32_t width{};
			const uint32_t height{};
			const std::string windowName{};

			GLFWwindow* window;

			VkInstance instance;
			VkDebugUtilsMessengerEXT debugMessenger;
			VkSurfaceKHR surface;

			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
			VkDevice device;

			VkQueue graphicsQueue;
			VkQueue presentQueue;

			VkSwapchainKHR swapChain;
			std::vector<VkImage> swapChainImages;
			VkFormat swapChainImageFormat;
			VkExtent2D swapChainExtent;
			std::vector<VkImageView> swapChainImageViews;
			std::vector<VkFramebuffer> swapChainFramebuffers;

			VkRenderPass renderPass;
			VkDescriptorSetLayout descriptorSetLayout;
			VkPipelineLayout pipelineLayout;
			VkPipeline graphicsPipeline;

			VkCommandPool commandPool;

			VkBuffer vertexBuffer;
			VkDeviceMemory vertexBufferMemory;
			VkBuffer indexBuffer;
			VkDeviceMemory indexBufferMemory;

			std::vector<VkBuffer> uniformBuffers;
			std::vector<VkDeviceMemory> uniformBuffersMemory;
			std::vector<void*> uniformBuffersMapped;

			VkDescriptorPool descriptorPool;
			std::vector<VkDescriptorSet> descriptorSets;

			std::vector<VkCommandBuffer> commandBuffers;

			std::vector<VkSemaphore> imageAvailableSemaphores;
			std::vector<VkSemaphore> renderFinishedSemaphores;
			std::vector<VkFence> inFlightFences;
			uint32_t currentFrame = 0;

			bool framebufferResized = false;


			void initWindow();
			static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
			void initVulkan();
			void mainLoop();
			void cleanupSwapChain();
			void cleanup();

			void recreateSwapChain();

			// create instance
			void createInstance();
			void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

			void setupDebugMessenger() ;
			void createSurface();
			
			void pickPhysicalDevice();
			void createLogicalDevice() ;
			void createSwapChain();
			void createImageViews();

			void createRenderPass();
			void createGraphicsPipeline();
			void createFramebuffers();
			void createCommandPool();
			void createVertexBuffer();
			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
			void createCommandBuffers();
			void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
			void createSyncObjects();

			// descriptorSets
			void createDescriptorSetLayout() ;
			void createDescriptorPool();
			void createDescriptorSets() ;

			// index buffers
			void createIndexBuffer();
			void createUniformBuffers();


			void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
			void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) ;

			void updateUniformBuffer(uint32_t currentImage) ;



			void drawFrame();
			VkShaderModule createShaderModule(const std::vector<char>& code);
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) ;
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) ;
			SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) ;
			bool isDeviceSuitable(VkPhysicalDevice device) ;
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) ;
		    std::vector<const char*> getRequiredExtensions();
		 	bool checkValidationLayerSupport();
			static std::vector<char> readFile(const std::string& filename);
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);



			


	};




}
