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
	GLFWwindow *m_window;

	void initWindow() {
		// tell glfw to not create an opengl context (use vulkan instead)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// option 4 is a specific monitor to open the window on
		// option 5 is opengl-only option (not relevant here)
		window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);

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
