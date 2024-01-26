//#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanUp();
	}
	
private:
	void initVulkan() {
		
	}
	
	void mainLoop() {
		
	}
	
	void cleanUp() {
		
	}
};


int main() {
	std::cout << "Hi" << std::endl;
	
	HelloTriangleApplication app;
	
	try {
		app.run();
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	
	return 0;
}
