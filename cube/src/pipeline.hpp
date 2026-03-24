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
#include <unordered_set>
#include "window.hpp"


namespace cube {
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
		uint32_t graphicsFamily;
		uint32_t presentFamily;
		bool graphicsFamilyHasValue = false;
		bool presentFamilyHasValue = false;

		bool isComplete() {
			return graphicsFamilyHasValue && presentFamilyHasValue;
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

	struct SimplePushConstantData
	{
		glm::mat2 transform{1.f};
		glm::vec2 offset;
		alignas(16) glm::vec3 color;

	};


	class Cube {
		public:
			Cube(Window &window_);
			void run();
			Cube(const Cube& )= delete;
			Cube& operator=(const Cube&)= delete;
			~Cube();


			//physical QueueFamilyIndices
			 QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }

		private:

			// window Tools
			Window &window_;


			// Vulkan Tools
			VkInstance instance_{};
		    VkDebugUtilsMessengerEXT debugMessenger;
			VkSurfaceKHR surface_{};


			// Devices Tools
			VkPhysicalDeviceProperties properties;
			VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
			VkDevice device_{VK_NULL_HANDLE};
			VkQueue graphicsQueue_{VK_NULL_HANDLE};
			VkQueue presentQueue_{VK_NULL_HANDLE};


			//command pools
			VkCommandPool commandPool_{VK_NULL_HANDLE};


			// Window methods 
			void initWindow();
			void mainLoop();


			// Vulkan Methods
			void initVulkan();
			void createInstance();
			void setupDebugMessenger();
			void createSurface();

			// Devices
			void pickPhysicalDevice();
			bool isDeviceSuitable(VkPhysicalDevice device);
			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
			void createLogicalDevice();


			//command pool
			void createCommandPool();
			











			//helper functions
			void cleanUp();
			bool checkValidationLayerSupport();
			std::vector<const char*> getRequiredExtensions();
			void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
			void hasGflwRequiredInstanceExtensions();
			static  VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
					VkDebugUtilsMessageTypeFlagsEXT messageType, 
					const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
			

		};


}
