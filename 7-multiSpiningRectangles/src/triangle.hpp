#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/gtc/constants.hpp>

#include <glm/glm.hpp>
#include <vector>
#include <optional>
#include <array>
#include <string>
#include <iostream>
#include <set>
#include <limits>
#include <fstream>
#include <algorithm>
#include <string.h>

#include "gameobjects.hpp"





namespace rectangle{

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
		alignas(16) glm::vec3 color;


	};

	struct SimplePushConstantData
	{
		glm::mat2 transform{1.f};
		glm::vec2 offset;
		alignas(16) glm::vec3 color;
	};


	const std::vector<Vertex> vertices = {
		{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}}
	};


	class Rectangle{
		public:
			Rectangle(int w, int h, std::string name);
			void run();
			Rectangle(const Rectangle&) = delete;
			Rectangle& operator=(const Rectangle&) = delete;
			~Rectangle();


		private:
			const uint32_t width{};
			const uint32_t height{};
			const std::string windowName{};

			GLFWwindow* window{};

			VkInstance instance{VK_NULL_HANDLE};
			VkDebugUtilsMessengerEXT debugMessenger{VK_NULL_HANDLE};
			VkSurfaceKHR surface{VK_NULL_HANDLE};

			VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
			VkDevice device{VK_NULL_HANDLE};

			VkQueue graphicsQueue{VK_NULL_HANDLE};
			VkQueue presentQueue{VK_NULL_HANDLE};

			VkSwapchainKHR swapChain{VK_NULL_HANDLE};
			std::vector<VkImage> swapChainImages;
			VkFormat swapChainImageFormat;
			VkExtent2D swapChainExtent;
			std::vector<VkImageView> swapChainImageViews;
			std::vector<VkFramebuffer> swapChainFramebuffers;

			VkRenderPass renderPass;
			VkPipelineLayout pipelineLayout;
			VkPipeline graphicsPipeline;

			VkCommandPool commandPool;

			VkBuffer vertexBuffer;
			VkDeviceMemory vertexBufferMemory;

			std::vector<VkCommandBuffer> commandBuffers;

			std::vector<VkSemaphore> imageAvailableSemaphores;
			std::vector<VkSemaphore> renderFinishedSemaphores;
			std::vector<VkFence> inFlightFences;
			uint32_t currentFrame = 0;

		    bool framebufferResized = false;


			std::vector<GameObject> gameobjects;

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



			void loadGameObjects();



			


	};




}
