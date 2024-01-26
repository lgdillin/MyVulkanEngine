//#include <vulkan/vulkan.h>
#define VK_VERSION_1_1 1
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

#define DEBUGMODE false

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
#ifdef DEBUGMODE
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif
const std::vector<const char *> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};


class HelloTriangleApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanUp();
	}
	
private:
	GLFWwindow *m_window;
	VkInstance m_instance;

	void initWindow() {
		// tell glfw to not create an opengl context (use vulkan instead)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// option 4 is a specific monitor to open the window on
		// option 5 is opengl-only option (not relevant here)
		m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan() {
		createInstance();
	}
	
	void createInstance() {
		if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
		
		// this type of struct has a pNext member that can point to
		// extension information in the future
		VkApplicationInfo appInfo{};
		// specify what type of struct this is with sType
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "hello triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "no engine name";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;
		
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
	
		uint32_t glfwExtensionCount = 0;
		const char **glfwExtensions;
		// use glfw's built in function that returns the extensions
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);	
		
		// these last two members determine the global validation layers to enable
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		
		createInfo.enabledLayerCount = 0;
		
		// we have now created all our specification and can create instance
		VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
		if(result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create Instance");
		}
		
		
		
		/*
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		std::cout << "available extensions" << std::endl;
		for(const auto &e : extensions) {
			std::cout << '\t' << e.extensionName << std::endl;
		}
		*/
		
	}
	
	void mainLoop() {
		while(glfwWindowShouldClose(m_window)) {
			glfwPollEvents();
		}
	}
	
	bool checkValidationLayerSupport() {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
		
		for(const char * layerName : validationLayers) {
			bool layerFound = false;
			
			for(const auto &layerProperties : availableLayers) {
				std::cout << layerProperties.layerName << std::endl;
				if(strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			
			if(!layerFound) {
				return false;
			}
		}
		std::cout << "Validation Layers found!" << std::endl;
		return true;
	}
	
	void cleanUp() {
		vkDestroyInstance(m_instance, nullptr);
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
};


int main() {
	
	HelloTriangleApplication app;
	
	try {
		app.run();
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	
	return 0;
}
