#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <optional>
#include <vector>
#include <string.h>
#include <iostream>
#include <set>
#include <fstream>
#include <limits>
#include <algorithm>


namespace triangle 
{

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



 	inline VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
	{
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

			GLFWwindow* window{};

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
			VkPipelineLayout pipelineLayout;
			VkPipeline graphicsPipeline;

			VkCommandPool commandPool;
			std::vector<VkCommandBuffer> commandBuffers;

			std::vector<VkSemaphore> imageAvailableSemaphores;
			std::vector<VkSemaphore> renderFinishedSemaphores;
			std::vector<VkFence> inFlightFences;
			uint32_t currentFrame = 0;
			bool framebufferResized = false;



			void initWindow();
			void initVulkan();
			void mainLoop();
			static void framebufferResizeCallback(GLFWwindow *window, int width, int height);


			// Clean Ups
			void cleanup();
			void cleanupSwapChain();


			// swapChains
			void recreateSwapChain();
			void createSwapChain();
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

			// instance
			void createInstance();
			void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
			void setupDebugMessenger();

			// surface
			void createSurface();

			// device
			void pickPhysicalDevice();
			void createLogicalDevice();
		    bool isDeviceSuitable(VkPhysicalDevice device);
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);


			//images
			void createImageViews();



			// render
			void createRenderPass();
			void createGraphicsPipeline();

			
			//buffer
			void createFramebuffers();
			void createCommandBuffers();
			void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

			//commandPool
			void createCommandPool();


			//extensions
			std::vector<const char*> getRequiredExtensions();
			 bool checkValidationLayerSupport() ;

			//command sync
			void createSyncObjects();

			//drawframe
			void drawFrame();



			//create shaders
			VkShaderModule createShaderModule(const std::vector<char>& code);
			static std::vector<char> readFile(const std::string& filename);
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);












	};

}
