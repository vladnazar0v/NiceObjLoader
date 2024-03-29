#include <WindowManager.hpp>

GLFWwindow* WindowManager::window = nullptr;

WindowManager::WindowManager(const std::uint32_t& screenWidth, const std::uint32_t& screenHeight, 
                             const std::string winName,
                             bool _visible) 
{
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_VISIBLE, _visible);
    window = glfwCreateWindow(screenWidth, screenHeight, winName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // 	// Cull triangles which normal is not towards the camera
	// glEnable(GL_CULL_FACE);
}

void WindowManager::runWindow(const float& dt, const std::function<void()>& renderFunc) {
    renderFunc();
    glfwSwapBuffers(window);
    glfwPollEvents();
    this->cameraMovement(dt);
}

void WindowManager::setVisibility(bool _switch) noexcept{
    if (!_switch) {
        glfwPollEvents();
        glfwHideWindow(window);
    } else {
        glfwPollEvents();
        glfwShowWindow(window);
    }
}
void WindowManager::setCursor(bool _switch) noexcept {
    if (_switch)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // enable cursor
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor
}