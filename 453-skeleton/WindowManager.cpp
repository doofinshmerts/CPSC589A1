/**
 * CPSC 589 W25 Assignment 1
 * @name Holden Holzer
 * @email holden.holzer@ucalgary.ca
 *
 * Modified from provided 453-skeleton-Assignment-1-capFix files
 */
#include "WindowManager.h"
#include "InputManager.h"

#include <iostream>

WindowManager::WindowManager(int width, int height)
{
    this->width = width;
    this->height = height;
}

bool WindowManager::SetupWindow()
{
    std::cout << "seting up window" << std::endl;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width, height, "Assignment3", NULL, NULL);
    if (window == NULL)
    {
        std::cout<<"window setup failed" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    

    return true;
}

void WindowManager::SetInputManager(InputManager *_input)
{
    glfwSetWindowUserPointer(window, _input);
    // bind meta callbacks to actual callbacks
    glfwSetKeyCallback(window, KeyboardInputHandler);
    glfwSetMouseButtonCallback(window, MouseButtonInputHandler);
    glfwSetCursorPosCallback(window, CursorPositionInputHandler);
    glfwSetScrollCallback(window, ScrollWheelInputHandler);
    glfwSetFramebufferSizeCallback(window, UpdateWindowSize); // if your window is not resizing then you may not have set the input manager
}

bool WindowManager::ShoudWindowClose()
{
    return glfwWindowShouldClose(window);
}

GLFWwindow *WindowManager::GetWindowPointer()
{
    return window;
}

void WindowManager::UpdateWindowSize(GLFWwindow *_window, int _width, int _height)
{
    InputManager *_input = static_cast<InputManager *>(glfwGetWindowUserPointer(_window));
    if (_input != nullptr)
    {
        _input->HandleWindowResize(_width, _height);
    }
    
    // update the width and height of the window
    glViewport(0, 0, _width, _height);
}

void WindowManager::KeyboardInputHandler(GLFWwindow *_window, int key, int scancode, int action, int mods)
{
    InputManager *_input = static_cast<InputManager *>(glfwGetWindowUserPointer(_window));
    if (_input != nullptr)
    {
        // GNDN
    }
}

void WindowManager::MouseButtonInputHandler(GLFWwindow *_window, int button, int action, int mods)
{
    InputManager *_input = static_cast<InputManager *>(glfwGetWindowUserPointer(_window));

    if(_input != nullptr)
    {
        _input->HandleMouseButton(button, action, mods);
    }
 
}

void WindowManager::CursorPositionInputHandler(GLFWwindow *_window, double x_pos, double y_pos)
{
    InputManager *_input = static_cast<InputManager *>(glfwGetWindowUserPointer(_window));
    if(_input != nullptr)
    {
        _input->HandleCursorPositionChange(x_pos, y_pos);
    }
}

void WindowManager::ScrollWheelInputHandler(GLFWwindow *_window, double xoffset, double yoffset)
{
    InputManager *_input = static_cast<InputManager *>(glfwGetWindowUserPointer(_window));
  
}